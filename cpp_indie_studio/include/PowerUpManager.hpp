//
// PowerUpManager.hpp for PowerUpManager in /home/tekm/tek2/cpp_indie_studio
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Thu Jun 15 19:17:36 2017 leroy_0
// Last update Sun Jun 18 21:35:37 2017 longle_h
//

#ifndef				__POWERUPMANAGER_HPP__
#define				__POWERUPMANAGER_HPP__

#include			"Powerup.hpp"
#include			"pSpeedUp.hpp"
#include			"pSpeedDown.hpp"
#include			"pBombUp.hpp"
#include			"pBombDown.hpp"
#include			"pBombRangeUp.hpp"
#include			"pBombRangeDown.hpp"

namespace			IndieGame
{
  class				PowerUpManager
  {
  public:
				PowerUpManager();
				virtual ~PowerUpManager();

  public:
    std::vector<IndieGame::Powerup *>	getAll() const;
    void				clear(Ogre::SceneManager *pSceneManager);
    void				erase(Ogre::SceneManager *pSceneManager, IndieGame::Map *map, IndieGame::Powerup *powerup);
    bool				managePowerUps(Ogre::SceneManager *pSceneManager, IndieGame::Input *input, IndieGame::EntityManager *entityManager, IndieGame::Map *map, std::vector<Ogre::Vector3>  powerups);
    void				initPowerUps(Ogre::SceneManager *pSceneManager, IndieGame::Input *input, IndieGame::EntityManager *entityManager, IndieGame::Map *map, int nb);

  private:
    std::vector<IndieGame::Powerup *> 	_powerups;
    int 				_nbPowerups;
    int					_activePowerups;
  };
};

#define					RAND_VALUE 			(2)

#endif					/* __POWERUPMANAGER_HPP__ */
