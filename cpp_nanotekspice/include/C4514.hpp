//
// C4514.hpp for C4514 in /home/tekm/tek2/cpp_nanotekspice
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Sun Mar  5 15:07:17 2017 leroy_0
// Last update Sun Mar  5 15:07:18 2017 leroy_0
//

#ifndef C4514_HPP
# define C4514_HPP

#include "Component.hpp"

class C4514 : public Component
{
	public:
   		C4514(const std::string &name);
   		virtual ~C4514() {};
};

#endif /* C4514_HPP */
