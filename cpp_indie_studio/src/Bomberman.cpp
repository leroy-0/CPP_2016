
//
// IndieGame::Bomberman.cpp for IndieGame::Bomberman in /home/tekm/tek2/cpp_indie_studio
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Thu May  4 00:23:36 2017 leroy_0
// Last update Sun Jun 18 20:58:04 2017 yan
//

#include <CEGUI/CEGUI.h>
#include <thread>
#include <chrono>
#include "Bomberman.hpp"
#include "Map.hpp"
#include "GUI.hpp"
#include "Explosion.hpp"

IndieGame::Bomberman::Bomberman()
{
  _pRoot = NULL;
  _pSceneManager = NULL;
  _pRenderWindow = NULL;
  _pViewport = NULL;
  _pCamera = NULL;
  _entityManager = new EntityManager();
  _powerUpManager = new PowerUpManager();
  _save = new IndieGame::Save();
  _soundEngine = irrklang::createIrrKlangDevice();
  _soundEngine->setSoundVolume(0.5);
  _baseSound = _soundEngine->addSoundSourceFromFile("media/sound/base.ogg");
  _baseSound->setDefaultVolume(0.5f);
  _gameSound = _soundEngine->addSoundSourceFromFile("media/sound/game.ogg");
  _gameSound->setDefaultVolume(0.5f);
  //_soundEngine->play2D(_baseSound);
  _splashSound = _soundEngine->addSoundSourceFromFile("media/sound/splash.ogg");
  _splashSound->setDefaultVolume(0.5f);
  _explosion_count = 0;
  _start = 0;
}

IndieGame::Bomberman::~Bomberman()
{
  delete _entityManager;
  _soundEngine->drop();
  exit();
}

void IndieGame::Bomberman::loadRessources(Ogre::String pResourceFilename)
{
  Ogre::ConfigFile configFile;
  configFile.load(pResourceFilename);
  Ogre::ConfigFile::SectionIterator sectionItr = configFile.getSectionIterator();

  while (sectionItr.hasMoreElements())
  {
   Ogre::String secName = sectionItr.peekNextKey();
   Ogre::ConfigFile::SettingsMultiMap *settings = sectionItr.getNext();
   for (Ogre::ConfigFile::SettingsMultiMap::iterator itr = settings->begin(); itr != settings->end(); ++itr)
   {
    Ogre::ResourceGroupManager::getSingleton().addResourceLocation(itr->second, itr->first, secName);
  }
}
Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void IndieGame::Bomberman::initOIS()
{
  OIS::ParamList pl;size_t windowHnd = 0;
  std::ostringstream windowHndStr;
  _pRenderWindow->getCustomAttribute("WINDOW", &windowHnd);
  windowHndStr << windowHnd;
  pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
  _pInputManager = OIS::InputManager::createInputSystem( pl );

  _pMouse = static_cast<OIS::Mouse*>(_pInputManager->createInputObject(OIS::OISMouse, false));
  _pKeyboard = static_cast<OIS::Keyboard*>(_pInputManager->createInputObject(OIS::OISKeyboard, false));

  unsigned int width, height, depth;
  int top, left;
  _pRenderWindow->getMetrics(width, height, depth, left, top);
  const OIS::MouseState &ms = _pMouse->getMouseState();
  ms.width = width;
  ms.height = height;
  _input = new IndieGame::Input(DEFAULT_INPUT);
}

void IndieGame::Bomberman::initOgre()
{
  _pRoot = new Ogre::Root("bin/plugins.cfg", "bin/ogre.cfg", "");
  _pRoot->setRenderSystem(_pRoot->getRenderSystemByName("OpenGL Rendering Subsystem"));
  _pRenderWindow = _pRoot->initialise(true, "Bomberman");
  _pSceneManager = _pRoot->createSceneManager(Ogre::ST_GENERIC, "SceneManager");
  _pSceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
  _pCamera = _pSceneManager->createCamera("MainCamera");
  _pViewport = _pRenderWindow->addViewport(_pCamera);
  _pLight = _pSceneManager->createLight("MainLight");
  _pCamera->setPosition(Ogre::Vector3(0, 1400, 1400));
  _pCamera->lookAt(Ogre::Vector3(0, 0, 200));
  _pLight->setPosition(0, 1000, 0);
}

std::vector<OIS::KeyCode> IndieGame::Bomberman::manageInput()
{
  std::vector<OIS::KeyCode> inputs;

  _pKeyboard->capture();
  for (auto it = _players.begin(); it < _players.end(); ++it)
  {
    if (_pKeyboard->isKeyDown(_input->getKeyDown((*it)->getName() + std::string("_right"))))
      inputs.push_back(_input->getKeyDown((*it)->getName() + std::string("_right")));
    if (_pKeyboard->isKeyDown(_input->getKeyDown((*it)->getName() + std::string("_left"))))
      inputs.push_back(_input->getKeyDown((*it)->getName() + std::string("_left")));
    if (_pKeyboard->isKeyDown(_input->getKeyDown((*it)->getName() + std::string("_up"))))
      inputs.push_back(_input->getKeyDown((*it)->getName() + std::string("_up")));
    if (_pKeyboard->isKeyDown(_input->getKeyDown((*it)->getName() + std::string("_down"))))
      inputs.push_back(_input->getKeyDown((*it)->getName() + std::string("_down")));
    if (_pKeyboard->isKeyDown(_input->getKeyDown((*it)->getName() + std::string("_space"))))
      inputs.push_back(_input->getKeyDown((*it)->getName() + std::string("_space")));
    if (_pKeyboard->isKeyDown(_input->getKeyDown("escape")))
      inputs.push_back(_input->getKeyDown("escape"));
  }
  return (inputs);
}

bool 	IndieGame::Bomberman::displayMap()
{
  std::stringstream 		name;

  for (int i = 0; i < _map->getHeight(); ++i)
  {
    for (int j = 0; j < _map->getWidth(); ++j)
    {
      if (_map->getMap()[i][j] == 1)
      {
	name << "Wall" << i << ":" << j;
	_wall.push_back(dynamic_cast<IndieGame::Wall *>(_entityManager->createEntity<IndieGame::Wall>(_pSceneManager, _input, name.str(), "crate.mesh", Ogre::Vector3(_map->getWorldPosX(j), 0, _map->getWorldPosY(i)))));
      }
      else if (_map->getMap()[i][j] == 3)
      {
	name << "Wall_undestructible" << i << ":" << j;
	_wall_undestructible.push_back(dynamic_cast<IndieGame::Wall *>(_entityManager->createEntity<IndieGame::Wall>(_pSceneManager, _input, name.str(), "crate_undestruct.mesh", Ogre::Vector3(_map->getWorldPosX(j), 0, _map->getWorldPosY(i)))));
      }
      name.clear();
      name.str("");
    }
  }
  return (true);
}

bool IndieGame::Bomberman::createMap(const Ogre::String & name)
{
  _map = new IndieGame::Map(name);
  if (!_map->getMap())
    return (false);
  Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
  Ogre::MeshManager::getSingleton().createPlane(name, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
    _map->getWidth() * RATIO_MAP, _map->getHeight() * RATIO_MAP, 20, 20,  true,  1, 5, 5, Ogre::Vector3::UNIT_Z);
  _pGroundEntity = _pSceneManager->createEntity(name);
  _pSceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(_pGroundEntity);
  _pGroundEntity->setCastShadows(false);
  _pGroundEntity->setMaterialName("Plane/Skin");
  _pCamera->setPosition(Ogre::Vector3(0, _map->getWidth() * RATIO_MAP, _map->getHeight() * RATIO_MAP * 0.7));
  _pCamera->lookAt(Ogre::Vector3(0, 0, _map->getHeight() * RATIO_MAP * 0.12));
  return (true);
}

void			IndieGame::Bomberman::createExplosions(std::vector<Ogre::Vector3> *fire_tiles)
{
  int			i;
  int			j;
  std::stringstream	name;

  for (auto it = fire_tiles->begin(); it < fire_tiles->end(); it++)
    {
      i = (*it).x;
      j = (*it).z;
      if (j < _map->getHeight() && i < _map->getWidth() && j >= 0 && i >= 0 &&
	  _map->getMap()[j][i] != 6 && _map->getMap()[j][i] != 3)
	{
	  
	  name << "Wall Explosion" << _explosion_count << "," << j;
	  _explosion.push_back(dynamic_cast<IndieGame::Explosion *>(_entityManager->createEntity<IndieGame::Explosion>(_pSceneManager, _input, name.str(), "crate_explode.mesh", Ogre::Vector3(_map->getWorldPosX(i), 0, _map->getWorldPosY(j)))));
	  _explosion_count++;
	}
    }
}

void			IndieGame::Bomberman::print(IndieGame::Map *map) const
{
  for (int i = 0; i < map->getHeight(); ++i) {
    for (int j = 0; j < map->getWidth(); ++j) {
      std::cout << map->getMap()[i][j];
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

bool	IndieGame::Bomberman::loadSplash(const std::string & name)
{
  std::vector<OIS::KeyCode>	inputs;
  std::ifstream			infile(name);
  std::string			line;

  if (!infile.good())
  {
    std::cerr << "Failed to load splash: " << name << std::endl;
    return (false);
  }

  while (std::getline(infile, line))
  {
    std::istringstream 	iss(line);
    std::string 	map_line;

    if (!(iss >> map_line))
      break;
    _splashScreen.push_back(static_cast<OIS::KeyCode>(std::atoi(map_line.c_str())));
  }
  return (true);
}

void			IndieGame::Bomberman::bzeroMap()
{
  for (int i = 0; i < _map->getHeight(); ++i) {
    for (int j = 0; j < _map->getWidth(); ++j) {
      if (_map->getMap()[i][j] != 3)
	_map->getMap()[i][j] = 0;
    }
  }
}

bool			IndieGame::Bomberman::splashScreen(const std::string & name)
{
  std::vector<OIS::KeyCode>	to_do;

  if (_start != 0 && _start >= _splashScreen.size()) {
    return (true);
  }

  if (_players.size() == 0) {
    createPlayers(1);
    if (!loadSplash(name))
      return (true);
    bzeroMap();
    _splash = _entityManager->createEntity<IndieGame::Entity>(_pSceneManager, _input, "SPLASH",
						    "text.mesh", Ogre::Vector3(_map->getWorldPosX(2), 80,
									       _map->getWorldPosY(_map->getHeight() / 2)));
    _splash->getNode()->scale(140, 140, 140);
    _soundEngine->play2D(_splashSound);
  }
  if (!(*_players.begin())->goTo(_map, _input, _input->getKeyDown("escape"))) {
    (*_players.begin())->goTo(_map, _input, _input->getKeyDown("unknown"));
  } else {
    (*_players.begin())->goTo(_map, _input, _splashScreen.at(_start));
    _start++;
  }

  if (_start >= _splashScreen.size()) {
    _splash->destroy(_pSceneManager);
    delete _splash;
    restartGame();
    this->_gui->setState(MENU);
    _soundEngine->stopAllSounds();
    _soundEngine->play2D(_baseSound);
    return (true);
  }
  return (false);
}

bool      IndieGame::Bomberman::manageGame()
{
  std::vector<OIS::KeyCode>            inputs;
  std::vector<Ogre::Vector3>           powerups;
  std::vector<Ogre::Vector3>           fire_tiles;
  std::string				name;

  inputs = manageInput();
  for (auto it = _players.begin(); it < _players.end(); ++it)
  {
    if (!(*it)->managePowerups(_pSceneManager, _powerUpManager, _map, _input, inputs))
      return (false);
    if (!(*it)->managePosition(_map, _input, inputs))
      return (false);
    if (!(*it)->manageEvents(_pSceneManager, _entityManager, _map, _input, inputs))
      return (false);
    powerups = (*it)->manageBombs(_pSceneManager, _map, &_wall, _powerUpManager, &_players, &fire_tiles);
    createExplosions(&fire_tiles);
    if (!_powerUpManager->managePowerUps(_pSceneManager, _input, _entityManager, _map, powerups))
      return (false);
    name = (*_players.begin())->getName();
    if (!(*it)->isAlive())
    {
      (*it)->destroy(_pSceneManager);
      it = _players.erase(it);
    }
    if (_players.size() <= 1)
    {
      this->_gui->setMytext(name + " WINNNNNNS", CEGUI::USize(CEGUI::UDim(0.20, 0), CEGUI::UDim(0.09, 0)), 300, 150);
      this->_gui->displayText();
    }
    //print(_map);
  }
  return (true);
}

bool IndieGame::Bomberman::menu()
{
  const OIS::MouseState &move = _pMouse->getMouseState();
  if (this->_gui->isMenu())
  {
    if (this->_gui->getNewGame())
    {
      this->_gui->setNewGame(false);
      this->restartGame();
    }
    this->_gui->displayButton();
    this->_gui->mouseMoved(move);
    this->_gui->whereIsMouse(move);
    if (this->_gui->isButtonExitPressInMenu())
      return (false);
  }
  return (true);
}

bool IndieGame::Bomberman::pause()
{
  std::string	saveFile;
  const OIS::MouseState &move = _pMouse->getMouseState();

  this->_gui->mouseMoved(move);
  if (this->_gui->isPause())
  {
    if (!this->_gui->getPauseContainer().isVisible())
      this->_gui->displayButton();
    this->_gui->whereIsMouse(move);
    if (this->_gui->getWantSave())
    {
      saveFile = this->_save->saveGame(_players, _map, _input, true);
      this->_gui->displayText();
      this->_gui->setMytext("Game saved in file " + saveFile, CEGUI::USize(CEGUI::UDim(0.35, 0), CEGUI::UDim(0.09, 0)), 750, 150);
      this->_gui->setWantSave(false);
    }
    if (_gui->_drawMap)
    {
      this->_gui->setState(IndieGame::state::GAME);
      if (!this->restartGame())
        return (false);
      this->createPlayers(this->_gui->getNbPlayers());
      this->displayMap();
      _gui->setDrawMap(false);
      _gui->_drawMap = false;
    }
  }
  return (true);
}

bool IndieGame::Bomberman::game()
{
  if (this->_gui->isGame())
  {
    if (!this->_gui->isAllMenuDesactived())
      this->_gui->displayButton();
    if (_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
      this->_gui->setState(PAUSE);
    if (!manageGame())
      return (false);
  }
  return (true);
}

bool IndieGame::Bomberman::loadGame()
{
  const OIS::MouseState &move = _pMouse->getMouseState();
  if (this->_gui->isLoadGame())
  {
    this->_gui->createSaveDir();
    this->_gui->getSaveInDir();
    if (_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
      this->_gui->setState(MENU);
    this->_gui->mouseMoved(move);
    this->_gui->whereIsMouse(move);
    this->_gui->displayButton();
    if (!this->_gui->getSave().empty())
    {
      std::string file("save/");
      file += this->_gui->getLoadButton()[this->_gui->getSave()]->getText().c_str();
      this->_map->setMap(file, false);
      this->createPlayers(this->_save->getNbPlayersOnSaveFile(file));
      this->loadPlayerConfiguration(file);
      this->_input->setInputs(file);
      this->displayMap();
      _gui->setDrawMap(false);
      _gui->_drawMap = false;


      this->_gui->getSave().clear();
      this->_gui->setSave("");
      this->_gui->setState(GAME);
    }
  }
  return (true);
}

void IndieGame::Bomberman::loadPlayerConfiguration(const std::string & file) {

  for (auto it = _players.begin(); it < _players.end(); ++it) {
    (*it)->loadConfiguraton(file);
  }
}

void IndieGame::Bomberman::runThread()
{
  sleep(WAIT_FOR_AUTOSAVE);
  while (1)
  {
    if (this->_gui->isGame())
      _save->saveGame(_players, _map, _input, false);
    sleep(WAIT_FOR_AUTOSAVE);
  }
}

bool IndieGame::Bomberman::chooseIA()
{
  boost::shared_ptr<boost::thread> mThread;
  const OIS::MouseState &move = _pMouse->getMouseState();
  if (this->_gui->getState() == IA)
  {
    this->_gui->whereIsMouse(move);
    if (!this->_gui->getIAContainer().isVisible())
      this->_gui->displayButton();
    if (_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
    {
      this->_gui->setValueByDefault();
      this->_gui->setState(CHOOSEPLAYER);
    }
    if (this->_gui->isGame())
    {
      this->_gui->setMytext("Loading Game ....", CEGUI::USize(CEGUI::UDim(0.35, 0), CEGUI::UDim(0.09, 0)), 750, 150);
      this->_gui->displayText();
      createPlayers(this->_gui->getNbPlayers());
      displayMap();
      this->_soundEngine->stopAllSounds();
      this->_soundEngine->play2D(_gameSound);
      if (this->_gui->getSound())
	this->_soundEngine->setSoundVolume(0.5f);
      else
	this->_soundEngine->setSoundVolume(0);
      assert(!mThread);
      mThread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&IndieGame::Bomberman::runThread, this)));
      this->_gui->setState(GAME);
    }
  }
  return (true);
}

bool IndieGame::Bomberman::option()
{
  const OIS::MouseState &move = _pMouse->getMouseState();
  if (this->_gui->isOption())
  {
    this->_gui->whereIsMouse(move);
    if (!this->_gui->getChoosePlayerContainer().isVisible())
      this->_gui->displayButton();
    if (_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
    {
      this->_gui->setValueByDefault();
      this->_gui->setState(MENU);
    }
  }
  return (true);
}

bool IndieGame::Bomberman::choosePlayer()
{
  const OIS::MouseState &move = _pMouse->getMouseState();
  if (this->_gui->isChoosePlayer())
  {
    this->_gui->whereIsMouse(move);
    if (!this->_gui->getChoosePlayerContainer().isVisible())
      this->_gui->displayButton();
    if (_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
    {
      this->_gui->setValueByDefault();
      this->_gui->setState(MENU);
    }
  }
  return (true);
}

void	IndieGame::Bomberman::manageExplosions()
{
  for (auto it = _explosion.begin(); it < _explosion.end(); ++it)
    {
      if (static_cast<double>((std::clock() - (*it)->getTime()) / (CLOCKS_PER_SEC / 1000)) > EX_DURATION)
	{
	  (*it)->destroy(_pSceneManager);
	  _explosion.erase(it);
	}
    }
}

bool IndieGame::Bomberman::frameStarted(const Ogre::FrameEvent &evt)
{
  if (this->_gui->getSound())
    this->_soundEngine->setSoundVolume(0.5f);
  else
    this->_soundEngine->setSoundVolume(0);
  static_cast<void>(evt);
  _pMouse->capture();
  _pKeyboard->capture();
  if (!this->pause() || !this->menu() || !this->game() || !this->choosePlayer() || !this->chooseIA() || !this->loadGame() || !this->option())
    return (false);
  manageExplosions();
  for (unsigned int a = 0; a < _players.size(); a++)
    _players[a]->getAnimation()->addTime(evt.timeSinceLastFrame * 3);
  if (!splashScreen(DEFAULT_SPLASH))
    return (true);
  return (true);
}

bool IndieGame::Bomberman::frameEnded(const Ogre::FrameEvent &evt)
{
  static_cast<void>(evt);
  return (true);
}


void  IndieGame::Bomberman::createPlayers(int nb)
{
  Ogre::Vector3   pos;

  while (nb > 0)
  {
    pos = _map->getPlayerPos(nb);
    pos.x = _map->getWorldPosX(pos.x);
    pos.z = _map->getWorldPosY(pos.z);
    _players.push_back(dynamic_cast<IndieGame::Player *>(_entityManager->createEntity<IndieGame::Player>(_pSceneManager, _input, std::string(DEFAULT_PLAYERNAME) + std::to_string(nb), "ArmyPilot" + std::to_string(nb) + ".mesh", pos)));
    nb--;
  }
}

bool IndieGame::Bomberman::startGameWithParameters(const std::string &file) {
  static_cast<void>(file);
  this->_gui->setState(IndieGame::state::GAME);
  this->createPlayers(this->_gui->getNbPlayers());
  return (true);
}

bool    IndieGame::Bomberman::restartGame()
{
  for (auto it = _players.begin(); it < _players.end(); ++it)
  {
    (*it)->destroyBombs(_pSceneManager);
    (*it)->destroy(_pSceneManager);
  }
  _players.clear();
  for (auto it = _wall.begin(); it < _wall.end(); ++it)
    (*it)->destroy(_pSceneManager);
  _wall.clear();
  for (auto it = _wall_undestructible.begin(); it < _wall_undestructible.end(); ++it)
    (*it)->destroy(_pSceneManager);
  _wall_undestructible.clear();
  _powerUpManager->clear(_pSceneManager);
  delete _map;
  _map = new IndieGame::Map(std::string(MAP_DIR) + std::string("level1.indie"));
  if (!_map->getMap())
    return (false);
  return (true);
}

void  IndieGame::Bomberman::loadBackground(const Ogre::String & name)
{
 Ogre::Entity*      _pBackgroundEntity;

 Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -100);
 Ogre::MeshManager::getSingleton().createPlane(name, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
  _pRenderWindow->getWidth() * 2, _pRenderWindow->getHeight() * 2, 1, 1,  true,  1, 5, 5, Ogre::Vector3::UNIT_Z);
 _pBackgroundEntity = _pSceneManager->createEntity(name);
 _pSceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(_pBackgroundEntity);
 _pBackgroundEntity->setCastShadows(false);
 _pBackgroundEntity->setMaterialName("Background/Skin");
}

bool IndieGame::Bomberman::start()
{
  initOgre();
  initOIS();
  loadRessources(DEFAULT_RESSOURCES);
  loadBackground("background");
  if (!createMap(std::string(MAP_DIR) + std::string("level1.indie")))
    return (false);
  _pRoot->addFrameListener(this);
  return (true);
}

void IndieGame::Bomberman::run()
{
  _gui = new IndieGame::GUI(_pRoot, _pRenderWindow->getWidth(), _pRenderWindow->getHeight());
  _pRoot->startRendering();
}

void IndieGame::Bomberman::exit()
{
  //delete _pRoot;
}
