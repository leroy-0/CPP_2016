/*
** manager.cpp for trade in /home/kleinh/Documents/trade/src/manager.cpp
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Sat Jun 10 11:45:34 2017 Arthur Klein
** Last update Sat Jun 10 11:45:34 2017 Arthur Klein
*/

#include <iostream>
#include <fstream>
#include "manager.hpp"
#include "trade.hpp"

Manager::Manager()
{
  int		money;
  size_t	totalDay;

  std::cin >> money;
  std::cin >> totalDay;
  this->_money = money;
  this->_totalDay = totalDay;
}

Manager::~Manager()
{

}

int		Manager::run()
{
  std::string	line;
  Trade		robot(this->_totalDay, this->_money);
  action   act;
  int     value;

  while (robot.getDayClass().getCurrentDay() < robot.getDayClass().getTotalDay())
  {
    std::cin >> line;
    if (line == "--END--")
      return (0);
    value = atoi(line.c_str());
    robot.setValue(value);
    act = robot.chooseTheAction(value);
    if (!robot.manageSells())
      robot.manageAction(act, value);
    robot.getDayClass().setCurrentDay(1);
  }
  return (0);
}