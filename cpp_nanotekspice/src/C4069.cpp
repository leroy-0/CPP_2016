//
// C4069.cpp for C4069 in /home/tekm/tek2/cpp_nanotekspice
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Sun Mar  5 03:13:01 2017 leroy_0
// Last update Sun Mar  5 03:13:02 2017 leroy_0
//

#include "C4069.hpp"

C4069::C4069(const std::string &name)
{
	setName(name);
	setType("4069");
	setPins(new Pin(14, nts::Tristate::UNDEFINED));
	initGates(6, GateType::UNDEFINED);
	setGate(new int[1]{2}, 1, GateType::NOT, new int[1]{1}, 1);
	setGate(new int[1]{4}, 1, GateType::NOT, new int[1]{3}, 1);
	setGate(new int[1]{6}, 1, GateType::NOT, new int[1]{5}, 1);
	setGate(new int[1]{8}, 1, GateType::NOT, new int[1]{9}, 1);
	setGate(new int[1]{10}, 1, GateType::NOT, new int[1]{11}, 1);
	setGate(new int[1]{12}, 1, GateType::NOT, new int[1]{13}, 1);
}