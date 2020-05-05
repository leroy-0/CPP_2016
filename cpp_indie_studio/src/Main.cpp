//
// Main.cpp for main in /home/kleinh/Documents/TEK2/cpp_indie_studio/src
// 
// Made by Arthur Klein
// Login   <arthur.klein@epitech.eu>
// 
// Started on  Tue May  2 13:14:38 2017 Arthur Klein
// Last update Fri May  5 08:44:44 2017 Arthur
//

#include "Bomberman.hpp"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN64
#define WIN64_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN64
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
int	main()
#endif
{
  IndieGame::Bomberman 	game;

  std::srand(std::time(NULL));
  if (!game.start())
    return (-1);
  game.run();
  game.exit();
}
#ifdef	__cplusplus
}
#endif
