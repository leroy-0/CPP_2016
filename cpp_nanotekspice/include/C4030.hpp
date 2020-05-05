//
// C4030.hpp for C4030 in /home/tekm/tek2/cpp_nanotekspice
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Sun Mar  5 03:08:38 2017 leroy_0
// Last update Sun Mar  5 03:08:39 2017 leroy_0
//

#ifndef C4030_HPP
# define C4030_HPP

#include "Component.hpp"

class C4030 : public Component
{
	public:
   		C4030(const std::string &name);
   		virtual ~C4030() {};
};

#endif /* C4030_HPP */
