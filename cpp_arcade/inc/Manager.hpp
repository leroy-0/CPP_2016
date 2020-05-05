//
// Manager.hpp for Manager in /home/tekm/tek2/cpp_arcade
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Tue Mar  7 14:10:43 2017 leroy_0
// Last update Tue Mar  7 14:10:49 2017 leroy_0
//

#ifndef			__MANAGER_HPP_
#define			__MANAGER_HPP_

#include		<iostream>
#include		<dlfcn.h>

#include		"Protocol.hpp"
#include		"Error.hpp"
#include		"Core.hpp"

namespace		arcade
{
  class			Manager
  {
  private:
    Core		*_core;
  public:
    Manager(const int & argc, char ** argv);
    virtual ~Manager() {};

    void		run();

  private:
    void		*_handler;
  };
}

#endif /* __MANAGER_HPP */