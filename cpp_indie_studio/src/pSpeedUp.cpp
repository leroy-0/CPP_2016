//
// pSpeedUp.cpp for pSpeedUp in /home/tekm/tek2/cpp_indie_studio
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Thu Jun 15 17:17:24 2017 leroy_0
// Last update Sun Jun 18 21:32:26 2017 Adrien Bachelet
//

#include		"pSpeedUp.hpp"

IndieGame::pSpeedUp::pSpeedUp(const std::string & name, Ogre::Entity * ent, Ogre::SceneNode* node, const OIS::KeyCode dir)
  : Powerup(name, ent, node, dir)
{
  _speedx = 2;
  _speedy = 2;
}

IndieGame::pSpeedUp::~pSpeedUp()
{
  
}
