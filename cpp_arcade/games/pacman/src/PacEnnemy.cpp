/*
** PacEnnemy.cpp for cpp_arcade in /home/kleinh/Documents/cpp_arcade/games/pacman/src/PacEnnemy.cpp
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Sat Apr 08 19:55:25 2017 Arthur Klein
** Last update Sat Apr 08 19:55:26 2017 Arthur Klein
*/

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include "Pacmap.hpp"
#include "PacEnnemy.h"

arcade::PacEnnemy::PacEnnemy(Pacmap *map, int _x, int _y)
{
    this->_map = map;
    this->x = _x;
    this->y = _y;
    _map->getMap()->tile[this->y * _map->getMap()->width + this->x] = arcade::TileType::EVIL_DUDE;
    this->pacmanKilled = false;
    this->savedTime = std::time(NULL);
}

arcade::Position            arcade::PacEnnemy::getDir() const
{
    arcade::Position        pos;

    pos.x = x;
    pos.y = y;
    return (pos);
}

void                        arcade::PacEnnemy::setPos(int newx, int newy)
{
    x = newx;
    y = newy;
}

bool        arcade::PacEnnemy::isOutofSpawn()
{
    if (this->x >= 9 && this->x <= 11 && (this->y == 12 || this->y == 13 || this->y == 11))
        return (false);
    return (true);
}

bool        arcade::PacEnnemy::CheckTile(enum ennemy_direction dir)
{
    int     obj_x = this->x;
    int     obj_y = this->y;
    arcade::TileType    type;

    if (dir == RIGHT)
        obj_x++;
    else if (dir == LEFT)
        obj_x--;
    else if (dir == UP)
        obj_y--;
    else if (dir == DOWN)
        obj_y++;
    else
        return false;
    type = this->_map->getTypeTilefromPos(obj_x, obj_y);
    if (type == arcade::TileType::POWERUP || type == arcade::TileType::OTHER || type == arcade::TileType::PLAYER
        || type == arcade::TileType::EMPTY)
        return (true);
    return (false);
}

void        arcade::PacEnnemy::move(arcade::PacEnnemy::ennemy_direction dir, arcade::TileType oldType)
{
    if (oldType == arcade::TileType::PLAYER)
        oldType = arcade::TileType::EMPTY;
    if (dir == UP)
    {
        this->previousType = this->_map->getMap()->tile[(this->y - 1) * this->_map->getMap()->width + this->x];
        this->previousDir = dir;
        this->_map->getMap()->tile[(this->y - 1) * this->_map->getMap()->width + this->x] = arcade::TileType::EVIL_DUDE;
        this->_map->getMap()->tile[(this->y) * this->_map->getMap()->width + this->x] = oldType;
        this->y--;
    }
    else if (dir == DOWN)
    {
        this->previousType = this->_map->getMap()->tile[(this->y + 1) * this->_map->getMap()->width + this->x];
        this->previousDir = dir;
        this->_map->getMap()->tile[(this->y + 1) * this->_map->getMap()->width + this->x] = arcade::TileType::EVIL_DUDE;
        this->_map->getMap()->tile[(this->y) * this->_map->getMap()->width + this->x] = oldType;
        this->y++;
    }
    else if (dir == LEFT)
    {
        this->previousType = this->_map->getMap()->tile[(this->y) * this->_map->getMap()->width + (this->x - 1)];
        this->previousDir = dir;
        this->_map->getMap()->tile[(this->y) * this->_map->getMap()->width + (this->x - 1)] = arcade::TileType::EVIL_DUDE;
        this->_map->getMap()->tile[(this->y) * this->_map->getMap()->width + this->x] = oldType;
        this->x--;
    }
    else if (dir == RIGHT)
    {
        this->previousType = this->_map->getMap()->tile[this->y * this->_map->getMap()->width + (this->x + 1)];
        this->previousDir = dir;
        this->_map->getMap()->tile[this->y * this->_map->getMap()->width + (this->x + 1)] = arcade::TileType::EVIL_DUDE;
        this->_map->getMap()->tile[(this->y) * this->_map->getMap()->width + this->x] = oldType;
        this->x++;
    }
}

void        arcade::PacEnnemy::getOutofHell()
{
    int     objectif_x = 10;
    int     objectif_y = 9;

    ennemy_direction    dir = NONE;


    if (this->y > objectif_y)
    {
        if (this->CheckTile(UP))
            dir = UP;
    }
    if (this->x > objectif_x && dir == NONE)
    {
        if (this->CheckTile(LEFT))
            dir = LEFT;
    }
    if (this->x < objectif_x && dir == NONE)
    {
        if (this->CheckTile(RIGHT))
            dir = RIGHT;
    }
    this->move(dir, arcade::TileType::EMPTY);
}

bool        arcade::PacEnnemy::checkPreviousDir(enum ennemy_direction dir)
{
    if (this->previousDir == UP && dir == DOWN)
    {
        if (this->_map->getTypeTilefromPos(this->x, this->y - 1) == arcade::TileType::EVIL_DUDE)
            return (true);
        return (false);
    }
    if (this->previousDir == DOWN && dir == UP)
    {
        if (this->_map->getTypeTilefromPos(this->x, this->y + 1) == arcade::TileType::EVIL_DUDE)
            return (true);
        return (false);
    }
    if (this->previousDir == LEFT && dir == RIGHT)
    {
        if (this->_map->getTypeTilefromPos(this->x - 1, this->y) == arcade::TileType::EVIL_DUDE)
            return (true);
        return (false);
    }
    if (this->previousDir == RIGHT && dir == LEFT)
    {
        if (this->_map->getTypeTilefromPos(this->x + 1, this->y) == arcade::TileType::EVIL_DUDE)
            return (true);
        return (false);
    }
    return (true);
}

enum arcade::PacEnnemy::ennemy_direction   arcade::PacEnnemy::generateRand()
{
    unsigned int    randdir = 0;
    ennemy_direction dir = NONE;

    randdir = (std::rand()) % 4;
    switch (randdir) {
        case 0 :
            dir = DOWN;
            break;
        case 1 :
            dir = UP;
            break;
        case 2 :
            dir = LEFT;
            break;
        case 3 :
            dir = RIGHT;
            break;
        default:
            dir = NONE;
            break;
    }
    return (dir);
}

int         arcade::PacEnnemy::run()
{
    ennemy_direction dir = NONE;

    if (this->_map->getTypeTilefromPos(this->x, this->y) == arcade::TileType::PLAYER)
        return (0);
    if ((std::time(NULL) - this->savedTime) < 10)
        return (1);
    if (!this->isOutofSpawn())
        this->getOutofHell();
    else
    {
        if (this->CheckTile(previousDir))
        {
            this->move(previousDir, this->previousType);
        }
        else
        {
            dir = this->generateRand();
            if (this->checkPreviousDir(dir))
            {
                if (this->CheckTile(dir))
                {
                    this->move(dir, this->previousType);
                }
            }
        }
    }
    if (this->_map->getTypeTilefromPos(this->x, this->y) == arcade::TileType::PLAYER)
        return (0);
    return (1);
}