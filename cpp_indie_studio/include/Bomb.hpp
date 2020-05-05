//
// Bomb.hpp for Bomb in /home/tekm/tek2/cpp_indie_studio
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Wed May 31 13:35:49 2017 leroy_0
// Last update Sun Jun 18 15:45:52 2017 yan
//

#ifndef				__BOMB_HPP_
#define				__BOMB_HPP_

#include			<OGRE/OgreRoot.h>
#include			<OGRE/OgreRenderWindow.h>
#include			<OGRE/Ogre.h>
#include			<OIS/OIS.h>
#include			<iostream>

#include			"PowerUpManager.hpp"
#include			"Player.hpp"
#include			"Map.hpp"

namespace			IndieGame
{
  class				Player;

  class Bomb : public IndieGame::Entity
  {
  public:
    Bomb(const std::string & name, Ogre::Entity * ent, Ogre::SceneNode* node, const OIS::KeyCode dir);
    virtual ~Bomb();

  public:
    const std::vector<Ogre::Vector3>	destruction(IndieGame::Map *map, int range, std::vector<Ogre::Vector3> *fire_tiles, Ogre::Vector3 player_pos);
    void				searchAndDestroyWalls(Ogre::SceneManager *pSceneManager, IndieGame::Map *map, std::vector<IndieGame::Entity *> *entities, const Ogre::Vector3 pos);
    void				searchAndDestroyPowerUps(Ogre::SceneManager *pSceneManager, IndieGame::Map *map, IndieGame::PowerUpManager *powerUpManager, const Ogre::Vector3 pos);
    bool				searchAndDestroyPlayers(Ogre::SceneManager *pSceneManager, IndieGame::Map *map, std::vector<IndieGame::Player *> *entities, const Ogre::Vector3 pos, const Ogre::Vector3 playerPos);
    bool				checkTimer() const;
    void				addScale(const Ogre::Vector3 to_add);
    void				bombUp();
  private:
    int					_start;
    std::vector<Ogre::Vector3>		_bombUpTimer;
  };
};

#define		BOMB_MESH		"bomb.mesh"
#define		BOMB_LIMIT		(1)
#define		BOMB_RANGE		(1)
#define		BOMB_TIMER		(3)
#define		SCALE_ADD_BOMB		(0.003)

#endif					/* __BOMB_HPP__ */
