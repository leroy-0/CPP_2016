//
// main.cpp for main in /home/tekm/tek2/cpp_arcade
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Tue Mar  7 14:12:42 2017 leroy_0
// Last update Tue Mar  7 14:21:04 2017 leroy_0
//

#include <ctime>
#include <cstdlib>
#include "Manager.hpp"

int		main(int argc, char **argv)
{
	arcade::Manager 		manager(argc, argv);

	std::srand(std::time(NULL));
	manager.run();
}