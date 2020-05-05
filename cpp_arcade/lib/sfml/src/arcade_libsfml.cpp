/*
** arcade_libsfml.cpp for cpp_arcade in /home/kleinh/Documents/cpp_arcade/lib/sfml/src/arcade_libsfml.cpp
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Sat Apr 08 16:59:25 2017 Arthur Klein
** Last update Sat Apr 08 16:59:26 2017 Arthur Klein
*/

#include <SFML/Graphics.hpp>
#include <ctime>
#include <sstream>
#include <thread>
#include "arcade_libsfml.hpp"
#include "Protocol.hpp"

arcade::libsfml::libsfml()
{
  std::map<arcade::TileType, sf::Texture *> tileTexture;
  std::map<arcade::TileType, sf::Texture *> pacTexture;
  
  //Snake
  tileTexture[arcade::TileType::BLOCK] = new sf::Texture();
  tileTexture[arcade::TileType::BLOCK]->loadFromFile("./lib/assets/player.png");
  tileTexture[arcade::TileType::POWERUP] = new sf::Texture();
  tileTexture[arcade::TileType::POWERUP]->loadFromFile("./lib/assets/apple.png");
  tileTexture[arcade::TileType::PLAYER] = new sf::Texture();
  tileTexture[arcade::TileType::PLAYER]->loadFromFile("./lib/assets/head.png");
  tileTexture[arcade::TileType::EMPTY] = NULL;
  this->textureMap["snake"] = tileTexture;

  //Pacman
  pacTexture[arcade::TileType::BLOCK] = new sf::Texture();
  pacTexture[arcade::TileType::BLOCK]->loadFromFile("./lib/assets/wall.png");
  pacTexture[arcade::TileType::POWERUP] = new sf::Texture();
  pacTexture[arcade::TileType::POWERUP]->loadFromFile("./lib/assets/powerup.png");
  pacTexture[arcade::TileType::PLAYER] = new sf::Texture();
  pacTexture[arcade::TileType::PLAYER]->loadFromFile("./lib/assets/pacman.png");
  pacTexture[arcade::TileType::OTHER] = new sf::Texture();
  pacTexture[arcade::TileType::OTHER]->loadFromFile("./lib/assets/coin.png");
  pacTexture[arcade::TileType::EVIL_DUDE] = new sf::Texture();
  pacTexture[arcade::TileType::EVIL_DUDE]->loadFromFile("./lib/assets/evil_dude.png");
  pacTexture[arcade::TileType::EMPTY] = NULL;
  this->textureMap["pacman"] = pacTexture;

  this->initDisplay(800, 400);
}

int 		arcade::libsfml::initDisplay(int width, int height)
{
  _width = width;
  _height = height;
  window = new sf::RenderWindow(sf::VideoMode(width, height), "SFML");
  event = new sf::Event();
  window->setFramerateLimit(8);
  return (0);
}

void 		arcade::libsfml::freeDisplay()
{
  window->close();
}

void 		arcade::libsfml::displayMap(arcade::GetMap *map, int score, int playerx, int playery)
{
  (void)score;
  window->clear();
  std::stringstream		trans;
  sf::Font font;
  sf::Text text;

  trans << score << std::endl;
  for (int i = 0; i < map->height; ++i)
  {
    for (int z = 0; z < map->width ; ++z)
    {
      if (this->spriteMap[map->tile[i * map->width + z]])
      {
	if (_height / _width != 0)
	{
	  if (map->tile[i * map->width + z] == arcade::TileType::BLOCK && playerx == z && playery == i)
	    this->spriteMap[arcade::TileType::PLAYER]->setPosition(sf::Vector2f(z * (this->_ratio * (_height / _width)), i * (this->_ratio * (_height / _width))));
	  else
	    this->spriteMap[map->tile[i * map->width + z]]->setPosition(sf::Vector2f(z * (this->_ratio * (_height / _width)), i * (this->_ratio * (_height / _width))));
	}
	else
	{
	  if (map->tile[i * map->width + z] == arcade::TileType::BLOCK && playerx == z && playery == i)
	    this->spriteMap[arcade::TileType::PLAYER]->setPosition(sf::Vector2f(z * this->_ratio, i * this->_ratio));
	  else
	    this->spriteMap[map->tile[i * map->width + z]]->setPosition(sf::Vector2f(z * this->_ratio, i * this->_ratio));
	}

	if (map->tile[i * map->width + z] == arcade::TileType::BLOCK && playerx == z && playery == i)
	  window->draw(*(this->spriteMap[arcade::TileType::PLAYER]));
	else
	  window->draw(*(this->spriteMap[map->tile[i * map->width + z]]));
      }
    }
  }
  if (font.loadFromFile("lib/assets/atari.ttf"))
  {
    text.setFont(font);
    text.setString("Score : ");
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(24);
    text.setPosition(sf::Vector2f(window->getSize().x - 100, 0));
    window->draw(text);
    text.setString(trans.str().c_str());
    text.setCharacterSize(24);
    text.setPosition(sf::Vector2f(window->getSize().x - 40, 0));
    window->draw(text);
  }
  window->display();
}

int			arcade::libsfml::menu(arcade::CommandType choose)
{
  sf::Font font;
  sf::Text text;
  sf::Text menu;
  sf::Text pacman;

  window->clear();
  if (font.loadFromFile("lib/assets/atari.ttf"))
  {
    menu.setFont(font);
    menu.setString("Hey you want a kiss ?!");
    menu.setPosition(sf::Vector2f((window->getSize().x / 2)- 100, 20));
    menu.setFillColor(sf::Color::White);
    if (choose == arcade::CommandType::UNDEFINED)
    {
      text.setFont(font);
      pacman.setFont(font);
      text.setString("> Snake");
      pacman.setString("  Pacman");
      text.setCharacterSize(24);
      pacman.setCharacterSize(24);
      text.setFillColor(sf::Color::White);
      pacman.setFillColor(sf::Color::White);
      pacman.setPosition(sf::Vector2f((window->getSize().x / 2)- 45, 200));
      text.setPosition(sf::Vector2f((window->getSize().x / 2) - 45, 120));

      text.setStyle(sf::Text::Underlined);
    }
    if (choose == arcade::CommandType::GO_UP)
    {
      text.setFont(font);
      pacman.setFont(font);

      text.setString("> Snake");
      pacman.setString("  Pacman");
      text.setCharacterSize(24);
      pacman.setCharacterSize(24);
      text.setFillColor(sf::Color::White);
      pacman.setFillColor(sf::Color::White);
      pacman.setPosition(sf::Vector2f((window->getSize().x / 2)- 45, 200));
      text.setPosition(sf::Vector2f((window->getSize().x / 2)- 45, 120));
    }
    else if (choose == arcade::CommandType::GO_DOWN)
    {
      text.setFont(font);
      pacman.setFont(font);

      text.setString("  Snake");
      pacman.setString("> Pacman");
      text.setCharacterSize(24);
      pacman.setCharacterSize(24);
      text.setFillColor(sf::Color::White);
      pacman.setFillColor(sf::Color::White);
      pacman.setPosition(sf::Vector2f((window->getSize().x / 2)- 45, 200));
      text.setPosition(sf::Vector2f((window->getSize().x / 2)- 45, 120));
    }
  }
  window->draw(text);
  window->draw(pacman);
  window->draw(menu);
  window->display();
  return (0);
}

void                    arcade::libsfml::loadAssets(const std::string & gameName)
{
  //Sprites creation
  this->spriteMap[arcade::TileType::BLOCK] = new sf::Sprite();
  this->spriteMap[arcade::TileType::POWERUP] = new sf::Sprite();
  this->spriteMap[arcade::TileType::PLAYER] = new sf::Sprite();

  this->spriteMap[arcade::TileType::BLOCK]->setTexture(*(this->textureMap[gameName])[arcade::TileType::BLOCK]);
  this->spriteMap[arcade::TileType::POWERUP]->setTexture(*(this->textureMap[gameName])[arcade::TileType::POWERUP]);
  this->spriteMap[arcade::TileType::PLAYER]->setTexture(*(this->textureMap[gameName])[arcade::TileType::PLAYER]);
  if (gameName.compare("snake") == 0)
  {
    this->spriteMap[arcade::TileType::BLOCK]->setScale(sf::Vector2f(0.1, 0.3));
    this->spriteMap[arcade::TileType::POWERUP]->setScale(sf::Vector2f(0.2, 0.2));
    this->spriteMap[arcade::TileType::PLAYER]->setScale(sf::Vector2f(0.06, 0.03));
    this->_ratio = 10;
  }
  else if (gameName.compare("pacman") == 0)
  {
    this->spriteMap[arcade::TileType::EVIL_DUDE] = new sf::Sprite();
    this->spriteMap[arcade::TileType::EVIL_DUDE]->setTexture(*(this->textureMap[gameName])[arcade::TileType::EVIL_DUDE]);
    this->spriteMap[arcade::TileType::OTHER] = new sf::Sprite();
    this->spriteMap[arcade::TileType::OTHER]->setTexture(*(this->textureMap[gameName])[arcade::TileType::OTHER]);
    this->spriteMap[arcade::TileType::BLOCK]->setScale(sf::Vector2f(0.4, 0.4));
    this->spriteMap[arcade::TileType::POWERUP]->setScale(sf::Vector2f(0.03, 0.03));
    this->spriteMap[arcade::TileType::OTHER]->setScale(sf::Vector2f(0.8, 0.8));
    this->spriteMap[arcade::TileType::EVIL_DUDE]->setScale(sf::Vector2f(0.13, 0.13));
    this->spriteMap[arcade::TileType::PLAYER]->setScale(sf::Vector2f(0.025, 0.025));
    this->_ratio = 15;
  }
}

arcade::CommandType 		arcade::libsfml::getEvent()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    return (arcade::CommandType::GO_DOWN);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    return (arcade::CommandType::GO_UP);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    return (arcade::CommandType::GO_RIGHT);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    return (arcade::CommandType::GO_LEFT);

  if (window->pollEvent(*event))
  {
    if (event->type == sf::Event::Closed || (event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::Escape))
      return (arcade::CommandType::STOP);
    else if (event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::Num3)
      return (arcade::CommandType::SWITCH_LIB_NEXT);
    else if (event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::Num2)
      return (arcade::CommandType::SWITCH_LIB_PREV);
    else if (event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::Num5)
      return (arcade::CommandType::SWITCH_GAME_NEXT);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && sf::Event::KeyPressed == event->type)
      return (arcade::CommandType::SWITCH_GAME_PREV);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8) && sf::Event::KeyPressed == event->type)
      return (arcade::CommandType::RESTART);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9) && sf::Event::KeyPressed == event->type)
      return (arcade::CommandType::MENU);
    else if (event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::Return)
      return (arcade::CommandType::PLAY);
  }
  return (arcade::CommandType::UNDEFINED);
}

extern "C" arcade::libsfml *getLib()
{
  std::cout << "Loading libsfml..."  << std::endl;
  arcade::libsfml *_new = new arcade::libsfml();
  return (_new);
}
