//
// manager.cpp for manager in /home/kleinh/Documents/TEK2/cpp_plaza/src
// 
// Made by Arthur Klein
// Login   <arthur.klein@epitech.eu>
// 
// Started on  Thu Apr 20 12:02:20 2017 Arthur Klein
// Last update Thu Apr 20 14:46:21 2017 Arthur Klein
//
#include	<iostream>
#include <Command.hpp>
#include "Plazza.hpp"
#include	"Error.hpp"
#include	"Manager.hpp"
#include "fstream"

bool		plazza::Manager::is_number(const std::string& str)
{
  auto		it = str.begin();

    while (it != str.end() && std::isdigit(*it))
        ++it;
    return (!str.empty() && it == str.end());
}

int		plazza::Manager::getNbThread()
{
  return (_nbThreads);
}

void        plazza::Manager::createCommand(const plazza::Information type, const std::string &fileName) {
    plazza::Command c(fileName, type);

    this->_reception->sendCommand(c);
}

void        plazza::Manager::createEmailCommand()
{
    std::string file;

    while (!this->_fileNamestack.empty())
    {
        this->createCommand(plazza::Information::EMAIL_ADDRESS, this->_fileNamestack.top());
        this->_fileNamestack.pop();
    }
}

void        plazza::Manager::createIpAddressCommand()
{
    std::string file;

    while (!this->_fileNamestack.empty())
    {
        this->createCommand(plazza::Information::IP_ADDRESS, this->_fileNamestack.top());
        this->_fileNamestack.pop();
    }
}
void        plazza::Manager::createPhoneNumberCommand()
{
    std::string file;

    while (!this->_fileNamestack.empty())
    {
        this->createCommand(plazza::Information::PHONE_NUMBER, this->_fileNamestack.top());
        this->_fileNamestack.pop();
    }
}

void		plazza::Manager::setNbThread(const int nbThread)
{
  if (nbThread > 0)
    this->_nbThreads = nbThread;
/* @TODO throw if this is not positive number */
  this->_reception = new plazza::Reception(this->_nbThreads);
}

plazza::Manager::Manager(const std::string & nbThread)
{
  try
  {
    if (!nbThread.empty() && this->is_number(nbThread))
      this->setNbThread(std::stoi(nbThread));
    else
      throw plazza::Error(std::cerr,"nbThread : is not a number or is empty");
  }
  catch (const plazza::Error & e)
  {
    e.getOs() << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }
    this->_commandSpawn["PHONE_NUMBER"] = &plazza::Manager::createPhoneNumberCommand;
    this->_commandSpawn["EMAIL_ADDRESS"] = &plazza::Manager::createEmailCommand;
    this->_commandSpawn["IP_ADDRESS"] = &plazza::Manager::createIpAddressCommand;

  /* @TODO throw if this is not number */
}

bool plazza::Manager::file_exist(const std::string filename)
{
    std::ifstream infile(filename);
    return infile.good();
}

void plazza::Manager::lexer(std::string & line)
{
    if (line.empty())
        return;
    if (line.size() != 0 && line[line.size() - 1] == ';')
        line = line.substr(0, line.size() - 1);
    if (this->_commandSpawn[line] == NULL)
    {
        if (file_exist(line) == false)
            std::cerr << "File could not be opened" << std::endl;
        else
            this->_fileNamestack.push(line);
    }
    else
    {
        (this->*_commandSpawn[line])();
    }
}

int		plazza::Manager::run()
{
    for (std::string line; std::cin >> line;)
    {
        this->lexer(line);
    }
    return (0);
}

plazza::Manager::~Manager()
{
    delete(this->_reception);
}