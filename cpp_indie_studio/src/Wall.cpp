//
// Wall.cpp for Wall in /home/tekm/tek2/cpp_indie_studio
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Wed May 31 14:09:36 2017 leroy_0
// Last update Wed May 31 14:09:37 2017 leroy_0
//

#include "Wall.hpp"

IndieGame::Wall::Wall(const std::string & name, Ogre::Entity * ent, Ogre::SceneNode* node, const OIS::KeyCode dir)
: Entity(name, ent, node, dir)
{
}

IndieGame::Wall::~Wall()
{

}