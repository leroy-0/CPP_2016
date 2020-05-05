/*
** arcade_libcaca.hpp for cpp_arcade in /home/kleinh/Documents/cpp_arcade/lib/caca/inc/arcade_libcaca.hpp
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Sat Apr 08 16:49:10 2017 Arthur Klein
** Last update Sat Apr 08 16:49:11 2017 Arthur Klein
*/

#ifndef					PROJECT_ARACADE_LIBCACA_HPP
#define					PROJECT_ARACADE_LIBCACA_HPP

#include				<iostream>
#include				<map>
#include				"IGraph.hpp"

namespace				arcade
{
    class				libcaca : public IGraphics
    {
      caca_display_t			*dp;
      caca_canvas_t			*cv;
      caca_event_t			ev;
      std::string			actualGame;
      int				_width;
      int				_height;
      int       _offsety;
      std::map<std::string, std::map<arcade::TileType, enum caca_color>>  textureMap;
      std::map<std::string, std::map<arcade::TileType, std::string>>  spriteMap;
      enum caca_color getColorFromTexture(arcade::TileType);
      std::string getSpriteFromTexture(arcade::TileType tile);
    public:
      int				initDisplay(int width, int height);
      void				freeDisplay();
      arcade::CommandType		getEvent();
      void 				displayMap(arcade::GetMap *map, int score, int x, int y);
      arcade::CommandType		manageEventCore(int &  ret);
      void				loadAssets(const std::string & gameName);
      int				menu(arcade::CommandType);
    public:
      libcaca();
      virtual ~libcaca() {};
    };
}

#endif //PROJECT_ARACADE_LIBCACA_HPP
