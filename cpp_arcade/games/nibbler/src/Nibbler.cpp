//
// Nibbler.cpp for Nibbler in /home/tekm/tek2/cpp_arcade/games/nibbler
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Tue Mar  7 15:30:39 2017 leroy_0
// Last update Tue Mar  7 15:30:40 2017 leroy_0
//

#include <istream>
#include <unistd.h>
#include "Nibbler.hpp"
#include "Character.hpp"

arcade::Nibbler::Nibbler(int width, int height)
{
	_map = new Map(width, height);
	_player = new Character(width / 2, height / 2);
	_player->getDir()->lenght = 4;
  _score = 0;
}

Character 		*arcade::Nibbler::getPlayer()
{
  return (_player);
}

void 		arcade::Nibbler::manageDir(arcade::CommandType event, CommandType *ret)
{
  static int   down = 0;

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
  else if (event == arcade::CommandType::MENU)
  {
    *ret = arcade::CommandType::MENU;
    return;
  }
  else if (event == arcade::CommandType::RESTART)
  {
    *ret = arcade::CommandType::RESTART;
    return;
  }
  if (event != arcade::CommandType::UNDEFINED)
    _player->getDir()->type = event;
  if (_player->getDir()->type == arcade::CommandType::GO_UP)
  {
    if (_player->getDir()->position->y - 1 < 0
	|| _map->getMap()->tile[_map->getMap()->width * (_player->getDir()->position->y - 1) + _player->getDir()->position->x] == arcade::TileType::BLOCK)
      *ret = CommandType::STOP;
    else
      _player->getDir()->position->y--;
  }
  else if (_player->getDir()->type == arcade::CommandType::GO_DOWN)
  {
    if (_player->getDir()->position->y + 1 >= _map->getMap()->height
	|| _map->getMap()->tile[_map->getMap()->width * (_player->getDir()->position->y + 1) + _player->getDir()->position->x] == arcade::TileType::BLOCK)
      *ret = CommandType::STOP;
    else
      _player->getDir()->position->y++;
  }
  else if (_player->getDir()->type == arcade::CommandType::GO_RIGHT)
  {
    if (_player->getDir()->position->x % _map->getMap()->width + 1 >= _map->getMap()->width
	|| _map->getMap()->tile[_map->getMap()->width * _player->getDir()->position->y + (_player->getDir()->position->x + 1)] == arcade::TileType::BLOCK)
      *ret = CommandType::STOP;
    else
      _player->getDir()->position->x++;
  }
  else if (_player->getDir()->type == arcade::CommandType::GO_LEFT)
  {
    if (_player->getDir()->position->x % _map->getMap()->width - 1 < 0
	|| _map->getMap()->tile[_map->getMap()->width * _player->getDir()->position->y + (_player->getDir()->position->x - 1)] == arcade::TileType::BLOCK)
      *ret = CommandType::STOP;
    else
      _player->getDir()->position->x--;
  }
  if (_map->getMap()->tile[_map->getMap()->width * _player->getDir()->position->y + _player->getDir()->position->x] == arcade::TileType::POWERUP && down == 0)
  {
    int lenght = _player->getDir()->lenght;
    _score += 10;
    lenght = std::rand() % 10;
    if (_player->getDir()->lenght >= lenght)
      lenght += _player->getDir()->lenght;
    down += lenght - _player->getDir()->lenght;

    _player->getDir()->lenght++;
    for (int i = _player->getDir()->lenght; i > 0; --i)
      _player->getHistory()[i] = _player->getHistory()[i - 1];
    _player->getHistory()[0] = _player->getDir()->type;
    if (down != 0)
      down--;
  }
  else if (down != 0)
  {
    _player->getDir()->lenght++;
    for (int i = _player->getDir()->lenght; i > 0; --i)
      _player->getHistory()[i] = _player->getHistory()[i - 1];
    _player->getHistory()[0] = _player->getDir()->type;
    down--;
  }
  else
    manageLenght();
  _map->getMap()->tile[_player->getDir()->position->x + _player->getDir()->position->y * _map->getMap()->width] = arcade::TileType::BLOCK;
}

void 		arcade::Nibbler::manageLenght()
{
  for (int i = _player->getDir()->lenght; i > 0; --i)
    _player->getHistory()[i] = _player->getHistory()[i - 1];
  _player->getHistory()[0] = _player->getDir()->type;

  for (int i = 1; i < _player->getDir()->lenght; ++i)
  {
    if (_player->getHistory()[i] == arcade::CommandType::GO_UP)
      _player->getDir()->position[i].y--;
    else if (_player->getHistory()[i] == arcade::CommandType::GO_RIGHT)
      _player->getDir()->position[i].x++;
    else if (_player->getHistory()[i] == arcade::CommandType::GO_LEFT)
      _player->getDir()->position[i].x--;
    else if (_player->getHistory()[i] == arcade::CommandType::GO_DOWN)
      _player->getDir()->position[i].y++;
  }
  if (_player->getHistory()[_player->getDir()->lenght] == arcade::CommandType::GO_UP)
    _player->getQueue()[1]--;
  else if (_player->getHistory()[_player->getDir()->lenght] == arcade::CommandType::GO_RIGHT)
    _player->getQueue()[0]++;
  else if (_player->getHistory()[_player->getDir()->lenght] == arcade::CommandType::GO_LEFT)
    _player->getQueue()[0]--;
  else if (_player->getHistory()[_player->getDir()->lenght] == arcade::CommandType::GO_DOWN)
    _player->getQueue()[1]++;
  _map->getMap()->tile[_player->getQueue()[0] + _player->getQueue()[1] * _map->getMap()->width] = arcade::TileType::EMPTY;
}

void 		arcade::Nibbler::managePowerUp()
{
  bool 	power = true;

  for (int i = 0; i < _map->getMap()->height; ++i)
    for (int z = 0; z < _map->getMap()->width ; ++z)
      if (_map->getMap()->tile[i * _map->getMap()->width + z] == arcade::TileType::POWERUP)
	power = false;

  if (power)
  {
    _powerup = std::rand() % (_map->getMap()->height * _map->getMap()->width);
    while (_map->getMap()->tile[_powerup] == arcade::TileType::BLOCK)
      _powerup = std::rand() % (_map->getMap()->height * _map->getMap()->width);
    _map->getMap()->tile[_powerup] = arcade::TileType::POWERUP;
  }
}

arcade::CommandType	arcade::Nibbler::analyseEvent(arcade::CommandType event)
{
  if (event == arcade::CommandType::GO_UP
      && _map->getMap()->tile[(_player->getDir()->position->y - 1) * _map->getMap()->width
			      + _player->getDir()->position->x] != arcade::TileType::BLOCK)
    return (event);
  else if (event == arcade::CommandType::GO_DOWN
	   && _map->getMap()->tile[(_player->getDir()->position->y + 1) * _map->getMap()->width
				   + _player->getDir()->position->x] != arcade::TileType::BLOCK)
    return (event);
  else if (event == arcade::CommandType::GO_LEFT
	   && _map->getMap()->tile[_player->getDir()->position->y * _map->getMap()->width
				   + (_player->getDir()->position->x - 1)] != arcade::TileType::BLOCK)
    return (event);
  else if (event == arcade::CommandType::GO_RIGHT
	   && _map->getMap()->tile[_player->getDir()->position->y * _map->getMap()->width
				   + (_player->getDir()->position->x + 1)] != arcade::TileType::BLOCK)
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

Character		*arcade::Nibbler::getCharacter()
{
  return (_player);
}

Map			*arcade::Nibbler::getMap()
{
  return (_map);
}

arcade::CommandType		arcade::Nibbler::run(IGraphics *lib)
{
  arcade::CommandType		ret = arcade::CommandType::UNDEFINED;

  lib->loadAssets("snake");
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
    managePowerUp();
    lib->displayMap(_map->getMap(),
		    _score, _player->getDir()->position[0].x,
		    _player->getDir()->position[0].y);
  }
  return (ret);
}

extern "C" void		Play()
{
  static int		i = 0;
  arcade::CommandType 	ret = arcade::CommandType::UNDEFINED;
  uint16_t		tmp;
  arcade::CommandType	command;
  arcade::CommandType	to_go;
  arcade::Nibbler	*_new;

  if (i == 0)
  {
    _new = new arcade::Nibbler(20, 10);
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
      std::cout.write(reinterpret_cast<char *>(_new->getPlayer()->getDir()), sizeof(struct arcade::WhereAmI) + _new->getPlayer()->getDir()->lenght * sizeof(struct arcade::Position));
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

extern "C" arcade::Nibbler *getLib()
{
  std::cout <<"Loading Nibbler..." << std::endl;
  arcade::Nibbler	*_new = new arcade::Nibbler(80, 40);
  return (_new);
}