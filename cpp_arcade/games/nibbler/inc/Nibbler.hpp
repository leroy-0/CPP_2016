//
// Nibbler.hpp for Nibbler in /home/tekm/tek2/cpp_arcade/games/nibbler
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Tue Mar  7 15:30:47 2017 leroy_0
// Last update Tue Mar  7 15:30:48 2017 leroy_0
//

#ifndef			__NIBBLER_HPP_
#define			__NIBBLER_HPP_

#include		<ctime>
#include		<Protocol.hpp>
#include		"IGame.hpp"
#include		"Map.hpp"
#include		"Character.hpp"

namespace		arcade
{
  class			Nibbler : public IGame
  {
  public:
    Nibbler(int width, int height);

    virtual		~Nibbler() {};
    Character		*getCharacter();
    Map			*getMap();
    arcade::CommandType	analyseEvent(arcade::CommandType event);
    void		manageDir(arcade::CommandType, CommandType *);
    void		manageLenght();
    void		managePowerUp();
    Character		*getPlayer();
    arcade::CommandType	run(IGraphics *);

  private:
    int			_powerup;
    int			_score;
    Character		*_player;
    Map			*_map;
  };
};

#endif