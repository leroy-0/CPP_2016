//
// Error.hpp for Error in /home/tekm/tek2/cpp_nanotekspice
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Sun Mar  5 21:54:35 2017 leroy_0
// Last update Sun Mar  5 21:54:38 2017 leroy_0
//

#ifndef ERROR_HPP
# define ERROR_HPP

# include <exception>
# include <iostream>
# include <string>

namespace nts
{
    class Error: public std::exception
    {
      public:
        Error(std::ostream &, const std::string &);
        virtual ~Error() throw();

      protected:
        std::ostream& _os;
        std::string _msg;

      public:
        const char *what() const throw();
        std::ostream& getOs() const;
    };
};

#endif
