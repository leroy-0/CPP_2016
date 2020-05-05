//
// Input.cpp for input in /home/tekm/tek2/cpp_indie_studio
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Tue Jun 13 18:37:06 2017 leroy_0
// Last update Sun Jun 18 21:31:11 2017 Adrien Bachelet
//

#include		"Input.hpp"
#include		"Bomberman.hpp"

IndieGame::Input::Input(const std::string & conf_file)
{
  setInputs(conf_file);
}

IndieGame::Input::~Input()
{
  
}

bool			IndieGame::Input::setInputs(const std::string & conf_file)
{
  std::ifstream		infile(conf_file);
  std::string		line;

  if (!infile.good())
    {
      std::cerr << "Failed to load input file: " << conf_file << std::endl;
      return (false);
    }
  while (std::getline(infile, line))
    {
      std::istringstream	iss(line);
      std::string			attribute;
      std::string			value;
      
      if (!(iss >> attribute))
	break;
      if (!(iss >> value))
	break;
      if (attribute.find(DEFAULT_PLAYERNAME) != std::string::npos)
	{
	  _names.push_back(attribute);
	  _values.push_back(static_cast<OIS::KeyCode>(std::atoi(value.c_str())));
	}
    }
  return (true);
}

OIS::KeyCode		IndieGame::Input::getKeyDown(const std::string & name) const
{
  int	x = 0;
  
  for (auto it = _names.begin(); it < _names.end(); ++it)
    {
      if ((*it) == name)
	return (_values.at(x));
      x++;
    }
  return (static_cast<OIS::KeyCode>(0));
}
