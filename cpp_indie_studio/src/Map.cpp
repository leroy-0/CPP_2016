//
// Map.cpp for Map in /home/tekm/tek2/cpp_indie_studio
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Fri May  5 22:15:02 2017 leroy_0
// Last update Fri May  5 22:15:03 2017 leroy_0
//

#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include "Map.hpp"

IndieGame::Map::Map(const std::string & name)
{
  _height = 0;
  _width = 0;
  _map = NULL;
  setMap(name, true);
}

IndieGame::Map::~Map()
{
  delete _map;
}

Ogre::Vector3   IndieGame::Map::getPlayerPos(unsigned int nb) const
{
  nb--;
  if (static_cast<int>(nb) >= 0 && nb < _playersPos.size())
    return (_playersPos.at(nb));
  return (Ogre::Vector3(0, 0, 0));
}

bool 	IndieGame::Map::setMap(const std::string & name, bool state)
{
  std::ifstream			infile(name);
  std::string			line;

  _height = 0;
  _width = 0;
  if (!infile.good())
  {
    std::cerr << "Failed to load map: " << name << std::endl;
    return (false);
  }

  while (std::getline(infile, line))
  {
    std::istringstream 	iss(line);
    std::string 		map_line;
    if (!(iss >> map_line))
      break;
    if (map_line.empty())
      break;
    if (_height == 0)
      _width = map_line.size();
    _height++;
  }

  _map = new int*[_height];

  infile = std::ifstream(name);
  for (int i = 0; i < _height; ++i)
  {
    std::getline(infile, line);
    std::istringstream	iss(line);
    std::string		map_line;

    if (!(iss >> map_line))
      break;
    _map[i] = new int[_width];
    for (int z = 0; z < _width ; ++z)
    {
      _map[i][z] = map_line[z] - '0';
      if (_map[i][z] == 2)
	_playersPos.push_back(Ogre::Vector3(z, 0, i));
    }
  }

  if (state) // IF LOAD NEW GAME
    generateBreakableWall();
  for (auto it = _playersPos.begin(); it < _playersPos.end(); ++it) {
    _map[static_cast<int>((*it).z)][static_cast<int>((*it).x)] = 0;
  }
  return (true);
}



int 		IndieGame::Map::checkPercentBreakableWall() {
  int		nbBreakableWall = 0;
  int		nbOther = 0;

  for (int y = 0; y < _width; ++y) {
    for (int x = 0; x < _height; ++x) {
      if (_map[x][y] == 1)
	nbBreakableWall++;
      else
	nbOther++;
    }
  }
  return ((nbOther / 100) * nbBreakableWall);
}

bool IndieGame::Map::checkValidBreakableWall(int x, int y) {
  if (x > 0 && _map[x - 1][y] == 2)
    return (false);
  else if (y > 0 && _map[x][y - 1] == 2)
    return (false);
  else if (y < _width && _map[x][y + 1] == 2)
    return (false);
  else if (x < _height && _map[x + 1][y] == 2)
    return (false);
  return (true);
}

void IndieGame::Map::generateBreakableWall() {
  int		x = 0;
  int		y = 0;

  while (1)
  {
    x = std::rand() % (_height - 1);
    y = std::rand() % (_width - 1);
    if (_map[x][y] != 2 && _map[x][y] != 3 && checkValidBreakableWall(x, y))
      _map[x][y] = 1;
    if (checkPercentBreakableWall() > 70)
      break;
  }
}

bool  IndieGame::Map::isCollision(Ogre::Vector3 nbox1, Ogre::Vector3 nbox2, Ogre::Vector3 ebox1, Ogre::Vector3 ebox2)
{
  if ((nbox2.x >= nbox1.x + ebox1.x)
      || (nbox2.x + ebox2.x <= nbox1.x)
      || (nbox2.y >= nbox1.y + ebox1.y)
      || (nbox2.y + ebox2.y <= nbox1.y)
      || (nbox2.z >= nbox1.z + ebox1.z)
      || (nbox2.z + ebox2.z <= nbox1.z))
    return (false);
  return (true);
}

int   IndieGame::Map::getMapPosX(int x) const
{
  x += ((getWidth() / 2) * RATIO_MAP);
  x += RATIO_MAP / 2;
  x /= RATIO_MAP;
  return (x);
}

int   IndieGame::Map::getMapPosY(int y) const
{
  y += ((getHeight() / 2) * RATIO_MAP);
  y += RATIO_MAP / 2;
  y /= RATIO_MAP;
  return (y);
}

int   IndieGame::Map::getWorldPosX(int x) const
{
  x -= (getWidth() / 2);
  x *= RATIO_MAP;
  return (x);
}

int   IndieGame::Map::getWorldPosY(int y) const
{
  y -= (getHeight() / 2);
  y *= RATIO_MAP;
  return (y);
}

int 	**IndieGame::Map::getMap() const
{
  return (_map);
}

int 	IndieGame::Map::getWidth() const
{
  return (_width);
}

int 	IndieGame::Map::getHeight() const
{
  return (_height);
	}