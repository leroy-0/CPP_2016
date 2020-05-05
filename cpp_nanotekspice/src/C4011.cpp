//
// C4011.cpp for C4011 in /home/tekm/tek2/cpp_nanotekspice
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Sun Mar  5 03:01:28 2017 leroy_0
// Last update Sun Mar  5 03:01:29 2017 leroy_0
//

#include "C4011.hpp"

C4011::C4011(const std::string &name)
{
	setName(name);
	setType("4011");
	setPins(new Pin(14, nts::Tristate::UNDEFINED));
	initGates(4, GateType::UNDEFINED);
	setGate(new int[1]{3}, 1, GateType::NAND, new int[2]{1, 2}, 2);
	setGate(new int[1]{4}, 1, GateType::NAND, new int[2]{5, 6}, 2);
	setGate(new int[1]{10}, 1, GateType::NAND, new int[2]{8, 9}, 2);
	setGate(new int[1]{11}, 1, GateType::NAND, new int[2]{12, 13}, 2);
}
