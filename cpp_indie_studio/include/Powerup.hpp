//
// Powerup.hpp for Powerup in /home/tekm/tek2/cpp_indie_studio
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Wed May 31 13:36:17 2017 leroy_0
// Last update Wed May 31 13:36:18 2017 leroy_0
//

#ifndef			__POWERUP_HPP__
#define			__POWERUP_HPP__

#include		"EntityManager.hpp"

namespace		IndieGame
{
  class Powerup :	public IndieGame::Entity
  {
  public:
    Powerup(const std::string & name, Ogre::Entity * ent, Ogre::SceneNode* node, const OIS::KeyCode dir);
    virtual ~Powerup();

  public:
    int 		getSpeedX() const;
    int 		getSpeedY() const;
    int 		getLimitBomb() const;
    int 		getBombRange() const;

  protected:
    int 		_speedx;
    int 		_speedy;
    int 		_limitBomb;
    int 		_bombRange;
  };
};

#endif			/* __POWERUP_HPP__ */