//
// Created by longle-h on 24/04/17.
//

#include <iostream>
#include "Reception.hpp"

plazza::Reception::Reception(int nbThread)
{
    this->nbThread = nbThread;
}

plazza::Reception::~Reception()
{

}

void plazza::Reception::createKitchen() {
    pid_t _pid;

    _pid = fork();
    if (_pid == 0)
    {
        //fils
        this->_process.push_back(plazza::Kitchen(5,_pid));
        this->
    }
    else if (_pid == -1)
    {
        std::cout << "Erreur de fork()" << std::endl;
        return;
    }
    //Todo Throw if _pid == -1;
}

void plazza::Reception::sendCommand(Command &_command)
{
    if (this->_process.empty())
    {

    }
}