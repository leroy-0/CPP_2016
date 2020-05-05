/*
** arcade_libsfml.hpp for cpp_arcade in /home/kleinh/Documents/cpp_arcade/lib/sfml/inc/arcade_libsfml.hpp
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Sat Apr 08 16:58:10 2017 Arthur Klein
** Last update Sat Apr 08 16:58:10 2017 Arthur Klein
*/

#ifndef					PROJECT_ARACADE_LIBSFML_HPP
#define					PROJECT_ARACADE_LIBSFML_HPP

#include				<iostream>
#include				"IGraph.hpp"

namespace				arcade
{
      class				libsfml : public IGraphics
      {
	sf::RenderWindow		*window;
	sf::Event			*event;
	int				_width;
	int				_height;
	int				_ratio;

	std::map<std::string, std::map<arcade::TileType, sf::Texture *>>  textureMap;
	std::map<arcade::TileType, sf::Sprite *> spriteMap;

      public:
	int 				initDisplay(int width, int height);
	void 				freeDisplay();
	arcade::CommandType		getEvent();
	void				displayMap(arcade::GetMap *map, int score, int playerx, int playery);
	void				loadAssets(const std::string & gameName);
	int				menu(arcade::CommandType);
	virtual ~libsfml() {};
      public:
	libsfml();
      };
}

#endif //PROJECT_ARACADE_SFML_HPP