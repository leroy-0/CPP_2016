//
// Pacmap.hpp for Pacmap in /home/tekm/tek2/cpp_arcade/games/nibbler
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Tue Mar  7 15:47:04 2017 leroy_0
// Last update Tue Mar  7 15:47:04 2017 leroy_0
//

#ifndef __PACMAP_HPP_
#define __PACMAP_HPP_

#include "Protocol.hpp"
#include <iostream>

class Pacmap
{
	public:
		Pacmap(const std::string & mapname);
		virtual ~Pacmap() {};

		arcade::GetMap 		*getMap();
		void 				loadMap(const std::string & mapname);
		arcade::TileType    getTypeTilefromPos(int x, int y);
	private:
		arcade::GetMap 		*_map;
};

#endif