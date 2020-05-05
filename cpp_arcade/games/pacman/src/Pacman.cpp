//
// Pacman.cpp for Pacman in /home/tekm/tek2/cpp_arcade/games/pacman
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Thu Apr  6 17:02:31 2017 leroy_0
// Last update Thu Apr  6 17:02:32 2017 leroy_0
//

#include <istream>
#include <unistd.h>
#include "Pacman.hpp"

arcade::Pacman::Pacman(const std::string & mapname)
{
  _map = new Pacmap(mapname);
  _score = 0;
  _player = new Character(10, 20);
  _ghost.push_back(PacEnnemy(_map, 10, 12));
  _ghost.push_back(PacEnnemy(_map, 11, 12));
  _ghost.push_back(PacEnnemy(_map, 10, 13));
  _ghost.push_back(PacEnnemy(_map, 11, 13));
  _player->getDir()->lenght = 1;
  _powerup = false;
  _start = std::time(NULL);
}

Character 		*arcade::Pacman::getPlayer()
{
  return (_player);
}

Pacmap      *arcade::Pacman::getMap()
{
  return (_map);
}

bool        arcade::Pacman::didIWin()
{
    for (int i = 0; i < _map->getMap()->height; ++i) {
        for (int z = 0; z < _map->getMap()->width; ++z) {
            if (_map->getMap()->tile[i * _map->getMap()->width + z] == arcade::TileType::OTHER)
                return (false);
        }
    }
    return (true);
}

void 		arcade::Pacman::manageDir(arcade::CommandType event, arcade::CommandType *ret)
{
    if (this->didIWin())
    {
        *ret = arcade::CommandType::MENU;
        return;
    }
  _map->getMap()->tile[_player->getDir()->position[0].x + _player->getDir()->position[0].y * _map->getMap()->width] = arcade::TileType::EMPTY;
  if (event == arcade::CommandType::SWITCH_LIB_PREV)
  {
    *ret = arcade::CommandType::SWITCH_LIB_PREV;
    return;
  }
  else if (event == arcade::CommandType::SWITCH_LIB_NEXT)
  {
    *ret = arcade::CommandType::SWITCH_LIB_NEXT;
    return;
  }
  else if (event == arcade::CommandType::SWITCH_GAME_NEXT)
  {
    *ret = arcade::CommandType::SWITCH_GAME_NEXT;
    return;
  }
  else if (event == arcade::CommandType::SWITCH_GAME_PREV)
  {
    *ret = arcade::CommandType::SWITCH_GAME_PREV;
    return;
  }
  else if (event == arcade::CommandType::STOP)
  {
    *ret = arcade::CommandType::STOP;
    return;
  }
  else if (event == arcade::CommandType::MENU || (_map->getMap()->tile[_player->getDir()->position->x + _player->getDir()->position->y * _map->getMap()->width] == arcade::TileType::EVIL_DUDE && _powerup == false))
  {
    *ret = arcade::CommandType::MENU;
    return;
  }
  else if (event == arcade::CommandType::RESTART)
  {
    *ret = arcade::CommandType::RESTART;
    return ;
  }
  if (event != arcade::CommandType::UNDEFINED)
    _player->getDir()->type = event;
  if (_player->getDir()->type == arcade::CommandType::GO_UP)
  {
    if (_player->getDir()->position->y - 1 < 0
	|| _map->getMap()->tile[_map->getMap()->width * (_player->getDir()->position->y - 1) + _player->getDir()->position->x] == arcade::TileType::BLOCK);
    else
    {
      if (_map->getMap()->tile[_map->getMap()->width * (_player->getDir()->position->y - 1) + _player->getDir()->position->x] == arcade::TileType::OTHER)
	_score++;
      _player->getDir()->position->y--;
    }
  }
  else if (_player->getDir()->type == arcade::CommandType::GO_DOWN)
  {
    if (_player->getDir()->position->y + 1 > _map->getMap()->height
	|| _map->getMap()->tile[_map->getMap()->width * (_player->getDir()->position->y + 1) + _player->getDir()->position->x] == arcade::TileType::BLOCK);
    else
    {
      if (_map->getMap()->tile[_map->getMap()->width * (_player->getDir()->position->y + 1) + _player->getDir()->position->x] == arcade::TileType::OTHER)
	_score++;
      _player->getDir()->position->y++;
    }
  }
  else if (_player->getDir()->type == arcade::CommandType::GO_RIGHT)
  {
    if (_player->getDir()->position->x % _map->getMap()->width + 1 >= _map->getMap()->width
	|| _map->getMap()->tile[_map->getMap()->width * _player->getDir()->position->y + (_player->getDir()->position->x + 1)] == arcade::TileType::BLOCK);
    else
    {
      if (_map->getMap()->tile[_map->getMap()->width * (_player->getDir()->position->y) + _player->getDir()->position->x + 1] == arcade::TileType::OTHER)
	_score++;
      _player->getDir()->position->x++;
    }
  }
  else if (_player->getDir()->type == arcade::CommandType::GO_LEFT)
  {
    if (_player->getDir()->position->x % _map->getMap()->width - 1 < 0
	|| _map->getMap()->tile[_map->getMap()->width * _player->getDir()->position->y + (_player->getDir()->position->x - 1)] == arcade::TileType::BLOCK);
    else
    {
      if (_map->getMap()->tile[_map->getMap()->width * (_player->getDir()->position->y) + _player->getDir()->position->x - 1] == arcade::TileType::OTHER)
	_score++;
      _player->getDir()->position->x--;
    }
  }
  
  managePowerUp();

  _map->getMap()->tile[_player->getDir()->position->x + _player->getDir()->position->y * _map->getMap()->width] = arcade::TileType::PLAYER;

  for (auto i = this->_ghost.begin(); i < this->_ghost.end(); ++i)
  {
    if ((*i).run() == 0 && _powerup == false)
    {
      *ret = arcade::CommandType::MENU;
      return ;
    }
    if (_powerup && ((*i).getDir().x == _player->getDir()->position->x && (*i).getDir().y == _player->getDir()->position->y))
    {
      _map->getMap()->tile[(*i).getDir().x + (*i).getDir().y * _map->getMap()->width] = arcade::TileType::PLAYER;
      (*i).setPos(10, 12);
    }
  }
}

void 		arcade::Pacman::managePowerUp()
{
  if (_map->getMap()->tile[_player->getDir()->position->x + _player->getDir()->position->y * _map->getMap()->width] == arcade::TileType::POWERUP)
  {
    _powerup = true;
    _start = std::time(NULL);
  }

  if (_powerup && (std::time(NULL) - _start) >= 10)
  {
    _powerup = false;
  }

  if (_powerup && _map->getMap()->tile[_player->getDir()->position->x + _player->getDir()->position->y * _map->getMap()->width] == arcade::TileType::EVIL_DUDE)
  {
    for (auto i = this->_ghost.begin(); i < this->_ghost.end(); ++i)
    {
      if ((*i).getDir().x == _player->getDir()->position->x && (*i).getDir().y == _player->getDir()->position->y)
      {
        (*i).setPos(10, 12);
        return ;
      }
    }
  }
}

arcade::CommandType 	arcade::Pacman::analyseEvent(arcade::CommandType event)
{
  if (event == arcade::CommandType::GO_UP && _map->getMap()->tile[(_player->getDir()->position->y - 1) * _map->getMap()->width + _player->getDir()->position->x] != arcade::TileType::BLOCK)
    return (event);
  else if (event == arcade::CommandType::GO_DOWN && _map->getMap()->tile[(_player->getDir()->position->y + 1) * _map->getMap()->width + _player->getDir()->position->x] != arcade::TileType::BLOCK)
    return (event);
  else if (event == arcade::CommandType::GO_LEFT && _map->getMap()->tile[_player->getDir()->position->y * _map->getMap()->width + (_player->getDir()->position->x - 1)] != arcade::TileType::BLOCK)
    return (event);
  else if (event == arcade::CommandType::GO_RIGHT && _map->getMap()->tile[_player->getDir()->position->y * _map->getMap()->width + (_player->getDir()->position->x + 1)] != arcade::TileType::BLOCK)
    return (event);
  else if (event == arcade::CommandType::SWITCH_LIB_NEXT)
    return (event);
  else if (event == arcade::CommandType::SWITCH_LIB_PREV)
    return (event);
  else if (event == arcade::CommandType::SWITCH_GAME_NEXT)
    return (event);
  else if (event == arcade::CommandType::SWITCH_GAME_PREV)
    return (event);
  else if (event == arcade::CommandType::STOP)
    return (event);
  else if (event == arcade::CommandType::MENU)
    return (event);
  else if (event == arcade::CommandType::RESTART)
    return (event);
  return (arcade::CommandType::UNDEFINED);
}

arcade::CommandType	arcade::Pacman::run(IGraphics *lib)
{
  arcade::CommandType		ret = arcade::CommandType::UNDEFINED;

  lib->loadAssets("pacman");
  while (ret != arcade::CommandType::STOP)
  {
    manageDir(analyseEvent(lib->getEvent()), &ret);
    if (ret == arcade::CommandType::SWITCH_LIB_PREV
	|| ret == arcade::CommandType::SWITCH_LIB_NEXT
	|| ret == arcade::CommandType::SWITCH_GAME_PREV
	|| ret == arcade::CommandType::SWITCH_GAME_NEXT
	|| ret == arcade::CommandType::STOP
	|| ret == arcade::CommandType::MENU
	|| ret == arcade::CommandType::RESTART)
      break;
    lib->displayMap(_map->getMap(), _score, _player->getDir()->position[0].x, _player->getDir()->position[0].y);
  }
  return (ret);
}

extern "C" void		Play()
{
  static int		  i = 0;
  arcade::CommandType             ret = arcade::CommandType::UNDEFINED;
  uint16_t 		    tmp;
  arcade::CommandType   command;
  arcade::CommandType   to_go;
  arcade::Pacman	*_new;

  if (i == 0)
  {
    _new = new arcade::Pacman("./games/pacman/maps/pacmap.pac");
    i++;
  }
  to_go = _new->getPlayer()->getDir()->type;
  while (std::cin.read(reinterpret_cast<char *>(&tmp), sizeof(uint16_t)))
  {
    command = static_cast<arcade::CommandType>(tmp);
    if (command == arcade::CommandType::GET_MAP)
      std::cout.write(reinterpret_cast<char *>(_new->getMap()->getMap()), sizeof(struct arcade::GetMap) + sizeof(enum arcade::TileType) * (_new->getMap()->getMap()->width * _new->getMap()->getMap()->height));
    else if (command == arcade::CommandType::WHERE_AM_I)
    {
      _new->getPlayer()->getDir()->type = arcade::CommandType::WHERE_AM_I;
      write(1, _new->getPlayer()->getDir(), sizeof(struct arcade::WhereAmI) + _new->getPlayer()->getDir()->lenght * sizeof(struct arcade::Position));
    }
    else if (command == arcade::CommandType::PLAY)
      _new->manageDir(_new->analyseEvent(to_go), &ret);
    else if (command == arcade::CommandType::GO_UP)
      to_go = arcade::CommandType::GO_UP;
    else if (command == arcade::CommandType::GO_DOWN)
      to_go = arcade::CommandType::GO_DOWN;
    else if (command == arcade::CommandType::GO_RIGHT)
      to_go = arcade::CommandType::GO_RIGHT;
    else if (command == arcade::CommandType::GO_LEFT)
      to_go = arcade::CommandType::GO_LEFT;
    _new->getPlayer()->getDir()->type = to_go;
  }
}

extern "C" arcade::Pacman *getLib()
{
  std::cout <<"Loading Pacman..." << std::endl;
  arcade::Pacman	*_new = new arcade::Pacman("./games/pacman/maps/pacmap.pac");
  return (_new);
}
