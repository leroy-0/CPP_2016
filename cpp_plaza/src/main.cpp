//
// main.cpp for plaza in /home/kleinh/Documents/cpp_plaza/src
// 
// Made by Arthur Klein
// Login   <arthur.klein@epitech.eu>
// 
// Started on  Tue Apr 11 09:25:59 2017 Arthur Klein
// Last update Thu Apr 20 14:43:19 2017 Arthur Klein
//

#include		<iostream>
#include "Plazza.hpp"
#include		"Manager.hpp"

int			main(int ac, char **av)
{
  plazza::Manager	*manager;

  if (av[1] != NULL && ac == 2)
  {
    manager = new plazza::Manager(static_cast<std::string>(av[1]));
    manager->run();
  }
  else
    std::cerr << "Usage : " << av[0] << " NumberOfthread" << std::endl;
  return (0);
 }
