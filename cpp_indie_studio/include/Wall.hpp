//
// Wall.hpp for Wall in /home/tekm/tek2/cpp_indie_studio
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Wed May 31 14:09:27 2017 leroy_0
// Last update Sun Jun 18 21:32:06 2017 longle_h
//

#ifndef		__WALL_HPP__
# define	__WALL_HPP__

#include	<OGRE/OgreRoot.h>
#include	<OGRE/OgreRenderWindow.h>
#include	<OGRE/Ogre.h>
#include	<OIS/OIS.h>

#include	"Entity.hpp"

namespace	IndieGame
{
	class	Wall : public IndieGame::Entity
	{
	public:
		Wall(const std::string & name, Ogre::Entity * ent, Ogre::SceneNode* node, const OIS::KeyCode dir);
		virtual ~Wall();
	};
};

#endif		/* _WALL_HPP_ */
