/*
** PacEnnemy.h for pacenemy in /home/tekm/tek2/cpp_arcade
** 
** Made by leroy_0
** Login   <maxime.leroy@epitech.eu>
** 
** Started on  Tue Apr 6 18:47:04 2017 leroy_0
** Last update Tue Apr 6 18:47:05 2017 leroy_0
*/

#ifndef PROJECT_PACENNEMY_H
#define PROJECT_PACENNEMY_H

#include "Pacmap.hpp"
#include "Protocol.hpp"

namespace arcade {
  class PacEnnemy {
  public:
      enum ennemy_direction
      {
          DOWN = 0,
          UP = 1,
          LEFT = 2,
          RIGHT = 3,
          NONE = 4
      };
  private:
      Pacmap *_map;
      int   x;
      int   y;
      long  savedTime;
      bool  pacmanKilled;
      arcade::TileType  previousType;
      enum  ennemy_direction    previousDir;

      bool      isOutofSpawn();
      void      getOutofHell();
      void      move(arcade::PacEnnemy::ennemy_direction dir, arcade::TileType oldType);
      bool                CheckTile(ennemy_direction dir);
      bool        checkPreviousDir(enum ennemy_direction);
      enum ennemy_direction   generateRand();
  public:
      PacEnnemy(Pacmap *_map, int x, int y);
      virtual               ~PacEnnemy(){};

      arcade::Position      getDir() const;
      void                  setPos(int newx, int newy);      
      int                   run();
  };
};

#endif //PROJECT_PACENNEMY_H
