//
// Pin.cpp for Pin in /home/tekm/tek2/cpp_nanotekspice
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Wed Mar  1 12:30:31 2017 leroy_0
// Last update Wed Mar  1 12:30:33 2017 leroy_0
//

#include "Pin.hpp"

Pin::Pin(const int &size, const nts::Tristate &state)
{
  int 			i = 0;

  _size = new int[size];
  _state = new nts::Tristate[size];
  _linkValue = new int[size];
  while (i < size)
  {
    _size[i] = size;
    _state[i] = state;
    _linkComps.push_back(NULL);
    _linkValue[i] = -1;
    i++;
  }
}

void 			Pin::setState(const int &value, const nts::Tristate &state)
{
  if (value >= 0 && value < _size[0])
  	_state[value] = state;
}

nts::Tristate 	Pin::getState(const int & value) const
{
	return (_state[value]);
}

int 			Pin::getSize(const int & value) const
{
	return (_size[value]);
}

void    Pin::setLinkComp(nts::IComponent & linkComp, size_t &value, size_t &linkValue)
{
  _linkComps[value] = &linkComp;
  _linkValue[value] = linkValue;
}

Pin    *Pin::getLinkPins(const int &value) const
{
  Component   *compo;

  if (_linkComps[value] == NULL)
    return (NULL);
  compo = (Component *)(_linkComps[value]);
  return (compo->getPins());
}

int       Pin::getLinkValue(const int &value) const
{
  if (value >= 0 && (unsigned int)value < _linkComps.size())
    return (_linkValue[value]);
  return (-1);
}