/*
** Protocol.hpp for cpp_arcade in /home/kleinh/Documents/cpp_arcade/inc/Protocol.hpp
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Tue Apr 04 18:48:48 2017 Arthur Klein
** Last update Tue Apr 04 18:48:48 2017 Arthur Klein
*/

#ifndef			__ARCADE_PROTOCOL_HPP__
# define		__ARCADE_PROTOCOL_HPP__
# include		<stdint.h>

namespace		arcade
{
  enum class		CommandType : uint16_t
  {
    WHERE_AM_I	= 0,		// RETURN A WHERE AM I STRUCTURE
    GET_MAP		= 1,		// RETURN A GETMAP STRUCTURE
    GO_UP		= 2,		// MOVE THE CHARACTER UP
    GO_DOWN		= 3,		// MOVE THE CHARACTER DOWN
    GO_LEFT		= 4,		// MOVE THE CHARACTER LEFT
    GO_RIGHT		= 5,		// MOVE THE CHARACTER RIGHT
    GO_FORWARD	= 6,		// MOVE THE CHARACTER FORWARD (FOR SNAKE)
    SHOOT		= 7,		// SHOOT (FOR SOLAR FOX AND CENTIPEDE)
    ILLEGAL		= 8,		// THE INSTRUCTION WAS ILLEGAL
    PLAY		= 9,		// PLAY A ROUND
    UNDEFINED		= 10,
    STOP		= 11,
    SWITCH_LIB_NEXT	= 12,
    SWITCH_LIB_PREV	= 13,
    SWITCH_GAME_NEXT	= 14,
    SWITCH_GAME_PREV	= 15,
    MENU		= 16,
    RESTART		= 17,
    GAME_WON		= 18,
    GAME_OVER		= 19
  };

  enum class		TileType : uint16_t
  {
    EMPTY		= 0,		// TILE WHERE THE CHARACTER CAN GO
    BLOCK		= 1,		// TILE WHERE THE CHARACTER CANNOT GO
    OBSTACLE		= 2,		// FOR CENTIPEDE
    EVIL_DUDE		= 3,		// EVIL DUDE
    EVIL_SHOOT	= 4,		// EVIL SHOOT
    MY_SHOOT		= 5,
    POWERUP		= 6,		// POWERUP
    OTHER		= 7,		// ANYTHING THAT WILL BE IGNORED BY THE KOALINETTE
    PLAYER = 8
  };

  // The format is width, height, and width * height * sizeof(TileType) quantity of TileType
  struct		GetMap
  {
    CommandType		type;
    uint16_t		width;
    uint16_t		height;
    TileType		tile[0];
  }__attribute__((packed));
  
  // The format is length, length * Position quantity of TileType
  struct		Position
  {
    uint16_t		x;
    uint16_t		y;
  } __attribute__((packed));

  struct		WhereAmI
  {
    CommandType		type;
    uint16_t		lenght;
    Position		position[0];
  } __attribute__((packed));
}

#endif	//		__ARCADE_PROTOCOL_HPP__