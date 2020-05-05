//
// C4514.cpp for C4514 in /home/tekm/tek2/cpp_nanotekspice
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Sun Mar  5 15:07:05 2017 leroy_0
// Last update Sun Mar  5 15:07:06 2017 leroy_0
//

#include "C4514.hpp"

C4514::C4514(const std::string &name)
{
	setName(name);
	setType("4514");
	setPins(new Pin(52, nts::Tristate::UNDEFINED));

	SetLink(25, *this, 29);
  	SetLink(26, *this, 31);
  	SetLink(27, *this, 33);
  	SetLink(28, *this, 35);
  	SetLink(30, *this, 37);
  	SetLink(32, *this, 40);
  	SetLink(34, *this, 43);
  	SetLink(36, *this, 46);
  	SetLink(38, *this, 49);
  	SetLink(41, *this, 50);
  	SetLink(44, *this, 51);
	SetLink(47, *this, 52);

	initGates(13, GateType::UNDEFINED);

	setGate(new int[1]{25}, 1, GateType::NAND, new int[2]{2, 1}, 2);
	setGate(new int[1]{26}, 1, GateType::NAND, new int[2]{3, 1}, 2);
	setGate(new int[1]{27}, 1, GateType::NAND, new int[2]{21, 1}, 2);
	setGate(new int[1]{28}, 1, GateType::NAND, new int[2]{22, 1}, 2);

	setGate(new int[1]{30}, 1, GateType::NAND, new int[2]{29, 1}, 2);
	setGate(new int[1]{32}, 1, GateType::NAND, new int[2]{31, 1}, 2);
	setGate(new int[1]{34}, 1, GateType::NAND, new int[2]{33, 1}, 2);
	setGate(new int[1]{36}, 1, GateType::NAND, new int[2]{35, 1}, 2);

	setGate(new int[2]{38, 39}, 2, GateType::FLIPFLOPRS, new int[2]{29, 37}, 2);
	setGate(new int[2]{41, 42}, 2, GateType::FLIPFLOPRS, new int[2]{31, 40}, 2);
	setGate(new int[2]{44, 45}, 2, GateType::FLIPFLOPRS, new int[2]{33, 43}, 2);
	setGate(new int[2]{47, 48}, 2, GateType::FLIPFLOPRS, new int[2]{35, 46}, 2);

	setGate(new int[16]{11, 9, 10, 8, 7, 6, 5, 4, 18, 17, 20, 19, 14, 13, 16, 15}, 16,
		GateType::DECODER, new int[5]{49, 50, 51, 52, 23}, 5);
}