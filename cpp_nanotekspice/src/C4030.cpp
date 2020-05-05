//
// C4030.cpp for C4030 in /home/tekm/tek2/cpp_nanotekspice
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Sun Mar  5 03:08:30 2017 leroy_0
// Last update Sun Mar  5 03:08:30 2017 leroy_0
//

#include "C4030.hpp"

C4030::C4030(const std::string &name)
{
	setName(name);
	setType("4030");
	setPins(new Pin(14, nts::Tristate::UNDEFINED));
	initGates(4, GateType::UNDEFINED);
	setGate(new int[1]{3}, 1, GateType::XOR, new int[2]{1, 2}, 2);
	setGate(new int[1]{4}, 1, GateType::XOR, new int[2]{5, 6}, 2);
	setGate(new int[1]{10}, 1, GateType::XOR, new int[2]{8, 9}, 2);
	setGate(new int[1]{11}, 1, GateType::XOR, new int[2]{13, 12}, 2);
}
