//
// arcade.cpp for arcade in /home/tekm/tek2/cpp_arcade
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Tue Mar  7 14:10:26 2017 leroy_0
// Last update Tue Mar  7 14:10:36 2017 leroy_0
//

#include "Manager.hpp"

arcade::Manager::Manager(const int & argc, char ** argv)
{
	this->_core = new Core;
	try {
		if (argc == 2)
		{
			this->_core->load(argv[1]);
		}
		else
			throw arcade::Error(std::cerr, "You should specify only one library");
	}
	catch (const arcade::Error & e) {
		e.getOs() << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}

void 		arcade::Manager::run()
{
  try
  {
    this->_core->run();
  }
  catch (const arcade::Error & e)
  {
    e.getOs() << e.what() << std::endl;
    delete this->_core;
    exit(EXIT_FAILURE);
  }
  delete this->_core;
}