//
// pBombDown.cpp for pBombDown in /home/tekm/tek2/cpp_indie_studio
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Thu Jun 15 17:17:24 2017 leroy_0
// Last update Thu Jun 15 17:17:26 2017 leroy_0
//

#include "pBombDown.hpp"

IndieGame::pBombDown::pBombDown(const std::string & name, Ogre::Entity * ent, Ogre::SceneNode* node, const OIS::KeyCode dir)
: Powerup(name, ent, node, dir)
{
	_limitBomb = -1;
}

IndieGame::pBombDown::~pBombDown()
{

}