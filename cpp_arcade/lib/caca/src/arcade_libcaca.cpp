/*
** arcade_libcaca.cpp for cpp_arcade in /home/kleinh/Documents/cpp_arcade/lib/caca/src/arcade_libcaca.cpp
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Sat Apr 08 16:50:45 2017 Arthur Klein
** Last update Sat Apr 08 16:50:45 2017 Arthur Klein
*/

#include <caca.h>
#include <sstream>
#include <ctime>
#include "arcade_libcaca.hpp"
#include "Protocol.hpp"

arcade::libcaca::libcaca()
{
  std::map<arcade::TileType, enum caca_color> tileTexture;
  std::map<arcade::TileType, std::string> tileSprite;

  _offsety = 2;
  this->initDisplay(80, 40 + _offsety);
  //Snake
  tileTexture[arcade::TileType::BLOCK] = CACA_GREEN;
  tileTexture[arcade::TileType::POWERUP] = CACA_RED;
  tileTexture[arcade::TileType::EMPTY] = CACA_BLACK;
  tileTexture[arcade::TileType::PLAYER] = CACA_WHITE;
  tileSprite[arcade::TileType::BLOCK] = " ";
  tileSprite[arcade::TileType::EMPTY] = " ";
  tileSprite[arcade::TileType::POWERUP] = "*";
  tileSprite[arcade::TileType::PLAYER] = ":";
  this->spriteMap["snake"] = tileSprite;
  this->textureMap["snake"] = tileTexture;

  //Pacman
  tileTexture[arcade::TileType::BLOCK] = CACA_BLUE;
  tileTexture[arcade::TileType::POWERUP] = CACA_GREEN;
  tileTexture[arcade::TileType::EMPTY] = CACA_BLACK;
  tileTexture[arcade::TileType::OTHER] = CACA_WHITE;
  tileTexture[arcade::TileType::PLAYER] = CACA_YELLOW;
  tileTexture[arcade::TileType::EVIL_DUDE] = CACA_RED;
  tileSprite[arcade::TileType::BLOCK] = " ";
  tileSprite[arcade::TileType::EMPTY] = " ";
    tileSprite[arcade::TileType::POWERUP] = "*";
    tileSprite[arcade::TileType::EVIL_DUDE] = "A";
  tileSprite[arcade::TileType::OTHER] = "°";
  tileSprite[arcade::TileType::PLAYER] = "C";
  this->spriteMap["pacman"] = tileSprite;
  this->textureMap["pacman"] = tileTexture;
}

int		arcade::libcaca::initDisplay(int width, int height)
{
  _width = width;
  _height = height;
  std::srand(std::time(NULL));
  cv = caca_create_canvas(width, height);
  if (!(dp = caca_create_display(cv)))
    return (-1);
  caca_set_display_title(dp, "Caca");
  return (0);
}

void    arcade::libcaca::freeDisplay()
{
  caca_free_display(dp);
  cucul_free_canvas(cv);
}

int	arcade::libcaca::menu(arcade::CommandType choose)
{
  caca_clear_canvas(this->cv);
  caca_set_color_ansi(this->cv, CACA_WHITE, CACA_BLACK);
  caca_put_str(this->cv, 35, 5, "Hey, you want a kiss ?!");
  if (choose == arcade::CommandType::UNDEFINED)
  {
    caca_put_str(this->cv, 35, 10, "> SNAKE");
    caca_set_color_ansi(this->cv, CACA_WHITE, CACA_BLACK);
    caca_put_str(this->cv, 35, 15, "  PACMAN");
    caca_refresh_display(this->dp);
  }
  if (choose == arcade::CommandType::GO_UP)
  {
    caca_put_str(this->cv, 35, 10, "> SNAKE");
    caca_set_color_ansi(this->cv, CACA_WHITE, CACA_BLACK);
    caca_put_str(this->cv, 35, 15, "  PACMAN");
  }
  else if (choose == arcade::CommandType::GO_DOWN)
  {
    caca_put_str(this->cv, 35, 10, "  SNAKE");
    caca_set_color_ansi(this->cv, CACA_WHITE, CACA_BLACK);
    caca_put_str(this->cv, 35, 15, "> PACMAN");
  }
  caca_refresh_display(dp);
  return (0);
}

void				arcade::libcaca::displayMap(arcade::GetMap *map, int score, int playerx, int playery)
{
  std::stringstream		trans;

  trans << score << std::endl;
  for (int i = 0; i < _height; ++i)
  {
    for (int z = 0; z < _width; ++z)
    {
      caca_set_color_ansi(cv, CACA_BLACK, CACA_BLACK);
      caca_put_str(cv, z, i, " "); 
    }
  }
  for (int i = 0; i < map->height; ++i)
  {
    for (int z = 0; z < map->width; ++z)
    {
      if (map->tile[i * map->width + z] == arcade::TileType::BLOCK && playerx == z && playery == i)
      {
	caca_set_color_ansi(cv, CACA_BLACK, this->getColorFromTexture(arcade::TileType::PLAYER));
	caca_put_str(cv, z, i + _offsety, this->getSpriteFromTexture(arcade::TileType::PLAYER).c_str());
      }
      else
      {
	caca_set_color_ansi(cv, CACA_BLACK, this->getColorFromTexture(map->tile[i * map->width + z]));
	caca_put_str(cv, z, i + _offsety, this->getSpriteFromTexture(map->tile[i * map->width + z]).c_str());
      }
    }
  }
  caca_set_color_ansi(this->cv, CACA_WHITE, CACA_BLACK);
  caca_put_str(cv, 0, 0, "Score : ");
  caca_put_str(cv, 8, 0, trans.str().c_str());
  std::string     delimit;
  for (int i = 0; i < _width; ++i)
    delimit[i] = '_';
  caca_put_str(cv, 0, 1, delimit.c_str());
  caca_refresh_display(dp);
}

arcade::CommandType	arcade::libcaca::getEvent()
{
  int			key;

  caca_get_event(dp, CACA_EVENT_KEY_PRESS, &ev, 200000);
  if(caca_get_event_type(&ev) & CACA_EVENT_KEY_PRESS)
  {
    key = caca_get_event_key_ch(&ev);
    if (key == CACA_KEY_ESCAPE)
    {
      return (arcade::CommandType::STOP);
    }
    else if (key == CACA_KEY_UP)
      return (arcade::CommandType::GO_UP);
    else if (key == CACA_KEY_DOWN)
      return (arcade::CommandType::GO_DOWN);
    else if (key == CACA_KEY_LEFT)
      return (arcade::CommandType::GO_LEFT);
    else if (key == CACA_KEY_RIGHT)
      return (arcade::CommandType::GO_RIGHT);
    else if (key == 34)
      return (arcade::CommandType::SWITCH_LIB_NEXT);
    else if (key == 233)
      return (arcade::CommandType::SWITCH_LIB_PREV);
    else if (key == 39)
      return (arcade::CommandType::SWITCH_GAME_NEXT);
    else if (key == 40)
      return (arcade::CommandType::SWITCH_GAME_PREV);
   else if (key == CACA_KEY_RETURN)
      return (arcade::CommandType::PLAY);
    else if (key == 231)
      return (arcade::CommandType::MENU);
    else if (key == 95)
      return (arcade::CommandType::RESTART);
   std::cerr << key << std::endl;
  }
  return (arcade::CommandType::UNDEFINED);
}

void  arcade::libcaca::loadAssets(const std::string & gameName)
{
  this->actualGame = gameName;
}

enum caca_color arcade::libcaca::getColorFromTexture(arcade::TileType tile)
{
  return ((this->textureMap[this->actualGame])[tile]); 
}

std::string arcade::libcaca::getSpriteFromTexture(arcade::TileType tile)
{
  return ((this->spriteMap[this->actualGame])[tile]);
}

extern "C" arcade::libcaca *getLib()
{
    std::cout <<"Loading libcaca..." << std::endl;
  arcade::libcaca *_new = new arcade::libcaca();
  return (_new);
}
