//
// Map.hpp for Map in /home/tekm/tek2/cpp_indie_studio
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Fri May  5 22:15:10 2017 leroy_0
// Last update Fri May  5 22:15:11 2017 leroy_0
//

#ifndef				__MAP_HPP__
#define				__MAP_HPP__

#include			<OGRE/OgreRoot.h>
#include			<OGRE/OgreRenderWindow.h>
#include			<OGRE/Ogre.h>
#include			<OIS/OIS.h>

namespace			IndieGame
{
  class				Map
  {
  public:
    struct			pos
    {
      int			x;
      int			y;
    };

    Map(const std::string & name);
    virtual ~Map();

    bool			setMap(const std::string & name, bool);
    int				**getMap() const;
    int				getWidth() const;
    int				getHeight() const;

    void			generateBreakableWall();
    int				checkPercentBreakableWall();
    bool			checkValidBreakableWall(int, int);
    int				getWorldPosX(int x) const;
    int				getWorldPosY(int y) const;

    int				getMapPosX(int x) const;
    int				getMapPosY(int y) const;

    Ogre::Vector3   getPlayerPos(unsigned int nb) const;

    bool isCollision(Ogre::Vector3 nbox1, Ogre::Vector3 nbox2, Ogre::Vector3 ebox1, Ogre::Vector3 ebox2);

  private:
    int				**_map;
    int				_width;
    int				_height;
    std::vector<Ogre::Vector3>	_playersPos;
  };
};

#define 	RATIO_MAP 	(70)
#define 	DEFAULT_W_POS	"pos"

#endif