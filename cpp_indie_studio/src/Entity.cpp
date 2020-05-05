//
// Entity.cpp for Entity in /home/tekm/tek2/cpp_indie_studio
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Thu Jun 15 18:23:23 2017 leroy_0
// Last update Fri Jun 16 18:06:26 2017 yan
//

#include	"Entity.hpp"

using namespace IndieGame;

Entity::Entity(const std::string &name, Ogre::Entity * ent, Ogre::SceneNode *node, const OIS::KeyCode default_dir)
{
  this->name = name;
  this->oEntity = ent;
  this->oNode = node;
  this->_currentDir = default_dir;
  this->iterator = 0;
  this->limit = 0;
  this->to_add = 0;
}

Entity::~Entity()
{

}

void	  Entity::unHide()
{
  setPosition(Ogre::Vector3(getPosition().x, 70, getPosition().z));
}

void	  Entity::hide()
{
  setPosition(Ogre::Vector3(getPosition().x, -400, getPosition().z));
}

void      Entity::destroy(Ogre::SceneManager *manager)
{
  this->oNode->detachAllObjects();
  manager->getRootSceneNode()->removeAndDestroyChild(oNode->getName());
  manager->destroyEntity(oEntity);
}

std::string Entity::getName() const
{
  return this->name;
}

Ogre::Entity* Entity::getEntity() const
{
  return this->oEntity;
}

Ogre::SceneNode* Entity::getNode() const
{
  return this->oNode;
}

const Ogre::Vector3 &Entity::getPosition() const
{
  return (oNode->getPosition());
}

Ogre::Vector3 Entity::getSize() const
{
  return (oEntity->getBoundingBox().getSize());
}

void	Entity::setPosition(const Ogre::Vector3 & pos)
{
  this->oNode->setPosition(pos.x, oEntity->getBoundingBox().getSize().y * (1.0f - Ogre::MeshManager::getSingleton().getBoundsPaddingFactor()) + pos.y, pos.z);
}

OIS::KeyCode	Entity::getDir() const
{
  return this->_currentDir;
}

bool Entity::goTo(IndieGame::Map *map, IndieGame::Input *inputManager, OIS::KeyCode dir)
{
  if (inputManager->getKeyDown("escape") == dir && limit == 0)
    return (true);
  if (dir == inputManager->getKeyDown(getName() + std::string("_up")) || dir == inputManager->getKeyDown(getName() + std::string("_left")))
    to_add = -2;
  else if (dir == inputManager->getKeyDown(getName() + std::string("_right")) || dir == inputManager->getKeyDown(getName() + std::string("_down")))
    to_add = 2;

  if (_currentDir == inputManager->getKeyDown("unknown") && (((dir == inputManager->getKeyDown(getName() + std::string("_up")) || dir == inputManager->getKeyDown(getName() + std::string("_down")))
    && map->getMap()[map->getMapPosY(getPosition().z) + (to_add < 0 ? -1 : 1)][map->getMapPosX(getPosition().x)] == 0)
    || ((dir == inputManager->getKeyDown(getName() + std::string("_right")) || dir == inputManager->getKeyDown(getName() + std::string("_left")))
	&& map->getMap()[map->getMapPosY(getPosition().z)][map->getMapPosX(getPosition().x) + (to_add < 0 ? -1 : 1)] == 0)))
    _currentDir = dir;
  if (_currentDir == inputManager->getKeyDown("unknown"))
    return (true);

  limit = RATIO_MAP;
  if (iterator < limit)
  {
    if (_currentDir == inputManager->getKeyDown(getName() + std::string("_up")) || _currentDir == inputManager->getKeyDown(getName() + std::string("_down")))
      setPosition(Ogre::Vector3(getPosition().x, 0, getPosition().z + to_add));
    else if (_currentDir == inputManager->getKeyDown(getName() + std::string("_right")) || _currentDir == inputManager->getKeyDown(getName() + std::string("_left")))
      setPosition(Ogre::Vector3(getPosition().x + to_add, 0, getPosition().z));
    iterator += (to_add < 0 ? to_add * -1 : to_add);
    return (false);
  }
  iterator = 0;
  limit = 0;
  to_add = 0;
  _currentDir = inputManager->getKeyDown("unknown");
  return (true);
}
