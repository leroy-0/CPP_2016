/*
** IGraph.hpp for cpp_arcade in /home/kleinh/Documents/cpp_arcade/inc/IGraph.hpp
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Sat Apr 08 16:46:22 2017 Arthur Klein
** Last update Sat Apr 08 16:46:23 2017 Arthur Klein
*/

#ifndef					PROJECT_IGRAPH_HPP
#define					PROJECT_IGRAPH_HPP

#include				"Protocol.hpp"
#include				<string>

namespace				arcade
{
    class				IGraphics
    {
    public:
      virtual	arcade::CommandType	 getEvent() = 0;
      virtual	void			           displayMap(arcade::GetMap *map, int score, int x, int y) = 0;
      virtual	void			           freeDisplay() = 0;
      virtual	int			             menu(arcade::CommandType) = 0;
      virtual	void			           loadAssets(const std::string & gameName) = 0;
      virtual                      ~IGraphics(){};
    };
};

#endif //PROJECT_IGRAPH_HPP
