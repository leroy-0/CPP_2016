/*
** manager.hpp for trade in /home/kleinh/Documents/trade/include/manager.hpp
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Sat Jun 10 11:44:05 2017 Arthur Klein
** Last update Sat Jun 10 11:44:07 2017 Arthur Klein
*/

#ifndef PROJECT_MANAGER_HPP
#define PROJECT_MANAGER_HPP

#include <cstring>

class Manager
{
private:
  int	_money;
  size_t _totalDay;

public:
  Manager();
  ~Manager();
  int run();
};

#endif //PROJECT_MANAGER_HPP
