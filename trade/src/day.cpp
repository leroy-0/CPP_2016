/*
** day.cpp for trade in /home/kleinh/Documents/trade/src/day.cpp
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Sat Jun 10 11:29:06 2017 Arthur Klein
** Last update Sat Jun 10 11:29:06 2017 Arthur Klein
*/
#include "day.hpp"

Day::Day(size_t totalday) : _currentDay(0)
{
  this->_totalDay = totalday;
}

Day::~Day()
{

}

size_t Day::getTotalDay()
{
  return (this->_totalDay);
}

size_t Day::getCurrentDay()
{
  return (this->_currentDay);
}

void Day::setCurrentDay(size_t currentday)
{
  this->_currentDay += currentday;
}

void Day::setTotalDay(size_t totalday)
{
  this->_totalDay = totalday;
}