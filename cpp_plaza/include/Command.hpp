//
// Created by longle-h on 24/04/17.
//

#ifndef PROJECT_COMMAND_HPP
#define PROJECT_COMMAND_HPP

#include <string>
#include "Plazza.hpp"

namespace plazza {
    class Command
    {
    private:
        const std::string     _fileName;
        plazza::Information   _type;

    public:
        Command(const std::string & fileName, const plazza::Information type);
        ~Command();
    };
};

#endif //PROJECT_COMMAND_HPP
