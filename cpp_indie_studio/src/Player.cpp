//
// Player.cpp for Player in /home/tekm/tek2/cpp_indie_studio
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Wed May 31 13:37:00 2017 leroy_0
// Last update Sun Jun 18 21:37:44 2017 Adrien Bachelet
//

#include				<iostream>
#include				"Bomberman.hpp"
#include				"Bomb.hpp"
#include				"Player.hpp"

IndieGame::Player::Player(const std::string & name, Ogre::Entity * ent, Ogre::SceneNode* node, const OIS::KeyCode dir)
  : Entity(name, ent, node, dir), _animation(0)
{
  _speedx = SPEED_X;
  _speedy = SPEED_Y;
  _limitBomb = BOMB_LIMIT;
  _activeBombs = 0;
  _bombRange = 0;
  _alive = true;
  _animation = oEntity->getAnimationState("Idle");
  _animation->setLoop(true);
  _animation->setEnabled(true);
  this->setPosition(Ogre::Vector3(getPosition().x, Y_POS, getPosition().z));
  _soundEngine = irrklang::createIrrKlangDevice();
  _soundEngine->setSoundVolume(0.5f);
  _gameSound = _soundEngine->addSoundSourceFromFile("media/sound/explosion.ogg");
  _deathSound =  _soundEngine->addSoundSourceFromFile("media/sound/death_1.ogg");
  _oldPos = getPosition();
}

IndieGame::Player::~Player()
{
  
}

bool					IndieGame::Player::loadConfiguraton(const std::string & file) {
  std::ifstream				infile(file);
  std::string				line;
  size_t				find;
  std::string				attribut;
  std::string				value;
  Ogre::Vector3				pos;

  if (!infile.good())
    {
      std::cerr << "Failed to load save file : " << file << std::endl;
      return (false);
    }
  while (std::getline(infile, line))
    {
      std::istringstream		iss(line);
      iss >> attribut;
      iss >> value;
      if ((find = attribut.find(this->getName())) != std::string::npos)
	{
	  attribut = attribut.substr(find + this->getName().length() + 1, attribut.length());
	  if (attribut.compare("limitBomb") == 0)
	    this->_limitBomb = std::atoi(value.c_str());
	  else if (attribut.compare("bombRange") == 0)
	    this->_bombRange = std::atoi(value.c_str());
	  else if (attribut.compare("speedX") == 0)
	    this->_speedx = std::atoi(value.c_str());
	  else if (attribut.compare("speedY") == 0)
	    this->_speedy = std::atoi(value.c_str());
	  else if (attribut.compare("posX") == 0)
	    pos.x = std::atoi(value.c_str());
	  else if (attribut.compare("posY") == 0)
	    pos.z = std::atoi(value.c_str());
	}
    }
  pos.y = Y_POS;
  this->setPosition(pos);
  return (true);
}

bool					IndieGame::Player::isAlive() const
{
  return (_alive);
}

bool					IndieGame::Player::isBombReady() const
{
  return (_activeBombs < _limitBomb);
}

void					IndieGame::Player::eatPowerup(IndieGame::Powerup *powerup)
{
  _speedx = (_speedx + powerup->getSpeedX() < SPEED_X ? SPEED_X : _speedx + powerup->getSpeedX());
  _speedy = (_speedy + powerup->getSpeedY() < SPEED_Y ? SPEED_Y : _speedy + powerup->getSpeedY());
  _limitBomb = (_limitBomb + powerup->getLimitBomb() < 1 ? 1 : _limitBomb + powerup->getLimitBomb());
  _bombRange = (_bombRange + powerup->getBombRange() < 0 ? 0 : _bombRange + powerup->getBombRange());
}

bool					IndieGame::Player::managePowerups(Ogre::SceneManager *pSceneManager, IndieGame::PowerUpManager *powerUpManager, IndieGame::Map *map, IndieGame::Input *inputManager, std::vector<OIS::KeyCode> inputs)
{
  std::vector<IndieGame::Powerup *> 	powerups;
  Ogre::Vector3				pos;
  OIS::KeyCode 				dir;
  int 					to_add;
  
  powerups = powerUpManager->getAll();
  for (auto it = inputs.begin(); it < inputs.end(); ++it)
    {
      to_add = 0;
      dir = inputManager->getKeyDown("unknown");
      if ((*it) == inputManager->getKeyDown(getName() + std::string("_up")) || (*it) == inputManager->getKeyDown(getName() + std::string("_left")))
	to_add = -2;
      else if ((*it) == inputManager->getKeyDown(getName() + std::string("_right")) || (*it) == inputManager->getKeyDown(getName() + std::string("_down")))
	to_add = 2;
      if (dir == inputManager->getKeyDown("unknown") && ((((*it) == inputManager->getKeyDown(getName() + std::string("_up")) || (*it) == inputManager->getKeyDown(getName() + std::string("_down")))
							  && map->getMap()[map->getMapPosY(getPosition().z) + (to_add < 0 ? -1 : 1)][map->getMapPosX(getPosition().x)] == 4)
							 || (((*it) == inputManager->getKeyDown(getName() + std::string("_right")) || (*it) == inputManager->getKeyDown(getName() + std::string("_left")))
							     && map->getMap()[map->getMapPosY(getPosition().z)][map->getMapPosX(getPosition().x) + (to_add < 0 ? -1 : 1)] == 4)))
	dir = (*it);
      if (dir != inputManager->getKeyDown("unknown"))
	{
	  to_add = 0;
	  dir = inputManager->getKeyDown("unknown");
	  if ((*it) == inputManager->getKeyDown(getName() + std::string("_up")) || (*it) == inputManager->getKeyDown(getName() + std::string("_left")))
	    to_add = -1;
	  else if ((*it) == inputManager->getKeyDown(getName() + std::string("_right")) || (*it) == inputManager->getKeyDown(getName() + std::string("_down")))
	    to_add = 1;
	  
	  if (dir == inputManager->getKeyDown("unknown") && ((((*it) == inputManager->getKeyDown(getName() + std::string("_up")) || (*it) == inputManager->getKeyDown(getName() + std::string("_down")))
							      && map->getMap()[map->getMapPosY(getPosition().z) + to_add][map->getMapPosX(getPosition().x)] == 4)
							     || (((*it) == inputManager->getKeyDown(getName() + std::string("_right")) || (*it) == inputManager->getKeyDown(getName() + std::string("_left")))
								 && map->getMap()[map->getMapPosY(getPosition().z)][map->getMapPosX(getPosition().x) + to_add] == 4)))
	    dir = (*it);
	  if (dir != inputManager->getKeyDown("unknown"))
	    {
	      if (dir == inputManager->getKeyDown(getName() + std::string("_up")) || dir == inputManager->getKeyDown(getName() + std::string("_down")))
		pos = Ogre::Vector3(map->getMapPosX(getPosition().x), 0, map->getMapPosY(getPosition().z) + to_add);
	      else if (dir == inputManager->getKeyDown(getName() + std::string("_right")) || dir == inputManager->getKeyDown(getName() + std::string("_left")))
		pos = Ogre::Vector3(map->getMapPosX(getPosition().x) + to_add, 0, map->getMapPosY(getPosition().z));
	      for (auto pit = powerups.begin(); pit < powerups.end(); ++pit)
		{
		  if (map->getMapPosX((*pit)->getPosition().x) == pos.x
		      && map->getMapPosY((*pit)->getPosition().z) == pos.z)
		    {
		      eatPowerup(*pit);
		      powerUpManager->erase(pSceneManager, map, *pit);
		      return (true);
		    }
		}
	    }
	}
    }
  return (true);
}

bool					IndieGame::Player::managePosition(IndieGame::Map *map, IndieGame::Input *input, std::vector<OIS::KeyCode> inputs)
{
  OIS::KeyCode				dir;

  if (!goTo(map, input, input->getKeyDown("escape")))
    goTo(map, input, input->getKeyDown("unknown"));
  else
    {
      if (map->getMap()[map->getMapPosY(_oldPos.z)][map->getMapPosX(_oldPos.x)] == 2)
	map->getMap()[map->getMapPosY(_oldPos.z)][map->getMapPosX(_oldPos.x)] = 0;
      if (map->getMap()[map->getMapPosY(getPosition().z)][map->getMapPosX(getPosition().x)] == 0)
	map->getMap()[map->getMapPosY(getPosition().z)][map->getMapPosX(getPosition().x)] = 2;
      for (auto it = inputs.begin(); it < inputs.end(); ++it)
	{
	  dir = (*it);
	  if (!goTo(map, input, input->getKeyDown("escape")))
	    goTo(map, input, input->getKeyDown("unknown"));
	  else
	    {
	      _oldPos = getPosition();
	      goTo(map, input, dir);
	    }
	}
    }
  return (true);
}

void					IndieGame::Player::manageOneBomb(Ogre::SceneManager *pSceneManager, IndieGame::EntityManager *entityManager, IndieGame::Map *map, IndieGame::Input *input)
{
  Ogre::Vector3				pos;
  std::stringstream			name;
  
  if (isBombReady() && map->getMap()[map->getMapPosY(getPosition().z)][map->getMapPosX(getPosition().x)] != 5)
    {
      name << "Bomb_" << getName() << " " << map->getMapPosX(getPosition().x) << ":" << map->getMapPosY(getPosition().z);
      pos = Ogre::Vector3(map->getWorldPosX(map->getMapPosX(getPosition().x)), 0, map->getWorldPosY(map->getMapPosY(getPosition().z)));
      _bomb.push_back(dynamic_cast<IndieGame::Bomb *>(entityManager->createEntity<IndieGame::Bomb>(pSceneManager, input, name.str(), BOMB_MESH, pos)));
      map->getMap()[map->getMapPosY(pos.z)][map->getMapPosX(pos.x)] = 5;
      _activeBombs++;
    }
}

std::vector<Ogre::Vector3> 		IndieGame::Player::manageBombs(Ogre::SceneManager *pSceneManager, IndieGame::Map *map, std::vector<IndieGame::Entity *>  *walls, IndieGame::PowerUpManager *powerUpManager, std::vector<IndieGame::Player *>  *players, std::vector<Ogre::Vector3> *fire_tiles)
{
  std::vector<Ogre::Vector3>		destroyed;
  std::vector<Ogre::Vector3>		powerups;

  for (auto it = _bomb.begin(); it < _bomb.end(); ++it)
    {
      if ((*it)->checkTimer())
	{
	  destroyed = (*it)->destruction(map, _bombRange, fire_tiles, getPosition());
	  _soundEngine->play2D(_gameSound);
	  for (auto dit = destroyed.begin(); dit < destroyed.end(); ++dit)
	    {
	      (*it)->searchAndDestroyWalls(pSceneManager, map, walls, Ogre::Vector3((*dit).x, 0, (*dit).z));
	      (*it)->searchAndDestroyPowerUps(pSceneManager, map, powerUpManager, Ogre::Vector3((*dit).x, 0, (*dit).z));
	      if ((*it)->searchAndDestroyPlayers(pSceneManager, map, players, Ogre::Vector3((*dit).x, 0, (*dit).z), getPosition()))
		{
		  _soundEngine->play2D(_deathSound);
		  _alive = false;

		}
	    }
	  map->getMap()[map->getMapPosY((*it)->getPosition().z)][map->getMapPosX((*it)->getPosition().x)] = 0;
	  (*it)->destroy(pSceneManager);
	  _bomb.erase(it);
	  _activeBombs--;
	  for (auto it = destroyed.begin(); it < destroyed.end(); ++it)
	    powerups.push_back(*it);
	} else {
	(*it)->bombUp();
      }
    }
  return (powerups);
}

bool					IndieGame::Player::manageEvents(Ogre::SceneManager *pSceneManager, IndieGame::EntityManager *entityManager, IndieGame::Map *map, IndieGame::Input *input, std::vector<OIS::KeyCode> inputs)
{
  int					event;

  for (auto it = inputs.begin(); it < inputs.end(); ++it)
    {
      event = (*it);
      if (event == input->getKeyDown(getName() + std::string("_space")))
	manageOneBomb(pSceneManager ,entityManager, map, input);
    }
  return (true);

}

void					IndieGame::Player::destroyBombs(Ogre::SceneManager *pSceneManager)
{
  for (auto it = _bomb.begin(); it < _bomb.end(); ++it)
    (*it)->destroy(pSceneManager);
}

Ogre::AnimationState			*IndieGame::Player::getAnimation() const
{
  return (this->_animation);
}

void					IndieGame::Player::setAnimation(Ogre::AnimationState *animation)
{
  this->_animation = animation;
}


bool					IndieGame::Player::goTo(IndieGame::Map *map, IndieGame::Input *inputManager, OIS::KeyCode dir)
{
  if (inputManager->getKeyDown("escape") == dir && limit == 0)
    return (true);
  if (dir == inputManager->getKeyDown(getName() + std::string("_up")) || dir == inputManager->getKeyDown(getName() + std::string("_left")))
    to_add = -2;
  else if (dir == inputManager->getKeyDown(getName() + std::string("_right")) || dir == inputManager->getKeyDown(getName() + std::string("_down")))
    to_add = 2;
  if (_currentDir == inputManager->getKeyDown("unknown") &&
      (((dir == inputManager->getKeyDown(getName() + std::string("_up")) || dir == inputManager->getKeyDown(getName() + std::string("_down")))
	&& map->getMap()[map->getMapPosY(getPosition().z) + (to_add < 0 ? -1 : 1)][map->getMapPosX(getPosition().x)] == 0)
       || ((dir == inputManager->getKeyDown(getName() + std::string("_right")) || dir == inputManager->getKeyDown(getName() + std::string("_left")))
	   && map->getMap()[map->getMapPosY(getPosition().z)][map->getMapPosX(getPosition().x) + (to_add < 0 ? -1 : 1)] == 0)))
    {
      if (dir == inputManager->getKeyDown(getName() + std::string("_up")) || dir == inputManager->getKeyDown(getName() + std::string("_down")))
	setOrientation(Ogre::Vector3(getPosition().x + to_add, getPosition().y, getPosition().z));
      else if (dir == inputManager->getKeyDown(getName() + std::string("_right")) || dir == inputManager->getKeyDown(getName() + std::string("_left")))
	setOrientation(Ogre::Vector3(getPosition().x, getPosition().y, getPosition().z + (to_add > 0 ? -2 : 2)));
      _currentDir = dir;
    }
  if (_currentDir == inputManager->getKeyDown("unknown"))
    {
      _animation = oEntity->getAnimationState("Idle");
      _animation->setLoop(true);
      _animation->setEnabled(true);
      return (true);
    }
  _animation = oEntity->getAnimationState("Run_Forwards");
  _animation->setLoop(true);
  _animation->setEnabled(true);
  limit = RATIO_MAP;
  if (iterator < limit)
    {
      if (_currentDir == inputManager->getKeyDown(getName() + std::string("_up")) || _currentDir == inputManager->getKeyDown(getName() + std::string("_down")))
	setPosition(Ogre::Vector3(getPosition().x, Y_POS, getPosition().z + to_add));
      else if (_currentDir == inputManager->getKeyDown(getName() + std::string("_right")) || _currentDir == inputManager->getKeyDown(getName() + std::string("_left")))
	setPosition(Ogre::Vector3(getPosition().x + to_add, Y_POS, getPosition().z));
      iterator += (to_add < 0 ? to_add * -1 : to_add);
      return (false);
    }
  iterator = 0;
  limit = 0;
  to_add = 0;
  _currentDir = inputManager->getKeyDown("unknown");
  _animation = oEntity->getAnimationState("Idle");
  _animation->setLoop(true);
  _animation->setEnabled(true);
  return (true);
}

int					IndieGame::Player::getIsAlive() const {
  return (_alive);
}
int					IndieGame::Player::getactiveBomb() const {
  return (_activeBombs);
}

int					IndieGame::Player::getSpeedX() const
{
  return (_speedx);
}

int					IndieGame::Player::getSpeedY() const
{
  return (_speedy);
}

int					IndieGame::Player::getLimitBomb() const
{
  return (_limitBomb);
}

int					IndieGame::Player::getBombRange() const
{
  return (_bombRange);
}

void					IndieGame::Player::setOrientation(const Ogre::Vector3 mDestination)
{
  Ogre::Vector3 mDirection = mDestination - oNode->getPosition();
  Ogre::Vector3 src = oNode->getOrientation() * Ogre::Vector3::UNIT_X;
  src.y = 0;
  mDirection.y = 0;
  src.normalise();
  mDirection.normalise();

  if ((1.0f + src.dotProduct(mDirection)) < 0.0001f)
    oNode->yaw(Ogre::Degree(180));
  else
    {
      Ogre::Quaternion quat = src.getRotationTo(mDirection);
      oNode->rotate(quat);
    }
}
