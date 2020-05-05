//
// explosion.cpp for explosion in /home/yan/Documents/cpp/cpp_indie_studio
// 
// Made by yan
// Login   <yan.poinssot@epitech.eu>
// 
// Started on  Sun Jun 18 13:04:04 2017 yan
// Last update Sun Jun 18 14:16:33 2017 yan
//

#include <iostream>
#include "Bomberman.hpp"
#include "Bomb.hpp"
#include "Player.hpp"

IndieGame::Explosion::Explosion(const std::string & name, Ogre::Entity * ent, Ogre::SceneNode* node, const OIS::KeyCode dir)
  : Entity(name, ent, node, dir)
{
  _start = std::clock();
}

IndieGame::Explosion::~Explosion() { }

std::clock_t	IndieGame::Explosion::getTime() const
{
  return (_start);
}

void		IndieGame::Explosion::dissapear()
{
  
}
