
//
// Map.cpp for Map in /home/tekm/tek2/cpp_arcade/games/nibbler
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Tue Mar  7 15:46:54 2017 leroy_0
// Last update Tue Mar  7 15:46:54 2017 leroy_0
//

#include		"Map.hpp"

Map::Map(const uint16_t & width, const uint16_t & height)
{

  _map = reinterpret_cast<struct arcade::GetMap*>(new char[sizeof(struct arcade::GetMap)
							   + sizeof(arcade::TileType) * (width * height)]);
  _map->type = arcade::CommandType::GET_MAP;
  _map->width = width;
  _map->height = height;

  for (int i = 0; i < height; ++i)
  {
    for (int z = 0; z < width; ++z)
    {
      _map->tile[i * width + z] = arcade::TileType::EMPTY;
    }
  }
}

arcade::TileType    Map::getTypeTilefromPos(int x, int y)
{
    if (x < this->_map->width &&  x > 0 &&  y > 0 && y < this->_map->height)
    {
      return (this->_map->tile[y * this->_map->width + x]);
    }
    return arcade::TileType::BLOCK;
}

arcade::GetMap		*Map::getMap()
{
  return(_map);
}