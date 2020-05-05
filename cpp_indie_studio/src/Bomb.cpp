//
// Bomb.cpp for Bomb in /home/tekm/tek2/cpp_indie_studio
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Wed May 31 13:36:07 2017 leroy_0
// Last update Sun Jun 18 17:12:50 2017 yan
//

#include "Bomb.hpp"

IndieGame::Bomb::Bomb(const std::string & name, Ogre::Entity * ent, Ogre::SceneNode* node, const OIS::KeyCode dir)
: Entity(name, ent, node, dir)
{
  float		x = 0;

  _start = std::time(NULL);
  while (x < static_cast<float>(BOMB_TIMER)) {
    _bombUpTimer.push_back(Ogre::Vector3(x, x + 0.01, 0));
    x += 0.01;
  }
}

IndieGame::Bomb::~Bomb()
{

}

void		IndieGame::Bomb::bombUp()
{
  for (auto it = _bombUpTimer.begin(); it < _bombUpTimer.end(); ++it) {
    if ((*it).z == 0)
    {
      addScale(Ogre::Vector3(SCALE_ADD_BOMB, SCALE_ADD_BOMB, SCALE_ADD_BOMB));
      (*it).z = 1;
      break;
    }
  }
}

void 		IndieGame::Bomb::addScale(const Ogre::Vector3 to_add)
{
  Ogre::Vector3 newScale;

  newScale.x = oNode->getScale().x + to_add.x;
  newScale.y = oNode->getScale().y + to_add.y;
  newScale.z = oNode->getScale().z + to_add.z;
  oNode->setScale(newScale);
}

const std::vector<Ogre::Vector3> 	IndieGame::Bomb::destruction(IndieGame::Map *map, int range, std::vector<Ogre::Vector3> *fire_tiles, Ogre::Vector3 player_pos)
{
  std::vector<Ogre::Vector3> 		destroyed;
  int 							x = map->getMapPosX(oNode->getPosition().x) - BOMB_RANGE - range;
  int 							y = map->getMapPosY(oNode->getPosition().z);
  int 							delimx = map->getMapPosX(oNode->getPosition().x) + BOMB_RANGE + range;
  int 							delimy = map->getMapPosY(oNode->getPosition().z) + BOMB_RANGE + range;
  int 							check = map->getMapPosX(oNode->getPosition().x);
  int 							inc = 0;

  while (check > x)
  {
    if (map->getMap()[y][check] == 3)
      x = check;
    check--;
  }
  check = map->getMapPosX(oNode->getPosition().x);
  while (check < delimx)
  {
    if (map->getMap()[y][check] == 3)
      delimx = check;
    check++;
  }
  while (x <= delimx)
    {
      if (x >= 0 && x < map->getWidth())
	{
	  if (map->getMap()[y][x] == 1 || map->getMap()[y][x] == 2 || map->getMap()[y][x] == 4)
	    {
	      destroyed.push_back(Ogre::Vector3(x, 0, y));
	      map->getMap()[y][x] = 0;
	      inc++;
	    }
	  fire_tiles->push_back(Ogre::Vector3(x, 0, y));
	}
      x++;
    }
  x = map->getMapPosX(oNode->getPosition().x);
  y = map->getMapPosY(oNode->getPosition().z) - BOMB_RANGE - range;
  check = map->getMapPosY(oNode->getPosition().z);
  while (check > y)
  {
    if (map->getMap()[check][x] == 3)
      y = check;
    check--;
  }
  check = map->getMapPosY(oNode->getPosition().z);
  while (check < delimy)
  {
    if (map->getMap()[check][x] == 3)
      delimy = check;
    check++;
  }
  while (y <= delimy)
    {
      if (y >= 0 && y < map->getHeight())
	{
	  if (map->getMap()[y][x] == 1 || map->getMap()[y][x] == 2 || map->getMap()[y][x] == 4)
	    {
	      destroyed.push_back(Ogre::Vector3(x, 0, y));
	      map->getMap()[y][x] = 0;
	      inc++;
	    }
	  fire_tiles->push_back(Ogre::Vector3(x, 0, y));
	}
      y++;
    }
  if (map->getMapPosX(player_pos.x) == map->getMapPosX(getPosition().x) && map->getMapPosY(player_pos.z) == map->getMapPosY(getPosition().z)) {
    destroyed.push_back(Ogre::Vector3(map->getMapPosX(player_pos.x), 0,
				      map->getMapPosY(player_pos.z)));
    map->getMap()[map->getMapPosY(player_pos.z)][map->getMapPosX(player_pos.x)] = 0;
  }
  return (destroyed);
}

void    IndieGame::Bomb::searchAndDestroyWalls(Ogre::SceneManager *pSceneManager, IndieGame::Map *map, std::vector<IndieGame::Entity *> *entities, const Ogre::Vector3 pos)
{
  int   i,j;

  for (auto wit = entities->begin(); wit < entities->end(); wit++)
  {
    i = map->getMapPosX((*wit)->getPosition().x);
    j = map->getMapPosY((*wit)->getPosition().z);
    if (pos.x == i && pos.z == j)
    {
      map->getMap()[j][i] = 0;
      (*wit)->destroy(pSceneManager);
      entities->erase(wit);
      return ;
    }
  }
}

bool    IndieGame::Bomb::searchAndDestroyPlayers(Ogre::SceneManager *pSceneManager, IndieGame::Map *map, std::vector<IndieGame::Player *> *entities, const Ogre::Vector3 pos, const Ogre::Vector3 playerPos)
{
  int   i,j;
  int   k,l;
  bool  dead = false;

  k = map->getMapPosX(playerPos.x);
  l = map->getMapPosY(playerPos.z);
  for (auto wit = entities->begin(); wit < entities->end(); wit++)
  {
    i = map->getMapPosX((*wit)->getPosition().x);
    j = map->getMapPosY((*wit)->getPosition().z);
    if (pos.x == i && pos.z == j)
    {
      if (pos.x == k && pos.z == l)
        dead = true;
      else
      {
        (*wit)->destroy(pSceneManager);
        entities->erase(wit);
      }
    }
  }
  return (dead);
}

void    IndieGame::Bomb::searchAndDestroyPowerUps(Ogre::SceneManager *pSceneManager, IndieGame::Map *map, IndieGame::PowerUpManager *powerUpManager, const Ogre::Vector3 pos)
{
  std::vector<IndieGame::Powerup *>   entities;
  int   i,j;

  entities = powerUpManager->getAll();
  for (auto wit = entities.begin(); wit < entities.end(); wit++)
  {
    i = map->getMapPosX((*wit)->getPosition().x);
    j = map->getMapPosY((*wit)->getPosition().z);
    if (pos.x == i && pos.z == j)
    {
      powerUpManager->erase(pSceneManager, map, *wit);
      return ;
    }
  }
}

bool 			IndieGame::Bomb::checkTimer() const
{
  if (std::time(NULL) - _start >= BOMB_TIMER)
    return (true);
  return (false);
}
