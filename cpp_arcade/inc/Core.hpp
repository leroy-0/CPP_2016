/*
** Core.hpp for cpp_arcade in /home/kleinh/Documents/cpp_arcade/inc/Core.hpp
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Sat Apr 08 16:44:46 2017 Arthur Klein
** Last update Sat Apr 08 16:44:46 2017 Arthur Klein
*/

#ifndef					PROJECT_CORE_HPP
#define					PROJECT_CORE_HPP

#include				<map>
#include				"Error.hpp"
#include				"IGraph.hpp"
#include				"IGame.hpp"

namespace				arcade
{
  class					Core
  {
  private:
    std::map<std::string, void *>	libs;
    std::map<std::string, void *>	games;
    IGraphics				*_gfx;
    arcade::CommandType			old_state;
    IGame 				*game;
    std::string				gfx_libs[3] = {"lib/lib_arcade_libcaca.so", "lib/lib_arcade_sfml.so", "lib/lib_arcade_opengl.so"};
    int					currentLib;
    std::string				game_libs[2] = {"snake", "pacman"};
    int					currentGame;
    void				*currentHandler;
    void				changeGameRun(int increment);

  public:
    Core();
    virtual ~Core();

    Core				*run() throw(arcade::Error);
    IGame				*loadSymGame(const std::string &function);
    IGraphics				*loadSymGraph(const std::string &function);
    void				load(const std::string &) throw(arcade::Error);
    void				changeLib(int increment);
    void				checkcursor(const int inc);
    void				check_state(CommandType *ret);
    void				getMyLib() throw(arcade::Error);
    void				getMyGame() throw(arcade::Error);
    void				closeMyLib();
  };
};

#endif					//PROJECT_CORE_HPP
