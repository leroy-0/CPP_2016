//
// C4001.hpp for C4001 in /home/tekm/tek2/cpp_nanotekspice
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Sun Mar  5 03:06:00 2017 leroy_0
// Last update Sun Mar  5 03:06:01 2017 leroy_0
//

#ifndef C4001_HPP
# define C4001_HPP

#include "Component.hpp"

class C4001 : public Component
{
	public:
   		C4001(const std::string &name);
   		virtual ~C4001() {};
};

#endif /* C4001_HPP */
