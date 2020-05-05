/*
** GUI.cpp for cpp_indie_studio in /home/kleinh/Documents/cpp_indie_studio/src/GUI.cpp
**
** Made by Arthur Klein
** Login   <arthur.klein@epitech.eu>
**
** Started on  Tue Jun 13 12:30:24 2017 Arthur Klein
** Last update Tue Jun 13 12:30:24 2017 Arthur Klein
*/

#include "GUI.hpp"
#include <iostream>
#include "CEGUI/CEGUI.h"
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <dirent.h>

IndieGame::GUI::~GUI()
{
}

bool IndieGame::GUI::createText()
{
  CEGUI::SchemeManager::getSingleton().createFromFile("OgreTray.scheme");
  CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();

  this->_textContainer = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");
  this->_text = wmgr.createWindow("OgreTray/StaticText", "CEGUIDemo/QuitButton");
  this->_textContainer->addChild(this->_text);
  this->_text->setSize(CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.09, 0)));
  this->_text->setPosition(CEGUI::UVector2(CEGUI::UDim(0, (_w - 250) / 2), CEGUI::UDim(0, (_h - 150))));
  return (true);
}

bool IndieGame::GUI::createButtonLoad()
{
  CEGUI::SchemeManager::getSingleton().createFromFile("OgreTray.scheme");
  CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();

  this->_loadContainer = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");

  this->_buttonLoad["1"] = wmgr.createWindow("OgreTray/Button", "CEGUIDemo/QuitButton");
  this->_buttonLoad["2"] = wmgr.createWindow("OgreTray/Button", "CEGUIDemo/QuitButton");
  this->_buttonLoad["3"] = wmgr.createWindow("OgreTray/Button", "CEGUIDemo/QuitButton");
  _buttonLoad["1"]->setSize(CEGUI::USize(CEGUI::UDim(0.20, 0), CEGUI::UDim(0.05, 0)));
  _buttonLoad["1"]->setPosition(CEGUI::UVector2(CEGUI::UDim(0, (_w - 270) / 2), CEGUI::UDim(0, (_h - 150) / 2)));
  _buttonLoad["2"]->setSize(CEGUI::USize(CEGUI::UDim(0.20, 0), CEGUI::UDim(0.05, 0)));
  _buttonLoad["2"]->setPosition(CEGUI::UVector2(CEGUI::UDim(0, (_w - 270) / 2), CEGUI::UDim(0, _h / 2)));
  _buttonLoad["3"]->setSize(CEGUI::USize(CEGUI::UDim(0.20, 0), CEGUI::UDim(0.05, 0)));
  _buttonLoad["3"]->setPosition(CEGUI::UVector2(CEGUI::UDim(0, (_w - 270) / 2), CEGUI::UDim(0, (_h + 150)/ 2)));
  this->_loadContainer->addChild(_buttonLoad["1"]);
  this->_loadContainer->addChild(_buttonLoad["2"]);
  this->_loadContainer->addChild(_buttonLoad["3"]);
  return (true);
}

bool IndieGame::GUI::createButtonForOption()
{
  CEGUI::SchemeManager::getSingleton().createFromFile("OgreTray.scheme");
  CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();

  this->_optionContainer = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");

  this->_buttonOption["Sound"] = wmgr.createWindow("OgreTray/Button", "CEGUIDemo/QuitButton");
  _buttonOption["Sound"]->setSize(CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
  _buttonOption["Sound"]->setText("Sound/On");
  _buttonOption["Sound"]->setPosition(CEGUI::UVector2(CEGUI::UDim(0, (_w - 250) / 2), CEGUI::UDim(0, (_h - 150) / 2)));
  this->_optionContainer->addChild(_buttonOption["Sound"]);
  return (true);
}

const CEGUI::Window& IndieGame::GUI::getTextContainer() const
{
  return (*this->_textContainer);
}

const CEGUI::Window& IndieGame::GUI::getText() const
{
  return (*this->_text);
}

void IndieGame::GUI::setMytext(const std::string &text, const CEGUI::USize size, int pos1, int pos2)
{
  this->_text->setSize(size);
  this->_text->setPosition(CEGUI::UVector2(CEGUI::UDim(0, (_w - pos1) / 2), CEGUI::UDim(0, (_h - pos2) / 2)));
  this->_text->setText(text);
  this->_text->setHorizontalAlignment(CEGUI::HorizontalAlignment(100));
}

IndieGame::GUI::GUI(Ogre::Root *root, int w, int h)
{
  this->_w = w;
  _newGame = false;
  _sound = true;
  _wantSave = false;
  this->_h = h;
  _nbIA = -1;
  _save = "";
  this->_nbPlayers = 0;
  this->_drawMap = false;
  this->state = SPLASH;
  this->_isPlayabled = false;
  Ogre::RenderTarget *renderTarget = root->getRenderTarget("Bomberman");

  this->_renderer = &CEGUI::OgreRenderer::bootstrapSystem(*renderTarget);
  CEGUI::SchemeManager::getSingleton().createFromFile("OgreTray.scheme");
  this->_rootWindow = CEGUI::WindowManager::getSingleton().createWindow( "DefaultWindow", "_MasterRoot" );
  CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(this->_rootWindow);
  CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("OgreTrayImages/MouseArrow");

  this->createButtonForMenu();
  this->createButtonForPause();
  this->createButtonForChoosePlayer();
  this->createButtonForIA();
  this->createText();
  this->createButtonLoad();
  this->createSaveDir();
  this->getSaveInDir();
  this->createButtonForOption();
}

bool			IndieGame::GUI::getSound() const
{
  return (this->_sound);
}

bool			IndieGame::GUI::getDrawMap() const
{
  return (this->_drawMap);
}

void			IndieGame::GUI::setDrawMap(bool draw)
{
  this->_drawMap = draw;
}

const CEGUI::Window		&IndieGame::GUI::getChoosePlayerContainer() const
{
  return (*this->_playerContainer);
}

const CEGUI::Window		&IndieGame::GUI::getDefaultContainer() const
{
  return (*this->_defaultContainer);
}

const CEGUI::Window		&IndieGame::GUI::getIAContainer() const
{
  return (*this->_IAContainer);
}

const CEGUI::Window		&IndieGame::GUI::getPauseContainer() const
{
  return (*this->_pauseContainer);
}

void					IndieGame::GUI::setNbButtonIa()
{
  if (this->getNbPlayers() == 1)
  {
    this->_buttonIA["2"]->hide();
    this->_buttonIA["3"]->hide();
    this->_buttonIA["4"]->hide();
  }
  if (this->getNbPlayers() == 2)
  {
    this->_buttonIA["3"]->hide();
    this->_buttonIA["4"]->hide();
  }
  if (this->getNbPlayers() == 3)
    this->_buttonIA["4"]->hide();
}

void IndieGame::GUI::iaState()
{
  CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(_IAContainer);
  this->_pauseContainer->setVisible(false);
  this->_defaultContainer->setVisible(false);
  this->_playerContainer->setVisible(false);
  this->_loadContainer->setVisible(false);
  this->_IAContainer->setVisible(true);
  this->setNbButtonIa();
}

void IndieGame::GUI::menuState()
{
  CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(_defaultContainer);
  this->_pauseContainer->setVisible(false);
  this->_defaultContainer->setVisible(true);
  this->_playerContainer->setVisible(false);
  this->_IAContainer->setVisible(false);
}

void IndieGame::GUI::playerState()
{
  CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(_playerContainer);
  this->_pauseContainer->setVisible(false);
  this->_defaultContainer->setVisible(false);
  this->_playerContainer->setVisible(true);
  this->_loadContainer->setVisible(false);
  this->_IAContainer->setVisible(false);
}

void IndieGame::GUI::pauseState()
{
  CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(_pauseContainer);
  this->_pauseContainer->setVisible(true);
  this->_defaultContainer->setVisible(false);
  this->_playerContainer->setVisible(false);
  this->_IAContainer->setVisible(false);
  this->_loadContainer->setVisible(false);
}

void IndieGame::GUI::gameState()
{
  this->_pauseContainer->setVisible(false);
  this->_textContainer->setVisible(false);
  this->_defaultContainer->setVisible(false);
  this->_playerContainer->setVisible(false);
  this->_IAContainer->setVisible(false);
  this->_loadContainer->setVisible(false);
}

void IndieGame::GUI::setTextForLoadButton()
{
  int		i;

  i = 0;
  for (auto it = _files.begin();it != _files.end() &&  i < 3; ++it)
  {
    if (i == 0)
      _buttonLoad["1"]->setText(*it);
    else if (i == 1)
      _buttonLoad["2"]->setText(*it);
    else if (i == 2)
      _buttonLoad["3"]->setText(*it);
    i++;
  }
}

void IndieGame::GUI::optionState()
{
  CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(_optionContainer);
  this->_pauseContainer->setVisible(false);
  this->_defaultContainer->setVisible(false);
  this->_playerContainer->setVisible(false);
  this->_IAContainer->setVisible(false);
  this->_loadContainer->setVisible(false);
  this->_optionContainer->setVisible(true);
}


void IndieGame::GUI::loadState()
{
  this->_pauseContainer->setVisible(false);
  this->_defaultContainer->setVisible(false);
  this->_playerContainer->setVisible(false);
  this->_IAContainer->setVisible(false);
  if (!_files.empty())
  {
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(_loadContainer);
    this->_loadContainer->setVisible(true);
    this->setTextForLoadButton();
  }
  else
  {
    this->setMytext("Oh no :(, No save Found", CEGUI::USize(CEGUI::UDim(0.20, 0), CEGUI::UDim(0.09, 0)), 300, 150);
    this->displayText();
  }
}

void			IndieGame::GUI::displayButton()
{
  if (state == CHOOSEPLAYER)
    this->playerState();
  if (state == MENU)
    this->menuState();
  if (state == PAUSE)
    this->pauseState();
  if (state == GAME)
    this->gameState();
  if (state == IA)
    this->iaState();
  if (state == LOAD)
    this->loadState();
  if (state == OPTION)
    this->optionState();
}

bool			IndieGame::GUI::isAllMenuDesactived() const
{
  if (this->_defaultContainer->isVisible()
      || this->_playerContainer->isVisible()
      || this->_pauseContainer->isVisible()
      || this->_IAContainer->isVisible()
      || this->_loadContainer->isVisible()
      || this->_textContainer->isVisible())
    return (false);
  return (true);
}

void			IndieGame::GUI::setState(IndieGame::state state)
{
  this->state = state;
}

IndieGame::state	IndieGame::GUI::getState() const
{
  return (this->state);
}

void			IndieGame::GUI::setPropetyButton(std::string name , std::string text,  CEGUI::USize size , CEGUI::UVector2 position, bool state)
{
  if (!state)
  {
    _buttonMap[name]->setText(text);
    _buttonMap[name]->setSize(size);
    _buttonMap[name]->setPosition(position);
  }
  else
  {
    _buttonIA[name]->setSize(size);
    _buttonIA[name]->setText(text);
    _buttonIA[name]->setPosition(position);
  }
}

void IndieGame::GUI::setNbPlayers(unsigned int nbPlayers)
{
  this->_nbPlayers = nbPlayers;
}
void IndieGame::GUI::setSave(const std::string &save)
{
  this->_save = save;
}
unsigned int IndieGame::GUI::getNbPlayers() const
{
  return (this->_nbPlayers);
}

int IndieGame::GUI::getNbIA() const
{
  return (this->_nbIA);
}


bool			IndieGame::GUI::createButtonForPause()
{
  CEGUI::SchemeManager::getSingleton().createFromFile("OgreTray.scheme");
  CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();

  this->_pauseContainer = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");
  this->_buttonMap["Resume"] = wmgr.createWindow("OgreTray/Button", "CEGUIDemo/QuitButton");
  this->_buttonMap["RestartGame"] = wmgr.createWindow("OgreTray/Button", "CEGUIDemo/QuitButton");
  this->_buttonMap["GoBackToMenu"] = wmgr.createWindow("OgreTray/Button", "CEGUIDemo/QuitButton");
  this->_buttonMap["Save"] = wmgr.createWindow("OgreTray/Button", "CEGUIDemo/QuitButton");
  this->setPropetyButton("Resume", "Resume", CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)), CEGUI::UVector2(CEGUI::UDim(0, (_w - 250) / 2), CEGUI::UDim(0, (_h - 450)/ 2)), false);
  this->setPropetyButton("RestartGame", "Restart Game", CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)), CEGUI::UVector2(CEGUI::UDim(0, (_w - 250) / 2), CEGUI::UDim(0, (_h - 300)/ 2)), false);
  this->setPropetyButton("GoBackToMenu", "Go Back To Menu", CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)), CEGUI::UVector2(CEGUI::UDim(0, (_w - 250) / 2), CEGUI::UDim(0, (_h - 150)/ 2)), false);
  this->setPropetyButton("Save", "Save", CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)), CEGUI::UVector2(CEGUI::UDim(0, (_w - 250) / 2), CEGUI::UDim(0, (_h)/ 2)), false);
  this->_pauseContainer->addChild(_buttonMap["Resume"]);
  this->_pauseContainer->addChild(_buttonMap["RestartGame"]);
  this->_pauseContainer->addChild(_buttonMap["GoBackToMenu"]);
  this->_pauseContainer->addChild(_buttonMap["Save"]);
  return (true);
}

bool			IndieGame::GUI::createButtonForIA()
{
  CEGUI::SchemeManager::getSingleton().createFromFile("OgreTray.scheme");
  CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();

  this->_IAContainer = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");
  this->_buttonIA["1"] = wmgr.createWindow("OgreTray/Button", "CEGUIDemo/QuitButton");
  this->_buttonIA["2"] = wmgr.createWindow("OgreTray/Button", "CEGUIDemo/QuitButton");
  this->_buttonIA["3"] = wmgr.createWindow("OgreTray/Button", "CEGUIDemo/QuitButton");
  this->_buttonIA["4"] = wmgr.createWindow("OgreTray/Button", "CEGUIDemo/QuitButton");
  this->_buttonIA["0"] = wmgr.createWindow("OgreTray/Button", "CEGUIDemo/QuitButton");
  this->setPropetyButton("0", "No IA", CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)), CEGUI::UVector2(CEGUI::UDim(0, (_w -650) / 2), CEGUI::UDim(0, (_h) / 2)), true);
  this->setPropetyButton("1", "One IA", CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)), CEGUI::UVector2(CEGUI::UDim(0, (_w - 650) / 2), CEGUI::UDim(0, (_h + 150)/ 2)), true);
  this->setPropetyButton("2", "Two IAS", CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)), CEGUI::UVector2(CEGUI::UDim(0, (_w + 150) / 2), CEGUI::UDim(0, (_h + 150)/ 2)), true);
  this->setPropetyButton("3", "Three IAS", CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)), CEGUI::UVector2(CEGUI::UDim(0, (_w - 650) / 2), CEGUI::UDim(0, (_h + 300) / 2)), true);
  this->setPropetyButton("4", "Four IAS", CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)), CEGUI::UVector2(CEGUI::UDim(0, (_w + 150) / 2), CEGUI::UDim(0, (_h + 300) / 2)), true);
  this->_IAContainer->addChild(_buttonIA["1"]);
  this->_IAContainer->addChild(_buttonIA["2"]);
  this->_IAContainer->addChild(_buttonIA["3"]);
  this->_IAContainer->addChild(_buttonIA["4"]);
  this->_IAContainer->addChild(_buttonIA["0"]);
  return (true);
}

bool			IndieGame::GUI::createButtonForChoosePlayer()
{
  CEGUI::SchemeManager::getSingleton().createFromFile("OgreTray.scheme");
  CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();

  this->_playerContainer = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");
  this->_buttonMap["1"] = wmgr.createWindow("OgreTray/Button", "CEGUIDemo/QuitButton");
  this->_buttonMap["2"] = wmgr.createWindow("OgreTray/Button", "CEGUIDemo/QuitButton");
  this->_buttonMap["3"] = wmgr.createWindow("OgreTray/Button", "CEGUIDemo/QuitButton");
  this->_buttonMap["4"] = wmgr.createWindow("OgreTray/Button", "CEGUIDemo/QuitButton");
  this->setPropetyButton("1", "One Player", CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)), CEGUI::UVector2(CEGUI::UDim(0, (_w - 650) / 2), CEGUI::UDim(0, (_h + 150)/ 2)), false);
  this->setPropetyButton("2", "Two Players", CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)), CEGUI::UVector2(CEGUI::UDim(0, (_w + 150) / 2), CEGUI::UDim(0, (_h + 150)/ 2)), false);
  this->setPropetyButton("3", "Three Players", CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)), CEGUI::UVector2(CEGUI::UDim(0, (_w - 650) / 2), CEGUI::UDim(0, (_h + 300) / 2)), false);
  this->setPropetyButton("4", "Four Players", CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)), CEGUI::UVector2(CEGUI::UDim(0, (_w + 150) / 2), CEGUI::UDim(0, (_h + 300) / 2)), false);
  this->_playerContainer->addChild(_buttonMap["1"]);
  this->_playerContainer->addChild(_buttonMap["2"]);
  this->_playerContainer->addChild(_buttonMap["3"]);
  this->_playerContainer->addChild(_buttonMap["4"]);
  return (true);
}

bool			IndieGame::GUI::createButtonForMenu()
{
  CEGUI::SchemeManager::getSingleton().createFromFile("OgreTray.scheme");
  CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();

  this->_defaultContainer = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");
  this->_buttonMap["quit"] = wmgr.createWindow("OgreTray/Button", "CEGUIDemo/QuitButton");
  this->_buttonMap["LoadGame"] = wmgr.createWindow("OgreTray/Button", "CEGUIDemo/QuitButton");
  this->_buttonMap["NewGame"] = wmgr.createWindow("OgreTray/Button", "CEGUIDemo/QuitButton");
  this->_buttonMap["Setup"] = wmgr.createWindow("OgreTray/Button", "CEGUIDemo/QuitButton");
  this->_buttonMap["Credits"] = wmgr.createWindow("OgreTray/Button", "CEGUIDemo/QuitButton");
  this->setPropetyButton("quit", "Quit", CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)), CEGUI::UVector2(CEGUI::UDim(0, (_w - 250) / 2), CEGUI::UDim(0, (_h + 450)/ 2)), false);
  this->setPropetyButton("NewGame", "Start New Game", CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)), CEGUI::UVector2(CEGUI::UDim(0, (_w - 250) / 2), CEGUI::UDim(0, (_h - 150) / 2)), false);
  this->setPropetyButton("Setup", "Setup", CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)), CEGUI::UVector2(CEGUI::UDim(0, (_w - 250) / 2), CEGUI::UDim(0, (_h + 150)/ 2)), false);
  this->setPropetyButton("LoadGame", "Load Game", CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)), CEGUI::UVector2(CEGUI::UDim(0, (_w - 250) / 2), CEGUI::UDim(0, (_h) / 2)), false);
  this->setPropetyButton("Credits", "Credits", CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)), CEGUI::UVector2(CEGUI::UDim(0, (_w - 250) / 2), CEGUI::UDim(0, (_h + 300)/ 2)), false);
  this->_defaultContainer->addChild(_buttonMap["quit"]);
  this->_defaultContainer->addChild(_buttonMap["Setup"]);
  this->_defaultContainer->addChild(_buttonMap["Credits"]);
  this->_defaultContainer->addChild(_buttonMap["LoadGame"]);
  this->_defaultContainer->addChild(_buttonMap["NewGame"]);
  return (true);
}

void IndieGame::GUI::displayText()
{
  CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(this->_textContainer);

  this->_textContainer->setVisible(true);
  this->_loadContainer->setVisible(false);
  this->_defaultContainer->setVisible(false);
  this->_IAContainer->setVisible(false);
  this->_playerContainer->setVisible(false);
  this->_pauseContainer->setVisible(false);
}

bool IndieGame::GUI::isMenu() const
{
  if (this->getState() == MENU)
    return (true);
  return (false);
}

bool IndieGame::GUI::isOption() const
{
  if (this->getState() == OPTION)
    return (true);
  return (false);
}


bool IndieGame::GUI::isChoosePlayer() const
{
  if (this->getState() == CHOOSEPLAYER)
    return (true);
  return (false);
}

bool IndieGame::GUI::isGame() const
{
  if (this->getState() == GAME)
    return (true);
  return (false);
}

bool					IndieGame::GUI::isLoadGame() const
{
  if (this->getState() == LOAD)
    return (true);
  return (false);
}


bool IndieGame::GUI::isButtonExitPressInMenu() const
{
  if (this->getState() == EXIT)
    return (true);
  return (false);
}

bool IndieGame::GUI::isPause() const
{
  if (this->getState() == PAUSE)
    return (true);
  return (false);
}


bool IndieGame::GUI::mouseMoved(const OIS::MouseState &arg)
{
  _context = &CEGUI::System::getSingleton().getDefaultGUIContext();

  _context->injectMouseMove(arg.X.rel, arg.Y.rel);
  return (true);
}

bool IndieGame::GUI::isPlayable() const
{
  return (this->_isPlayabled);
}
bool IndieGame::GUI::getNewGame() const
{
  return (this->_newGame);
}


void IndieGame::GUI::setNewGame(bool newGame)
{
  this->_newGame = newGame;
}

void IndieGame::GUI::setWantSave(bool wantSave)
{
  this->_wantSave = wantSave;
}

bool IndieGame::GUI::getWantSave() const
{
  return (this->_wantSave);
}

std::string IndieGame::GUI::getSave() const
{
  return (this->_save);
}

std::map<std::string, CEGUI::Window *> IndieGame::GUI::getLoadButton() const
{
  return (this->_buttonLoad);
}

void IndieGame::GUI::setNbIA(int nbIA)
{
  this->_nbIA = nbIA;
}

std::vector<std::string>	IndieGame::GUI::getSaveInDir()
{
  if (_dir != NULL)
  {
    while ((_ent = readdir(_dir)) != NULL)
    {
      if (_ent->d_name[0] != '.')
	_files.push_back(std::string(_ent->d_name));
    }
    return (_files);
  }
  return (_files);
}

void				IndieGame::GUI::setValueByDefault()
{
  this->_nbPlayers = 0;
  this->_nbIA = -1;
  _save = "";
  this->_isPlayabled = false;
  this->_newGame = true;
  this->_buttonIA["1"]->setVisible(true);
  this->_buttonIA["2"]->setVisible(true);
  this->_buttonIA["3"]->setVisible(true);
  this->_buttonIA["4"]->setVisible(true);
}

void				IndieGame::GUI::createSaveDir()
{
  _dir = opendir("save");
  _files.clear();
}

IndieGame::state	IndieGame::GUI::whereIsMouse(const OIS::MouseState &arg)
{
  if (_buttonLoad["1"]->isMouseContainedInArea() && arg.buttonDown(OIS::MouseButtonID::MB_Left))
    this->_save = "1";
  if (_buttonLoad["2"]->isMouseContainedInArea() && arg.buttonDown(OIS::MouseButtonID::MB_Left))
    this->_save = "2";
  if (_buttonLoad["3"]->isMouseContainedInArea() && arg.buttonDown(OIS::MouseButtonID::MB_Left))
    this->_save = "3";
  if (_buttonMap["quit"]->isMouseContainedInArea() && arg.buttonDown(OIS::MouseButtonID::MB_Left))
    this->setState(EXIT);
  if (_buttonMap["Setup"]->isMouseContainedInArea() && arg.buttonDown(OIS::MouseButtonID::MB_Left))
    this->setState(OPTION);
  if (_buttonIA["0"]->isMouseContainedInArea() && arg.buttonDown(OIS::MouseButtonID::MB_Left))
    this->setNbIA(0);
  if (_buttonIA["1"]->isMouseContainedInArea() && arg.buttonDown(OIS::MouseButtonID::MB_Left))
    this->setNbIA(1);
  if (_buttonIA["2"]->isMouseContainedInArea() && arg.buttonDown(OIS::MouseButtonID::MB_Left))
    this->setNbIA(2);
  if (_buttonIA["3"]->isMouseContainedInArea() && arg.buttonDown(OIS::MouseButtonID::MB_Left))
    this->setNbIA(3);
  if (_buttonIA["4"]->isMouseContainedInArea() && arg.buttonDown(OIS::MouseButtonID::MB_Left))
    this->setNbIA(4);
  if (_buttonMap["LoadGame"]->isMouseContainedInArea() && arg.buttonDown(OIS::MouseButtonID::MB_Left))
    this->setState(LOAD);
  if (_buttonMap["1"]->isMouseContainedInArea() && arg.buttonDown(OIS::MouseButtonID::MB_Left))
    this->setNbPlayers(1);
  if (_buttonMap["2"]->isMouseContainedInArea() && arg.buttonDown(OIS::MouseButtonID::MB_Left))
    this->setNbPlayers(2);
  if (_buttonMap["3"]->isMouseContainedInArea() && arg.buttonDown(OIS::MouseButtonID::MB_Left))
    this->setNbPlayers(3);
  if (_buttonMap["4"]->isMouseContainedInArea() && arg.buttonDown(OIS::MouseButtonID::MB_Left))
    this->setNbPlayers(4);
  if (_buttonMap["NewGame"]->isMouseContainedInArea() && arg.buttonDown(OIS::MouseButtonID::MB_Left))
    this->setState(CHOOSEPLAYER);
  if (_buttonMap["RestartGame"]->isMouseContainedInArea() && arg.buttonDown(OIS::MouseButtonID::MB_Left))
    _drawMap = true;
  if (_buttonMap["Resume"]->isMouseContainedInArea() && arg.buttonDown(OIS::MouseButtonID::MB_Left))
    this->setState(GAME);
  if (_buttonOption["Sound"]->isMouseContainedInArea() && arg.buttonDown(OIS::MouseButtonID::MB_Left))
  {
    if (this->_sound)
    {
      _buttonOption["Sound"]->setText("Sound/Off");
      this->_sound = false;
    }
    else
    {
      _buttonOption["Sound"]->setText("Sound/On");
      this->_sound = true;
    }
  }
  if (_buttonMap["Save"]->isMouseContainedInArea() && arg.buttonDown(OIS::MouseButtonID::MB_Left))
  {
    this->setWantSave(true);
    this->setState(GAME);
  }
  if (_buttonMap["GoBackToMenu"]->isMouseContainedInArea() && arg.buttonDown(OIS::MouseButtonID::MB_Left))
  {
    this->_nbPlayers = 0;
    this->_nbIA = -1;
    this->_isPlayabled = false;
    this->_newGame = true;
    this->_buttonIA["1"]->setVisible(true);
    this->_buttonIA["2"]->setVisible(true);
    this->_buttonIA["3"]->setVisible(true);
    this->_buttonIA["4"]->setVisible(true);
    this->setState(MENU);
  }
  if (this->getNbPlayers() != 0 && this->isChoosePlayer())
    this->setState(IA);
  if (this->getNbIA() != -1 && this->getState() == IA)
    this->setState(GAME);
  return (LOOP);
}


