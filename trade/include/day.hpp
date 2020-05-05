/*
** day.hpp for trade in /home/kleinh/Documents/trade/include/day.hpp
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Sat Jun 10 11:41:39 2017 Arthur Klein
** Last update Sat Jun 10 11:41:40 2017 Arthur Klein
*/

#ifndef PROJECT_DAY_HPP
#define PROJECT_DAY_HPP

#include <iostream>
#include <string>
#include <list>

class Day
{
private:
  size_t	_totalDay;
  size_t	_currentDay;

public:
  Day(size_t);
  ~Day();
  void		setTotalDay(size_t);
  size_t	getTotalDay();
  void		setCurrentDay(size_t);
  size_t	getCurrentDay();

};

#endif //PROJECT_DAY_HPP
