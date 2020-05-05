//
// Pacman.hpp for Pacman in /home/tekm/tek2/cpp_arcade/games/pacman
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Thu Apr  6 17:02:38 2017 leroy_0
// Last update Thu Apr  6 17:02:39 2017 leroy_0
//

#ifndef __PACMAN_HPP_
#define __PACMAN_HPP_

#include <ctime>
#include <vector>
#include "PacEnnemy.h"
#include "IGame.hpp"
#include "Map.hpp"
#include "Character.hpp"
#include "Pacmap.hpp"

namespace arcade
{
  class Pacman : public IGame
  {
  public:
    Pacman(const std::string & mapname);

    virtual ~Pacman() {};

    Pacmap *getMap();
    arcade::CommandType analyseEvent(arcade::CommandType event);
    void manageDir(arcade::CommandType, arcade::CommandType *);
    void manageLenght();
    void managePowerUp();
    Character 		*getPlayer();
    bool        didIWin();
    CommandType run(IGraphics *);
    int _score;    

  private:
    time_t    _start;
    bool      _powerup;
    Character *_player;
    Pacmap    *_map;
    std::vector<arcade::PacEnnemy>  _ghost;
  };
};

#endif
