/*
** Player.hpp for cpp_indie_studio in /home/bruere_s/Projets/cpp_indie_studio/include/Player.hpp
**
** Made by Sebastien Bruere
** Login   <sebastien.bruere@epitech.eu>
**
** Started on  Fri Jun 16 14:17:56 2017 Sebastien Bruere
// Last update Sun Jun 18 15:50:50 2017 yan
*/

#ifndef					__PLAYER_HPP_
#define					__PLAYER_HPP_

#include				<OGRE/OgreRoot.h>
#include				<OGRE/OgreRenderWindow.h>
#include				<OGRE/Ogre.h>
#include				<OIS/OIS.h>
#include				<iostream>
#include				<irrKlang.h>
#include				"EntityManager.hpp"
#include				"PowerUpManager.hpp"
#include				"Input.hpp"
#include				"Bomb.hpp"

namespace				IndieGame
{

  class					Bomb;
  class					Player : public IndieGame::Entity
  {
  public:
    Player(const std::string & name, Ogre::Entity * ent, Ogre::SceneNode* node, const OIS::KeyCode dir);
    virtual ~Player();

  public:
    bool 				isAlive() const;
    bool 				isBombReady() const;
    bool 	 			managePosition(IndieGame::Map *map, IndieGame::Input *input, std::vector<OIS::KeyCode> inputs);
    bool 				manageEvents(Ogre::SceneManager *pSceneManager, IndieGame::EntityManager *entityManager, IndieGame::Map *map, IndieGame::Input *input, std::vector<OIS::KeyCode> inputs);
    void 				manageOneBomb(Ogre::SceneManager *pSceneManager, IndieGame::EntityManager *entityManager, IndieGame::Map *map, IndieGame::Input *input);
    std::vector<Ogre::Vector3>		manageBombs(Ogre::SceneManager *pSceneManager, IndieGame::Map *map, std::vector<IndieGame::Entity *>  *walls, IndieGame::PowerUpManager *powerUpManager, std::vector<IndieGame::Player *>  *players, std::vector<Ogre::Vector3> *fire_tiles);
    bool 				managePowerups(Ogre::SceneManager *pSceneManager, IndieGame::PowerUpManager *powerUpManager, IndieGame::Map *map, IndieGame::Input *input, std::vector<OIS::KeyCode> inputs);
    void 				eatPowerup(IndieGame::Powerup *powerup);
    void 				destroyBombs(Ogre::SceneManager *pSceneManager);

    int					getLimitBomb() const;
    int					getactiveBomb() const;
    int					getBombRange() const;
    int					getSpeedX() const;
    int					getSpeedY() const;
    int					getIsAlive() const;
    Ogre::AnimationState *		getAnimation() const;
    void				setAnimation(Ogre::AnimationState *);
    bool				goTo(IndieGame::Map *map, IndieGame::Input *inputManager, OIS::KeyCode dir);
    void 				setOrientation(const Ogre::Vector3 to_look);
    bool				loadConfiguraton(const std::string & file);

  protected:
    std::vector<IndieGame::Bomb *>	_bomb;
    Ogre::AnimationState *		_animation;
    int 				_limitBomb;
    int 				_activeBombs;
    int 				_bombRange;
    int 				_speedx;
    int 				_speedy;
    bool 				_alive;
    irrklang::ISoundEngine		*_soundEngine;
    Ogre::Vector3			_oldPos;
    irrklang::ISoundSource		*_gameSound;
    irrklang::ISoundSource		*_deathSound;
  };
};

#define		Y_POS			(-170)
#define		SPEED_X			(5)
#define		SPEED_Y			(8)

#endif					/* __PLAYER_HPP__ */
