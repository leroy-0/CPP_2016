//
// Bomberman.hpp for Bomberman in /home/tekm/tek2/cpp_indie_studio
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Thu May  4 00:23:25 2017 leroy_0
// Last update Sun Jun 18 20:25:48 2017 yan
//

#ifndef					__BOMBERMAN_HPP__
#define					__BOMBERMAN_HPP__

#include				<OGRE/OgreRoot.h>
#include 				<OGRE/OgreRenderWindow.h>
#include 				<OGRE/Ogre.h>
#include 				<irrKlang.h>
#include 				<OIS/OIS.h>
#include 				<boost/thread.hpp>
#include 				<iostream>
#include 				<vector>
#include 				<chrono>

#include 				"Save.hpp"
#include 				"Map.hpp"
#include 				"Player.hpp"
#include 				"Wall.hpp"
#include 				"Bomb.hpp"
#include 				"Explosion.hpp"
#include 				"GUI.hpp"
#include 				"Entity.hpp"
#include 				"Input.hpp"
#include 				"PowerUpManager.hpp"
#include 				"EntityManager.hpp"

namespace				IndieGame
{
  class Bomberman:			public Ogre::FrameListener, public Ogre::WindowEventListener
  {
  public:
    OIS::Keyboard			*_pKeyboard;
    OIS::Mouse				*_pMouse;
    Bomberman();
    virtual ~Bomberman();

    bool				start();
    void				run();
    void				exit();
    void				createPlayer(const Ogre::String & name);
    bool				createMap(const Ogre::String & name);
    void				loadRessources(const Ogre::String pResourceFilename);
    bool				chooseIA();
    void				initOgre();
    void				initOIS();
    bool				pause();
    bool				loadGame();
    bool				menu();
    bool				choosePlayer();
    bool				game();
    bool				option();

    void				loadBackground(const Ogre::String & name);

    bool				frameStarted(const Ogre::FrameEvent &evt);
    bool				frameEnded(const Ogre::FrameEvent &evt);

    std::vector<OIS::KeyCode>		manageInput();

    bool				displayMap();

    bool				manageGame();
    bool				restartGame();
    bool				startGameWithParameters(const std::string & file);
    void				loadPlayerConfiguration(const std::string & file);
    void				createPlayers(int nb);
    void				runThread();
    void				createExplosions(std::vector<Ogre::Vector3> *fire_tiles);
    void				manageExplosions();
    void				print(IndieGame::Map *map) const;
    bool				loadSplash(const std::string & name);
    void				bzeroMap();
    bool				splashScreen(const std::string & name);


  private:
    Ogre ::Root*			_pRoot;
    Ogre ::SceneManager*		_pSceneManager;
    Ogre ::RenderWindow*		_pRenderWindow;
    Ogre ::Viewport*			_pViewport;
    Ogre ::Camera*			_pCamera;

    Ogre::Light* 			_pLight;
    Ogre::Entity* 			_pGroundEntity;

    OIS::InputManager 			*_pInputManager;
    Save				*_save;
    GUI					*_gui;

  private:
    IndieGame::EntityManager		*_entityManager;
    IndieGame::PowerUpManager		*_powerUpManager;
    IndieGame::Input			*_input;
    IndieGame::Map			*_map;
    std::vector<IndieGame::Player *>	_players;
    std::vector<IndieGame::Entity *> 	_wall;
    std::vector<IndieGame::Entity *> 	_wall_undestructible;
    std::vector<IndieGame::Explosion *>	_explosion;
    int					_explosion_count;
    irrklang::ISoundEngine		*_soundEngine;
    irrklang::ISoundSource		*_baseSound;
    irrklang::ISoundSource		*_gameSound;
    irrklang::ISoundSource		*_splashSound;
    std::vector<OIS::KeyCode>		_splashScreen;
    IndieGame::Entity			*_splash;
    unsigned int			_start;
  };
};

#define		DEFAULT_SPLASH		"config/splash.cfg"
#define		DEFAULT_RESSOURCES	"bin/ressources.cfg"
#define		DEFAULT_INPUT		"config/input.cfg"
#define		MAP_DIR			"config/maps/"
#define		WAIT_FOR_AUTOSAVE	(10)

#define		DEFAULT_PLAYERNAME	"Player_"

#endif					/* __BOMBERMAN_HPP__ */
