//
// Character.cpp for Character in /home/tekm/tek2/cpp_arcade/games/nibbler
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Tue Mar  7 15:46:22 2017 leroy_0
// Last update Tue Mar  7 15:46:23 2017 leroy_0
//
#include			<iostream>
#include			"Character.hpp"

Character::Character(uint16_t width, uint16_t height)
{
  _dir = reinterpret_cast<struct arcade::WhereAmI*>(new char[sizeof(struct arcade::WhereAmI)
							     + sizeof(arcade::Position) * (width * height)]);
  _dir->type = arcade::CommandType::GO_UP;
  _dir->lenght = 4;
  _dir->position[0].x = width;
  _dir->position[0].y = height;
  _dir->position[1].x = width;
  _dir->position[1].y = height + 1;
  _dir->position[2].x = width;
  _dir->position[2].y = height + 2;
  _dir->position[3].x = width;
  _dir->position[3].y = height + 3;

  _queue = new int[2];
  _queue[0] = _dir->position[3].x;
  _queue[1] = _dir->position[3].y + 1;

  _history = new arcade::CommandType[width * height];
  for (int i = 0; i < width * height; ++i)
  {
    if (i < _dir->lenght)
      _history[i] = arcade::CommandType::GO_UP;
    else
      _history[i] = arcade::CommandType::UNDEFINED;
  }
}

arcade::WhereAmI		*Character::getDir() const
{
  return (_dir);
}

int				*Character::getQueue() const
{
  return (_queue);
}

arcade::CommandType		*Character::getHistory() const
{
  return (_history);
}