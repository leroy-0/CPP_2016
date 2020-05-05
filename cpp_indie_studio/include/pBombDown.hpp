//
// pBombDown.hpp for pBombDown in /home/tekm/tek2/cpp_indie_studio
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Thu Jun 15 17:17:41 2017 leroy_0
// Last update Thu Jun 15 17:17:42 2017 leroy_0
//

#ifndef			__pBombDown_HPP__
#define			__pBombDown_HPP__

#include		"Entity.hpp"
#include		"Powerup.hpp"

namespace		IndieGame
{
  class pBombDown : public IndieGame::Powerup
  {
  public:
    pBombDown(const std::string & name, Ogre::Entity * ent, Ogre::SceneNode* node, const OIS::KeyCode dir);
    virtual ~pBombDown();
  };
};

#endif			/* __pBombDown_HPP__ */