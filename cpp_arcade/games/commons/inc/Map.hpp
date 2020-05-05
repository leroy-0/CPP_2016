//
// Map.hpp for Map in /home/tekm/tek2/cpp_arcade/games/nibbler
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Tue Mar  7 15:47:04 2017 leroy_0
// Last update Tue Mar  7 15:47:04 2017 leroy_0
//

#ifndef					__MAP_HPP_
#define					__MAP_HPP_

#include				"Protocol.hpp"
#include				<iostream>

class					Map
{
	public:
		Map(const uint16_t & width, const uint16_t & height);
		virtual ~Map() {};

		arcade::GetMap		*getMap(); 

		arcade::TileType	getTypeTilefromPos(int x, int y);
	private:
		arcade::GetMap		*_map;
};

#endif