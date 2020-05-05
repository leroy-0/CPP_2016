//
// C4071.cpp for C4071 in /home/tekm/tek2/cpp_nanotekspice
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Sun Mar  5 02:54:43 2017 leroy_0
// Last update Sun Mar  5 02:54:54 2017 leroy_0
//

#include "C4071.hpp"

C4071::C4071(const std::string &name)
{
	setName(name);
	setType("4071");
	setPins(new Pin(14, nts::Tristate::UNDEFINED));
	initGates(4, GateType::UNDEFINED);
	setGate(new int[1]{3}, 1, GateType::OR, new int[2]{1, 2}, 2);
	setGate(new int[1]{4}, 1, GateType::OR, new int[2]{5, 6}, 2);
	setGate(new int[1]{10}, 1, GateType::OR, new int[2]{8, 9}, 2);
	setGate(new int[1]{11}, 1, GateType::OR, new int[2]{12, 13}, 2);
}