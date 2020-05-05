//
// Explosion.hpp for Explosion in /home/yan/Documents/cpp/cpp_indie_studio
// 
// Made by yan
// Login   <yan.poinssot@epitech.eu>
// 
// Started on  Sun Jun 18 12:29:07 2017 yan
// Last update Sun Jun 18 17:13:45 2017 yan
//


#ifndef			__EXPLOSION_HPP_
#define			__EXPLOSION_HPP_

#include		<OGRE/OgreRoot.h>
#include		<OGRE/OgreRenderWindow.h>
#include		<OGRE/Ogre.h>
#include		<OIS/OIS.h>
#include		<iostream>
#include		<irrKlang.h>
#include		<ctime>
#include		"EntityManager.hpp"

namespace		IndieGame
{
  class			Explosion : public IndieGame::Entity
  {
  public:
    Explosion(const std::string & name, Ogre::Entity * ent, Ogre::SceneNode* node, const OIS::KeyCode dir);
    virtual ~Explosion();
    std::clock_t	getTime() const;
    void		dissapear();

  protected:
    std::clock_t	_start;
  };
};

#define			EX_DURATION (100)

#endif			/* __EXPLOSION_HPP__ */
