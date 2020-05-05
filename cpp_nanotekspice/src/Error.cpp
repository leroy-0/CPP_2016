//
// Error.cpp for Error in /home/tekm/tek2/cpp_nanotekspice
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Sun Mar  5 21:54:46 2017 leroy_0
// Last update Sun Mar  5 21:54:53 2017 leroy_0
//

#include "Error.hpp"

nts::Error::~Error() throw() {}

nts::Error::Error(std::ostream &os, const std::string &msg)
  : _os(os)
{
  _msg = msg;
}

const char* nts::Error::what() const throw()
{
  return (_msg.c_str());
}

std::ostream& nts::Error::getOs() const
{
  return (_os);
}