//
// pSpeedDown.hpp for pSpeedDown in /home/tekm/tek2/cpp_indie_studio
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Thu Jun 15 17:17:41 2017 leroy_0
// Last update Sun Jun 18 21:32:39 2017 longle_h
//

#ifndef		__pSpeedDown_HPP__
#define		__pSpeedDown_HPP__

#include	"Powerup.hpp"

namespace	IndieGame
{
	class	pSpeedDown : public IndieGame::Powerup
	{
	public:
		pSpeedDown(const std::string & name, Ogre::Entity * ent, Ogre::SceneNode* node, const OIS::KeyCode dir);
		virtual ~pSpeedDown();
	};
};

#endif		/* __pSpeedDown_HPP__ */
