//
// EntityManager.hpp for EntityManager in /home/tekm/tek2/cpp_indie_studio
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Thu Jun 15 13:04:58 2017 leroy_0
// Last update Sun Jun 18 14:30:14 2017 yan
//

#ifndef				__ENTITYMANAGER_HPP__
#define				__ENTITYMANAGER_HPP__

#include			"Entity.hpp"

namespace			IndieGame
{
  class				EntityManager
  {
  public:
    EntityManager();
    virtual ~EntityManager();

  public:
    template <class T>IndieGame::Entity	*createEntity(Ogre::SceneManager *pSceneManager, IndieGame::Input *input, const std::string & name, const std::string &mesh, const Ogre::Vector3 & pos)
    {
      Ogre::Entity		*ent;
      Ogre::SceneNode		*node;

      ent = pSceneManager->createEntity(name, mesh);
      node = pSceneManager->getRootSceneNode()->createChildSceneNode(name);
      node->setPosition(pos.x, ent->getBoundingBox().getSize().y *
			(1.0f - Ogre::MeshManager::getSingleton().getBoundsPaddingFactor()), pos.z);
      node->attachObject(ent);
      if (name.find("Wall") == 0)
	node->scale(35,35,35);
      if (name.find("Powerup") == 0)
	{
	  node->scale(12,12,12);
	  node->rotate(Ogre::Quaternion(Ogre::Degree(200), Ogre::Vector3::UNIT_Y));
	  node->setPosition(pos.x, ent->getBoundingBox().getSize().y *
			    (1.0f - Ogre::MeshManager::getSingleton().getBoundsPaddingFactor()) + 70, pos.z);
	}
      if (name.find("Player") == 0)
	node->scale(0.7, 0.7, 0.7);
      if (name.find("Bomb") == 0)
	{
	  node->scale(1.1, 1.1, 1.1);
	  node->rotate(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::UNIT_Z));
	  node->rotate(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::UNIT_Y));
	}
      return (new T(name, ent, node, input->getKeyDown("unknown")));
    }
  };
};

#endif				/* __ENTITYMANAGER_HPP__ */
