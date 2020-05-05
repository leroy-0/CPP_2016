//
// Pacmap.cpp for Pacmap in /home/tekm/tek2/cpp_arcade/games/nibbler
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Tue Mar  7 15:46:54 2017 leroy_0
// Last update Tue Mar  7 15:46:54 2017 leroy_0
//

#include <sstream>
#include <string>
#include <fstream>
#include "Pacmap.hpp"

Pacmap::Pacmap(const std::string & mapname)
{
  loadMap(mapname);
}

void				Pacmap::loadMap(const std::string & mapname)
{
  std::ifstream			infile(mapname);
  std::string			line;
  int				height = 0;
  int 				width = 0;

  while (std::getline(infile, line))
  {
    std::istringstream 	iss(line);
    std::string 		map_line;
    if (!(iss >> map_line))
      break;
    if (height == 0)
      width = map_line.size();
    height++;
  }
  _map = reinterpret_cast<struct arcade::GetMap*>(new char[sizeof(struct arcade::GetMap) + sizeof(arcade::TileType) * (width * height)]);
  _map->type = arcade::CommandType::GET_MAP;
  _map->width = width;
  _map->height = height;
  infile = std::ifstream(mapname);
  for (int i = 0; i < height; ++i)
  {
    std::getline(infile, line);
    std::istringstream 	iss(line);
    std::string 		map_line;

    if (!(iss >> map_line))
      break;
    for (int z = 0; z < width ; ++z)
      _map->tile[i * width + z] = (arcade::TileType)(map_line[z] - '0');
  }
}

arcade::TileType    Pacmap::getTypeTilefromPos(int x, int y)
{
    if (x < this->getMap()->width &&  x > 0 &&  y > 0 && y < this->getMap()->height)
        return (this->getMap()->tile[(y * this->getMap()->width) + x]);
    return arcade::TileType::BLOCK;
}

arcade::GetMap 		*Pacmap::getMap()
{
  return(_map);
}