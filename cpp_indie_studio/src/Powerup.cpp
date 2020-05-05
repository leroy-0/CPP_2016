//
// Powerup.cpp for Powerup in /home/tekm/tek2/cpp_indie_studio
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Wed May 31 13:36:34 2017 leroy_0
// Last update Sun Jun 18 21:30:02 2017 Adrien Bachelet
//

#include		"Powerup.hpp"

IndieGame::Powerup::Powerup(const std::string & name, Ogre::Entity * ent, Ogre::SceneNode* node, const OIS::KeyCode dir)
: Entity(name, ent, node, dir)
{
  _speedx = 0;
  _speedy = 0;
  _limitBomb = 0;
  _bombRange = 0;
}

IndieGame::Powerup::~Powerup()
{

}

int			IndieGame::Powerup::getSpeedX() const
{
  return (_speedx);
}

int			IndieGame::Powerup::getSpeedY() const
{
  return (_speedy);
}

int			IndieGame::Powerup::getLimitBomb() const
{
  return (_limitBomb);
}

int			IndieGame::Powerup::getBombRange() const
{
  return (_bombRange);
}
