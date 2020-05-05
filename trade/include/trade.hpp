/*
** trade.hpp for trade in /home/kleinh/Documents/trade/include/trade.hpp
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Sat Jun 10 11:22:10 2017 Arthur Klein
** Last update Sat Jun 10 11:22:12 2017 Arthur Klein
*/
#ifndef _TRADE_HPP_
# define _TRADE_HPP_

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "day.hpp"

#define   DAY_BEGIN     (5)
#define   DAY_STOP      (80)
#define   RISK_LVL      (3)

#define   FEE_COST      (0.0015)

enum action
{
  BUY,
  SELL,
  WAIT,
  BUY_10,
  SELL_10
};

class		Trade
{
private:
  Day		*_day;
  int		_money;
  int		_actions;
  int   _begin;
  int   _analyse_day;
  int   _last_value_bought;
  std::vector<int>  _oldValues;
  std::vector<int>  _oldMoyennes;

public:
  action		chooseTheAction(int value);
  void		sell(int);
  void		buy(int);
  void		wait();
  Day		&getDayClass();
  int		moyenne(unsigned int);
  int		ecartType(int moyenne, unsigned int);
  int		variance(int moyenne, unsigned int);
  bool  begin();
  void  setValue(int value);
  std::vector<int>  getValues() const;
  void  manageAction(action act, int value);
  bool  manageSells();
  void  displayInfo(int moyenne, int value, int ecart_type);
  Trade(size_t, int);
  ~Trade();
};

#endif	/* _TRADE_HPP_ */