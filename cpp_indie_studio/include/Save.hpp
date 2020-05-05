/*
** Save.hpp for cpp_indie_studio in /home/bruere_s/Projets/cpp_indie_studio/include/Save.hpp
**
** Made by Sebastien Bruere
** Login   <sebastien.bruere@epitech.eu>
**
** Started on  Fri Jun 16 11:40:01 2017 Sebastien Bruere
** Last update Fri Jun 16 11:40:01 2017 Sebastien Bruere
*/

#pragma once

#include			<dirent.h>
#include			<string>
#include			"Player.hpp"

namespace			IndieGame {

  class				Save {
  public:
    Save();
    virtual ~Save();

    std::string			saveGame(std::vector<IndieGame::Player *> &, IndieGame::Map *, IndieGame::Input *, bool);
    void			loadGame(const std::string &);
    void			createSaveDir();
    std::string			getDate();
    std::string			getActualMap(IndieGame::Map *);
    std::vector<std::string>	getSaveInDir();
    std::string			getNewFileName();
    std::string			getNewAutoFileName();
    int				getNbPlayersOnSaveFile(const std::string & file);

  protected:
    DIR				*_dir;
    struct dirent		*_ent;
    std::string			_fileName;
    int				_nbSave;
    std::vector<std::string>	_files;
  };
}
