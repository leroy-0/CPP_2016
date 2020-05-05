//
// IComponent.hpp for IComponent in /home/tekm/tek2/cpp_nanotekspice
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Mon Feb 27 18:55:51 2017 leroy_0
// Last update Mon Feb 27 18:55:56 2017 leroy_0
//

#ifndef _ICOMPONENT_HPP_
# define _ICOMPONENT_HPP_

namespace nts
{
  enum Tristate
    {
      UNDEFINED = (-true),
      TRUE = true,
      FALSE = false
    };

  class IComponent
  {
  public:
    virtual ~IComponent(void) {}
    virtual nts::Tristate Compute(size_t pin_num_this = 1) = 0;
    virtual void SetLink(size_t pin_num_this,
			 nts::IComponent &component,
			 size_t pin_num_target) = 0;
    virtual void Dump(void) const = 0;
  };
};

#endif /* !_ICOMPONENT_HPP_ */
