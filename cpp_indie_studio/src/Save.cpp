/*
** Save.cpp for cpp_indie_studio in /home/bruere_s/Projets/cpp_indie_studio/src/Save.cpp
**
** Made by Sebastien Bruere
** Login   <sebastien.bruere@epitech.eu>
**
** Started on  Fri Jun 16 11:41:33 2017 Sebastien Bruere
// Last update Sun Jun 18 21:29:13 2017 Adrien Bachelet
*/

#include			"Save.hpp"
#include			"Bomberman.hpp"

IndieGame::Save::Save()
{
  createSaveDir();
  getSaveInDir();
}
IndieGame::Save::~Save()
{
  closedir(_dir);
}
std::string			IndieGame::Save::getNewAutoFileName()
{
  std::ostringstream		name;

  createSaveDir();
  getSaveInDir();
  for (auto it = _files.begin(); it < _files.end(); ++it)
    {
      if ((*it).find("(autosave)") != std::string::npos)
	{
	  std::remove(("save/" + (*it)).c_str());
	}
    }
  name << "save/(autosave)-" << getDate();
  std::string str = name.str();
  _fileName = name.str();
  return (str.c_str());
}

std::string			IndieGame::Save::getNewFileName()
{
  int				nb;
  int				nbFile;
  std::ostringstream		name;

  nb = 0;
  nbFile = 0;
  createSaveDir();
  getSaveInDir();
  for (auto it = _files.begin(); it < _files.end(); ++it)
    {
      nb = (*it).at(5) - '0';
      if (nb == nbFile)
	nbFile++;
    }
  name << "save/save_" << nbFile << "-" << getDate();
  std::string str = name.str();
  _fileName = name.str();
  return (str.c_str());
}


int				IndieGame::Save::getNbPlayersOnSaveFile(const std::string &file)
{
  std::ifstream			infile(file);
  std::string			line;
  int				nb;
  
  nb = 0;
  if (!infile.good())
    {
      std::cerr << "Failed to load save file : " << file << std::endl;
      return (-1);
    }
  while (std::getline(infile, line))
    {
      std::istringstream	iss(line);
      std::string		save_line;
      
      iss >> save_line;
      if (save_line.find(DEFAULT_PLAYERNAME) != std::string::npos)
	{
	  if (save_line.at(7) - '0' > nb)
	    nb = save_line.at(7) - '0';
	}
  }
  return (nb);
}

std::string			IndieGame::Save::saveGame(std::vector<IndieGame::Player *> & players,
							  IndieGame::Map *map, IndieGame::Input *input,
							  bool mode)
{
  std::ofstream			saveFile;

  if (mode)
    saveFile.open(getNewFileName().c_str());
  else
    saveFile.open(getNewAutoFileName().c_str());
  saveFile << getActualMap(map);
  for (auto it = players.begin(); it < players.end(); ++it)
    {
      if (input->getKeyDown((*it)->getName() + std::string("_right")))
	saveFile << (*it)->getName() << "_right " << input->getKeyDown((*it)->getName() + std::string("_right")) << std::endl;
      if (input->getKeyDown((*it)->getName() + std::string("_left")))
	saveFile << (*it)->getName() << "_left " << input->getKeyDown((*it)->getName() + std::string("_left")) << std::endl;
      if (input->getKeyDown((*it)->getName() + std::string("_up")))
	saveFile << (*it)->getName() << "_up " << input->getKeyDown((*it)->getName() + std::string("_up")) << std::endl;
      if (input->getKeyDown((*it)->getName() + std::string("_down")))
	saveFile << (*it)->getName() << "_down " << input->getKeyDown((*it)->getName() + std::string("_down")) << std::endl;
      if (input->getKeyDown((*it)->getName() + std::string("_space")))
	saveFile << (*it)->getName() << "_space " << input->getKeyDown((*it)->getName() + std::string("_space")) << std::endl;
      if (input->getKeyDown("escape"))
	saveFile << (*it)->getName() << "_escape " << input->getKeyDown((*it)->getName() + std::string("espace")) << std::endl;
      
      saveFile << (*it)->getName() << "_posX " << (*it)->getPosition().x << std::endl;
      saveFile << (*it)->getName() << "_posY " << (*it)->getPosition().z << std::endl;
      saveFile << (*it)->getName() << "_limitBomb " << (*it)->getLimitBomb() << std::endl;
      saveFile << (*it)->getName() << "_bombRange " << (*it)->getBombRange() << std::endl;
      saveFile << (*it)->getName() << "_speedX " << (*it)->getSpeedX() << std::endl;
      saveFile << (*it)->getName() << "_speedY " << (*it)->getSpeedY() << std::endl;
      saveFile << (*it)->getName() << "_alive " << (*it)->isAlive() << std::endl;
    }
  saveFile.close();
  return (_fileName);
}

void				IndieGame::Save::createSaveDir()
{
  if ((_dir = opendir("save")) == NULL)
    {
      mkdir("save", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
      _dir = opendir("save");
    }
}

std::string			IndieGame::Save::getDate()
{
  std::ostringstream		date;
  std::time_t			t = time(0);
  struct tm			*now = localtime(&t);
  
   date << now->tm_mday << ":" << (now->tm_mon + 1) << ":"
	<< std::to_string((now->tm_year + 1900)).c_str()
	<< "-" << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec;
   return (date.str());
}

std::string			IndieGame::Save::getActualMap(IndieGame::Map *map) {
  std::ostringstream		saveFile;

  for (int i = 0; i < map->getHeight(); ++i)
    {
      for (int j = 0; j < map->getWidth(); ++j)
	{
	  saveFile << map->getMap()[i][j];
	}
      saveFile << std::endl;
    }
  saveFile << std::endl;
  return (saveFile.str());
}

std::vector<std::string>	IndieGame::Save::getSaveInDir()
{
  _nbSave = 0;
  while ((_ent = readdir(_dir)) != NULL)
    {
      _nbSave++;
      if (_ent->d_name[0] != '.')
	_files.push_back(std::string(_ent->d_name));
    }
  return (_files);
}
void				IndieGame::Save::loadGame(const std::string & name)
{
  static_cast<void>(name);
}
