//
// PowerUpManager.cpp for PowerUpManager in /home/tekm/tek2/cpp_indie_studio
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Thu Jun 15 19:17:22 2017 leroy_0
// Last update Sat Jun 17 20:06:30 2017 yan
//

#include 	"PowerUpManager.hpp"

IndieGame::PowerUpManager::PowerUpManager()
{
  _nbPowerups = 0;
  _activePowerups = 0;
}

IndieGame::PowerUpManager::~PowerUpManager()
{

}

void		IndieGame::PowerUpManager::initPowerUps(Ogre::SceneManager *pSceneManager, IndieGame::Input *input, IndieGame::EntityManager *entityManager, IndieGame::Map *map, int nb)
{
  Ogre::Vector3         pos;
  int			x;
  int			y;
  int			cmp;

  for (int i = 0; i < nb; ++i)
  {
    x = -10;
    y = -10;
    pos.x = map->getWorldPosX(x);
    pos.z = map->getWorldPosY(y);
    _nbPowerups++;
    cmp = std::rand() % 100;
    if (cmp <= 15)
      _powerups.push_back(dynamic_cast<IndieGame::Powerup *>(entityManager->createEntity<IndieGame::pSpeedUp>(pSceneManager, input, std::string("Powerup") + std::to_string(_nbPowerups), "pringle_green.mesh", pos)));
    else if (cmp <= 31)
      _powerups.push_back(dynamic_cast<IndieGame::Powerup *>(entityManager->createEntity<IndieGame::pSpeedDown>(pSceneManager, input, std::string("Powerup") + std::to_string(_nbPowerups), "pringle_green_down.mesh", pos)));
    else if (cmp <= 47)
      _powerups.push_back(dynamic_cast<IndieGame::Powerup *>(entityManager->createEntity<IndieGame::pBombUp>(pSceneManager, input, std::string("Powerup") + std::to_string(_nbPowerups), "pringle_blue.mesh", pos)));
    else if (cmp <= 64)
      _powerups.push_back(dynamic_cast<IndieGame::Powerup *>(entityManager->createEntity<IndieGame::pBombDown>(pSceneManager, input, std::string("Powerup") + std::to_string(_nbPowerups), "pringle_blue_down.mesh", pos)));
    else if (cmp <= 80)
      _powerups.push_back(dynamic_cast<IndieGame::Powerup *>(entityManager->createEntity<IndieGame::pBombRangeDown>(pSceneManager, input, std::string("Powerup") + std::to_string(_nbPowerups), "pringle_pink_down.mesh", pos)));
    else
      _powerups.push_back(dynamic_cast<IndieGame::Powerup *>(entityManager->createEntity<IndieGame::pBombRangeUp>(pSceneManager, input, std::string("Powerup") + std::to_string(_nbPowerups), "pringle_pink.mesh", pos)));
    _powerups.back()->hide();
  }
}

bool            IndieGame::PowerUpManager::managePowerUps(Ogre::SceneManager *pSceneManager, IndieGame::Input *input, IndieGame::EntityManager *entityManager, IndieGame::Map *map, std::vector<Ogre::Vector3>  powerups)
{
  Ogre::Vector3         pos;
  int			x;
  int			y;

  if (_powerups.empty())
    initPowerUps(pSceneManager, input, entityManager, map, map->getHeight() * map->getWidth());
  for (unsigned int i = 0; i < powerups.size(); ++i) {
    x = powerups.at(i).x;
    y = powerups.at(i).z;
    pos.x = map->getWorldPosX(x);
    pos.y = 0;
    pos.z = map->getWorldPosY(y);
    if (std::rand() % RAND_VALUE == 0) {
      _powerups.at(_activePowerups)->setPosition(pos);
      _powerups.at(_activePowerups)->unHide();
      map->getMap()[y][x] = 4;
      _activePowerups++;
    }
  }
  return (true);
}


std::vector<IndieGame::Powerup *> 	IndieGame::PowerUpManager::getAll() const
{
  return (_powerups);
}

void 								IndieGame::PowerUpManager::erase(Ogre::SceneManager *pSceneManager, IndieGame::Map *map, IndieGame::Powerup *powerup)
{
  for (auto it = _powerups.begin(); it < _powerups.end(); ++it)
  {
    if ((*it)->getName() == powerup->getName())
    {
      powerup->destroy(pSceneManager);
      map->getMap()[map->getMapPosY(powerup->getPosition().z)][map->getMapPosX(powerup->getPosition().x)] = 0;
      _powerups.erase(it);
      _activePowerups--;
      return ;
    }
  }
}

void 							IndieGame::PowerUpManager::clear(Ogre::SceneManager *pSceneManager)
{
  for (auto it = _powerups.begin(); it < _powerups.end(); ++it)
    (*it)->destroy(pSceneManager);
  _powerups.clear();
  _nbPowerups = 0;
  _activePowerups = 0;
}
