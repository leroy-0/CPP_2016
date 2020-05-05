/*
** Core.cpp for cpp_arcade in /home/kleinh/Documents/cpp_arcade/src/Core.cpp
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Sat Apr 08 16:59:55 2017 Arthur Klein
** Last update Sat Apr 08 16:59:56 2017 Arthur Klein
*/

#include <fstream>
#include "IGraph.hpp"
#include "Core.hpp"
#include "Error.hpp"
#include "Manager.hpp"
#include "cstring"
#include <dlfcn.h>


arcade::Core::Core()
{
  std::map<std::string, void *> gfx;
  std::map<std::string, void *>  game;

  gfx["./lib/lib_arcade_opengl.so"] = dlopen("./lib/lib_arcade_opengl.so", RTLD_NOW | RTLD_LAZY);
  gfx["./lib/lib_arcade_libcaca.so"] = dlopen("./lib/lib_arcade_libcaca.so", RTLD_NOW | RTLD_LAZY);
  gfx["./lib/lib_arcade_sfml.so"] =dlopen("./lib/lib_arcade_sfml.so", RTLD_NOW | RTLD_LAZY);
  gfx["lib/lib_arcade_opengl.so"]= dlopen("./lib/lib_arcade_opengl.so", RTLD_NOW | RTLD_LAZY);
  gfx["lib/lib_arcade_libcaca.so"] =  dlopen("./lib/lib_arcade_libcaca.so", RTLD_NOW | RTLD_LAZY);
  gfx["lib/lib_arcade_sfml.so"] = dlopen("./lib/lib_arcade_sfml.so", RTLD_NOW | RTLD_LAZY);
  game["snake"] = dlopen("./games/lib_arcade_nibbler.so", RTLD_NOW | RTLD_LAZY);
  game["pacman"] = dlopen("./games/lib_arcade_pacman.so", RTLD_NOW | RTLD_LAZY);

  this->currentLib = -1;
  this->libs = gfx;
  this->games = game;
}

arcade::Core::~Core()
{

}

void arcade::Core::load(const std::string & lib) throw(arcade::Error)
{
  std::cout << lib << std::endl;

    for (int i = 0; i < 3; ++i)
    {
        if (gfx_libs[i].find(lib) != std::string::npos)
        {
	  currentGame = 0;
            currentLib = i;
            break;
        }
    }
  if (this->libs[this->gfx_libs[this->currentLib]] != NULL)
  {
    this->currentHandler = this->libs[this->gfx_libs[this->currentLib]];
  }
  else
  {
    std::cerr << "Error dlopen failed :" << this->gfx_libs[this->currentLib] << " Not exist." << std::endl;
    throw arcade::Error(std::cerr, "Cannot Open shared Library");
  }
}

arcade::IGraphics *arcade::Core::loadSymGraph(const std::string &function)
{
  IGraphics *(*ptr)();
  ptr = reinterpret_cast<IGraphics  *(*)()>(dlsym(this->currentHandler, function.c_str()));
  return ptr();
}

arcade::IGame *arcade::Core::loadSymGame(const std::string &function)
{
  IGame *(*ptr)();

  ptr = reinterpret_cast<IGame *(*)()>(dlsym(this->currentHandler, function.c_str()));
  return ptr();
}

void	arcade::Core::changeGameRun(int increment)
{
    this->currentGame = (this->currentGame + increment) % 2;
    if (this->currentGame == -1)
      this->currentGame = 1;
  this->getMyGame();
}

void	arcade::Core::changeLib(int increment)
{
  this->_gfx->freeDisplay();
  this->currentLib = (this->currentLib + increment) % 3;
  if (this->currentLib == -1)
    this->currentLib = 2;
  this->getMyLib();
}

void				arcade::Core::getMyGame()  throw(arcade::Error)
{
  std::cout << this->currentGame << std::endl;
  if (this->games[this->game_libs[this->currentGame]] == NULL)
    throw arcade::Error(std::cerr, "Cannot open shared library");
  this->currentHandler = this->games[this->game_libs[this->currentGame]];
  if ((this->game = this->loadSymGame("getLib")) ==  NULL)
    throw arcade::Error(std::cerr, "Cannot find the symbol");
}

void				arcade::Core::getMyLib()  throw(arcade::Error)
{
  if (this->libs[this->gfx_libs[this->currentLib]] == NULL)
    throw arcade::Error(std::cerr, "Cannot open shared library");
  this->currentHandler = this->libs[this->gfx_libs[this->currentLib]];
  if ((this->_gfx = this->loadSymGraph("getLib")) == NULL)
    throw arcade::Error(std::cerr, "Cannot find the symbol");
}

void				arcade::Core::check_state(CommandType *ret)
{
  if (*ret == CommandType::UNDEFINED || *ret == CommandType::RESTART)
  {
    this->getMyGame();
    *ret = this->game->run(this->_gfx);
  }
  if (*ret == arcade::CommandType::SWITCH_LIB_NEXT)
    this->changeLib(1);
  if (*ret == arcade::CommandType::SWITCH_LIB_PREV)
    this->changeLib(-1);
  if (*ret == arcade::CommandType::SWITCH_GAME_PREV)
    this->changeGameRun(-1);
  if (*ret == arcade::CommandType::SWITCH_GAME_NEXT)
    this->changeGameRun(1);
  if (*ret == arcade::CommandType::RESTART)
    this->getMyGame();
  if (*ret != arcade::CommandType::STOP && *ret != arcade::CommandType::MENU)
    *ret = this->game->run(this->_gfx);
  if (*ret == arcade::CommandType::SWITCH_LIB_NEXT
      || *ret == arcade::CommandType::SWITCH_LIB_PREV
      || *ret == arcade::CommandType::SWITCH_GAME_PREV
      || *ret == arcade::CommandType::SWITCH_GAME_NEXT
      || *ret == arcade::CommandType::RESTART)
    this->check_state(ret);
  if (*ret == arcade::CommandType::MENU)
  {
    this->game = NULL;
    this->_gfx->menu(arcade::CommandType::GO_UP);
    *ret = CommandType::UNDEFINED;
  }
  this->currentGame = 0;
  this->old_state = CommandType::GO_UP;
}


void		arcade::Core::checkcursor(const int inc)
{
  switch (inc)
  {
    case 1:
      if (old_state == CommandType::GO_UP || old_state == CommandType::UNDEFINED)
      {
	this->_gfx->menu(CommandType::GO_DOWN);
	old_state = CommandType::GO_DOWN;
	this->changeGameRun(-1);
      }
      else
      {
	this->changeGameRun(1);
	this->_gfx->menu(CommandType::GO_UP);
	old_state = CommandType::GO_UP;
      }
      break;
    case -1:
      if (old_state == CommandType::GO_DOWN || old_state == CommandType::UNDEFINED)
      {
	this->changeGameRun(-1);
	this->_gfx->menu(CommandType::GO_UP);
	old_state = CommandType::GO_UP;
      }
      else
      {
	this->changeGameRun(1);
	this->_gfx->menu(CommandType::GO_DOWN);
	old_state = CommandType::GO_DOWN;
      }
      break;
  }
}

void		arcade::Core::closeMyLib()
{
  for (int i = 0; i < 3; i++)
  {
    if (this->game_libs[i].empty() && this->games[this->game_libs[i].c_str()] != NULL)
      dlclose(this->games[this->game_libs[i].c_str()]);
    if (this->gfx_libs[i].empty() && this->libs[this->gfx_libs[i].c_str()] != NULL && i < 2)
      dlclose(this->libs[this->gfx_libs[i].c_str()]);
  }
}

arcade::Core *arcade::Core::run() throw(arcade::Error)
{
  CommandType		ret = CommandType::UNDEFINED;

  this->game = NULL;
  this->old_state = CommandType::GO_UP;
  if ((this->_gfx = this->loadSymGraph("getLib")) == NULL)
    throw arcade::Error(std::cerr, "Cannot find the symbol");
  this->_gfx->menu(arcade::CommandType::UNDEFINED);
  while (ret != CommandType::STOP)
  {
    switch (this->_gfx->getEvent())
    {
      case CommandType::PLAY:
	this->check_state(&ret);
	break;
      case CommandType::SWITCH_LIB_NEXT:
	this->changeLib(1);
	this->_gfx->menu(this->old_state);
	break;
      case CommandType::SWITCH_LIB_PREV:
	this->changeLib(-1);
	this->_gfx->menu(this->old_state);
	break;
      case CommandType::SWITCH_GAME_NEXT:
	this->checkcursor(1);
	break;
      case CommandType::SWITCH_GAME_PREV:
	this->checkcursor(-1);
	break;
      case CommandType::GO_UP:
	this->_gfx->menu(CommandType::GO_UP);
	this->old_state = CommandType::GO_UP;
	this->currentGame = 0;
	break;
      case CommandType::GO_DOWN:
	this->_gfx->menu(CommandType::GO_DOWN);
	this->old_state = CommandType::GO_DOWN;
	this->currentGame = 1;
	break;
      case CommandType::STOP:
	ret = CommandType::STOP;
	break;
      default:
	continue;
    }
  }
  this->_gfx->freeDisplay();
  this->closeMyLib();
  return (this);
  //lejeu->play
}
