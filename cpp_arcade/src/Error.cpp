//
// Error.cpp for Error in /home/tekm/tek2/cpp_arcade
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Tue Mar  7 14:37:18 2017 leroy_0
// Last update Tue Mar  7 14:37:19 2017 leroy_0
//

#include "Error.hpp"

arcade::Error::~Error() throw() {}

arcade::Error::Error(std::ostream &os, const std::string &msg)
  : _os(os)
{
  _msg = msg;
}

const char* arcade::Error::what() const throw()
{
  return (_msg.c_str());
}

std::ostream& arcade::Error::getOs() const
{
  return (_os);
}
