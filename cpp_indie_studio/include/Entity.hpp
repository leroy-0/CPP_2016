//
// Entity.hpp for Entity in /home/tekm/tek2/cpp_indie_studio
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Thu Jun 15 18:23:31 2017 leroy_0
// Last update Fri Jun 16 18:07:05 2017 yan
//

#ifndef					PROJECT_ENTITY_HPP
#define					PROJECT_ENTITY_HPP

#include				<string>
#include				<OGRE/OgreRoot.h>
#include				<OGRE/OgreRenderWindow.h>
#include				<OGRE/Ogre.h>
#include				<OIS/OIS.h>

#include				"Input.hpp"

namespace				IndieGame
{
  class					Entity
  {
  public:
    Entity(const std::string &name, Ogre::Entity * ent, Ogre::SceneNode *node, const OIS::KeyCode default_dir);
    virtual ~Entity();

    std::string				getName() const;
    Ogre::Entity			*getEntity() const;
    Ogre::SceneNode			*getNode() const;
    void				setPosition(const Ogre::Vector3 & pos);
    Ogre::Vector3			getSize() const;
    const Ogre::Vector3			&getPosition() const;
    bool				goTo(IndieGame::Map *map, IndieGame::Input *, OIS::KeyCode);
    OIS::KeyCode			getDir() const;
    void				destroy(Ogre::SceneManager *manager);
    void				unHide();
    void				hide();

  protected:
    Ogre::Entity* 			oEntity;
    Ogre::SceneNode*			oNode;
    std::string				name;
    OIS::KeyCode			_currentDir;
    int					iterator;
    int					limit;
    int					to_add;

  };
};

#endif					//PROJECT_ENTITY_HPP
