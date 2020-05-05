/*
** IGame.hpp for cpp_arcade in /home/kleinh/Documents/cpp_arcade/games/commons/inc/IGame.hpp
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Sat Apr 08 16:41:10 2017 Arthur Klein
** Last update Sat Apr 08 16:41:10 2017 Arthur Klein
*/

#ifndef					PROJECT_IGAME_HPP
#define					PROJECT_IGAME_HPP

#include				"IGraph.hpp"

namespace				arcade
{
  class					IGame
  {
  public:
    virtual ~IGame() {};
    virtual arcade::CommandType		run(IGraphics *) = 0;
  };
};

#endif //PROJECT_IGAME_HPP
