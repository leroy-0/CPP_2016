//
// pSpeedUp.hpp for pSpeedUp in /home/tekm/tek2/cpp_indie_studio
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Thu Jun 15 17:17:41 2017 leroy_0
// Last update Sun Jun 18 21:31:44 2017 longle_h
//

#ifndef		__pSpeedUp_HPP__
# define	__pSpeedUp_HPP__

#include	"Entity.hpp"
#include	"Powerup.hpp"

namespace	IndieGame
{
	class	pSpeedUp : public IndieGame::Powerup
	{
	public:
		pSpeedUp(const std::string & name, Ogre::Entity * ent, Ogre::SceneNode* node, const OIS::KeyCode dir);
		virtual ~pSpeedUp();
	};
};

#endif		/* __pSpeedUp_HPP__ */
