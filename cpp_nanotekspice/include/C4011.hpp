//
// C4011.hpp for C4011 in /home/tekm/tek2/cpp_nanotekspice
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Sun Mar  5 03:01:43 2017 leroy_0
// Last update Sun Mar  5 03:01:44 2017 leroy_0
//

#ifndef C4011_HPP
# define C4011_HPP

#include "Component.hpp"

class C4011 : public Component
{
	public:
   		C4011(const std::string &name);
   		virtual ~C4011() {};
};

#endif /* C4011_HPP */
