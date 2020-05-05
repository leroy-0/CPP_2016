//
// C4071.hpp for C4071 in /home/tekm/tek2/cpp_nanotekspice
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Sun Mar  5 02:55:10 2017 leroy_0
// Last update Sun Mar  5 02:55:13 2017 leroy_0
//

#ifndef C4071_HPP
# define C4071_HPP

#include "Component.hpp"

class C4071 : public Component
{
	public:
   		C4071(const std::string &name);
   		virtual ~C4071() {};
};

#endif /* C4071_HPP */