#ifndef __MANAGER_HPP__

# define __MANAGER_HPP__

#include <stack>
#include <map>
#include <string>
#include "Reception.hpp"

namespace	plazza
{
    class		Manager
    {
    public:
        typedef void (plazza::Manager::*commandCreator)();

    public:
        ~Manager();
        Manager(const std::string& str);

    private:
        int		_nbThreads;

        std::stack<std::string> _fileNamestack;
        std::map<std::string, commandCreator> _commandSpawn;
        Reception   *   _reception;

    private:
        bool	is_number(const std::string& str);
        void    createPhoneNumberCommand();
        void    createEmailCommand();
        void    createIpAddressCommand();

    public:
        bool    file_exist(const std::string filename);
        void    lexer(std::string & line);
        int		getNbThread();
        void	setNbThread(const int nbThread);
        void    createCommand(const plazza::Information type, const std::string & fileName);
        int		run();

        void lexer();
    };
};

#endif /* __MANAGER_HPP__ */
