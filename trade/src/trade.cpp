/*
** trade.cpp for trade in /home/kleinh/Documents/trade/src/trade.cpp
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Sat Jun 10 11:30:28 2017 Arthur Klein
** Last update Sat Jun 10 11:30:28 2017 Arthur Klein
*/

#include <cmath>
#include <iostream>
#include <fstream>
#include "trade.hpp"

Trade::Trade(size_t totalDay, int money) : _actions(0)
{
  this->_day = new Day(totalDay);
  this->_money = money;
  this->_begin = 0;
  this->_analyse_day = 0;
  this->_last_value_bought = -1;
}

Trade::~Trade()
{

}

void 	Trade::setValue(int value)
{
  _oldValues.push_back(value);
}

std::vector<int>  Trade::getValues() const
{
  return(_oldValues);
}

Day& Trade::getDayClass()
{
  return (*this->_day);
}

void Trade::buy(int value)
{
  int 	nb = this->_money / (value * FEE_COST);

  while ((nb * value) + (FEE_COST * nb * value) > this->_money)
    nb--;
  if (nb != 0)
  {
    this->_actions += nb;
    this->_money -= (nb * value) + (FEE_COST * nb * value);
    std::cout << "buy " << nb << std::endl;
  }
  else
    this->wait();
}

void Trade::sell(int value)
{
  int 	nb = this->_actions;

  if (nb != 0)
  {
    this->_actions -= nb;
    this->_money += (nb * value) - (FEE_COST * nb * value);
    std::cout << "sell " << nb << std::endl;
  }
  else
    this->wait();
}

void Trade::wait()
{
  std::cout << "wait" << std::endl;
}

int 		Trade::moyenne(unsigned int days)
{
  unsigned int		x;
  unsigned int		y;

  x = 0;
  y = 0;
  for (auto it = this->_oldValues.begin(); it < this->_oldValues.end(); ++it)
  {
    if (days == 0 || (x >= _oldValues.size() - days))
      y += (*it);
    x++;
  }
  if (x != 0)
  {
    if (days == 0)
      return (y / x);
    return (y / days);
  }
  return (0);
}

int 	Trade::variance(int moyenne, unsigned int days)
{
  unsigned int	varriance;
  unsigned int	i;

  i = 0;
  varriance = 0;
  for (auto it = this->_oldValues.begin(); it < this->_oldValues.end(); ++it)
  {
    if (days == 0 || i >= _oldValues.size() - days)
      varriance += pow(((*it) - moyenne), 2);
    i++;
  }
  if (i != 0)
  {
    if (days == 0)
      return (varriance / i);
    return (varriance / days);
  }
  return (varriance);
}

int 	Trade::ecartType(int moyenne, unsigned int days)
{
  int	ecartType;

  ecartType = sqrt(this->variance(moyenne, days));
  return (ecartType);
}

bool 	Trade::begin()
{
  this->_begin++;
  if (this->_begin > DAY_BEGIN)
    return (true);
  return (false);
}

void 	Trade::manageAction(action act, int value)
{
  if (act == action::BUY)
    this->buy(value);
  else if (act == action::SELL)
    this->sell(value);
  else if (act == action::WAIT)
    this->wait();
}

bool Trade::manageSells()
{
  if (this->getDayClass().getCurrentDay() + 1 == this->getDayClass().getTotalDay())
  {
    this->sell(this->_actions);
    return (true);
  }
  return (false);
}

void  Trade::displayInfo(int moyenne, int value, int ecart_type)
{
  static std::ofstream myfile("trade.log");

  myfile << "variance:" << this->variance(moyenne, this->_analyse_day) << std::endl;
  myfile << "value:" << value << std::endl;
  myfile << "moyenne:" << moyenne << std::endl;
  myfile << "ecart_type:" << ecart_type << std::endl;
  myfile << "moyenne + ecart_type * RISK_LVL:" << moyenne + (ecart_type * RISK_LVL) << std::endl;
  myfile << "last_bought:" << this->_last_value_bought << std::endl;
  myfile << "MONEY:" << this->_money << std::endl;
  myfile << "_analyse_day:" << this->_analyse_day << std::endl;
}

action Trade::chooseTheAction(int value)
{
  int 	moyenne;
  int 	ecart_type;
  bool  buying = true;
  bool  buy_now = false;
  bool  sell_now = false;

  if (this->begin())
  {
    moyenne = this->moyenne(this->_analyse_day);
    ecart_type = this->ecartType(moyenne, this->_analyse_day);
    this->_oldMoyennes.push_back(moyenne);
    //displayInfo(moyenne, value, ecart_type);
    if (this->getDayClass().getTotalDay() - DAY_STOP <= this->getDayClass().getCurrentDay())
      buying = false;
    if (value < moyenne - (ecart_type))
      buy_now = true;
     if (value > moyenne + (ecart_type * RISK_LVL))
      sell_now = true;
    if (buying && value > this->_oldValues[this->_oldValues.size() - 2]
      && this->_last_value_bought == -1 && buy_now)
    {
      this->_last_value_bought = value;
      this->_analyse_day = 1;
      buy_now = false;
      return (BUY);
    }
    else if (((value > this->_last_value_bought + (ecart_type * RISK_LVL)
      && sell_now) || !buying)
      && (this->_last_value_bought < value && this->_last_value_bought != -1))
    {
      sell_now = false;
      this->_last_value_bought = -1;
      this->_analyse_day = 1;
      return (SELL);
    }
  }
  this->_analyse_day++;
  return (WAIT);
}