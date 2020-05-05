//
// Character.hpp for Character in /home/tekm/tek2/cpp_arcade/games/nibbler
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Tue Mar  7 15:46:35 2017 leroy_0
// Last update Tue Mar  7 15:46:36 2017 leroy_0
//

#ifndef				__CHARACTER_HPP_
#define				__CHARACTER_HPP_

#include			"Protocol.hpp"

class				Character
{
public:
  Character(uint16_t height, uint16_t width);
  virtual ~Character() {};

  arcade::WhereAmI		*getDir() const;
  int				    *getQueue() const;
  arcade::CommandType	*getHistory() const;
private:
  arcade::WhereAmI		*_dir;
  int				    *_queue;
  arcade::CommandType	*_history;
};

#endif /* __CHARACTER_HPP */