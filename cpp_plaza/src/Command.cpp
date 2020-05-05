//
// Created by longle-h on 24/04/17.
//

#include "Command.hpp"

plazza::Command::Command(const std::string &fileName, const plazza::Information type) : _fileName(fileName), _type(type) {

}

plazza::Command::~Command() {}