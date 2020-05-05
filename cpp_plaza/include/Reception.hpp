//
// Created by longle-h on 24/04/17.
//

#ifndef PROJECT_RECEPTION_HPP
#define PROJECT_RECEPTION_HPP

#include <vector>
#include "Kitchen.hpp"
#include "Command.hpp"

namespace plazza {
    class Reception
    {
    private:
        int     nbThread;
        std::vector<plazza::Kitchen> _process;

    public:
        Reception(int nbThread);
        ~Reception();

    public:
        void        sendCommand(Command & _command);

    private:
        void        createKitchen();
    };
};

#endif //PROJECT_RECEPTION_HPP
