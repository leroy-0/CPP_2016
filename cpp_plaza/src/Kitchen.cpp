//
// Created by longle-h on 24/04/17.
//

#include "Kitchen.hpp"

plazza::Kitchen::Kitchen(int nbThread, pid_t mypid) {
    this->_pid = mypid;
}

plazza::Kitchen::~Kitchen() {}

pid_t plazza::Kitchen::getPid() {
    return (this->_pid);
}

void plazza::Kitchen::run() {
    
}