//
// Input.hpp for Input in /home/tekm/tek2/cpp_indie_studio
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Tue Jun 13 18:37:17 2017 leroy_0
// Last update Tue Jun 13 18:37:17 2017 leroy_0
//

#ifndef				__INPUT__
#define				__INPUT__

#include			<iostream>
#include			"Map.hpp"

namespace			IndieGame
{
  class				Input
  {
  public:
    Input(const std::string & conf_file);
    ~Input();

    bool			setInputs(const std::string & conf_file);
    OIS::KeyCode		getKeyDown(const std::string & name) const;

  private:
    std::vector<std::string> 	_names;
    std::vector<OIS::KeyCode> 	_values;
  };
};

#endif 	/* __INPUT__ */