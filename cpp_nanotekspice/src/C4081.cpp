//
// C4801.cpp for C4801 in /home/tekm/tek2/cpp_nanotekspice
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Mon Feb 27 19:55:49 2017 leroy_0
// Last update Mon Feb 27 19:55:51 2017 leroy_0
//

#include "C4081.hpp"

C4081::C4081(const std::string &name)
{
	setName(name);
	setType("4081");
	setPins(new Pin(14, nts::Tristate::UNDEFINED));
	initGates(4, GateType::UNDEFINED);
	setGate(new int[1]{3}, 1, GateType::AND, new int[2]{1, 2}, 2);
	setGate(new int[1]{4}, 1, GateType::AND, new int[2]{5, 6}, 2);
	setGate(new int[1]{10}, 1, GateType::AND, new int[2]{8, 9}, 2);
	setGate(new int[1]{11}, 1, GateType::AND, new int[2]{12, 13}, 2);
}