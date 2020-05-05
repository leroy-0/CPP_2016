//
// Error.hpp for Error in /home/tekm/tek2/cpp_arcade
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Tue Mar  7 14:35:06 2017 leroy_0
// Last update Tue Mar  7 14:35:06 2017 leroy_0
//

#ifndef			__ERROR_HPP_
# define		__ERROR_HPP_

# include		<exception>
# include		<iostream>
# include		<string>

namespace		arcade
{
    class		Error: public std::exception
    {
      public:
        Error(std::ostream &, const std::string &);
        virtual ~Error() throw();

      protected:
        std::ostream&	_os;
        std::string	_msg;

      public:
        const char *what() const throw();
        std::ostream& getOs() const;
    };
};

#endif 	/* __ERROR_HPP_ */