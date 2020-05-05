//
// parser_tools.cpp for nts in /home/bruere_s/Projet/cpp_nanotekspice
// 
// Made by Sebastien Bruere
// Login   <sebastien.bruere@epitech.eu>
// 
// Started on  Thu Feb 16 13:36:16 2017 Sebastien Bruere
// Last update Thu Feb 16 13:36:17 2017 Sebastien Bruere
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include "../include/Parser.hpp"

void Parser::displayType(nts::ASTNodeType type) {
    std::cout << "type == ";

    if (type == nts::ASTNodeType::COMPONENT)
        std::cout << "COMPONENT" << std::endl;
    else if (type == nts::ASTNodeType::DEFAULT)
        std::cout << "DEFAULT" << std::endl;
    else if (type == nts::ASTNodeType::LINK)
        std::cout << "LINK" << std::endl;
    else if (type == nts::ASTNodeType::LINK_END)
        std::cout << "LINK_END" << std::endl;
    else if (type == nts::ASTNodeType::NEWLINE)
        std::cout << "NEWLINE" << std::endl;
    else if (type == nts::ASTNodeType::SECTION)
        std::cout << "SECTION" << std::endl;
    else if (type == nts::ASTNodeType::STRING)
        std::cout << "STRING" << std::endl;
}

std::string Parser::epurString(std::string str) {
    std::replace( str.begin(), str.end(), '\t', ' ');
    for (unsigned int i = 0; i < str.size(); i++)
    {
        if (i == 0 && (str.at(i) == ' ' || str.at(i) == '\t')) {
            str.erase(str.begin());
            i = 0;
        }
        else if (i + 1 < str.size() && str.at(i) == ' ' && (str.at(i + 1) == ' ' || str.at(i + 1) == '\0' )) {
            str.erase(str.begin() + i);
            i = 0;
        }
        else if (i + 1 < str.size() && str.at(i) == '\t' && (str.at(i + 1) == '\t' || str.at(i + 1) == '\0' )) {
            str.erase(str.begin() + i);
            i = 0;
        }
        else if (str.at(i) == '#')  
            str.erase(i, str.length());
    }
    return str;
}

bool Parser::checkNextSection(std::string line) {
    if (line.length() > 0 && line.at(0) == '.') {
        _file.seekg(_posFile);
        return true;
    }
    return false;
}
nts::t_ast_node* Parser::getTree() {
    return _tree;
}

nts::t_ast_node* Parser::createSection(std::string value) {
    std::vector<nts::t_ast_node *> *children = new std::vector<nts::t_ast_node *>();
    nts::t_ast_node *newSection = new nts::t_ast_node(children);
    newSection->value = value;
    newSection->type = nts::ASTNodeType::SECTION;
    return newSection;
}


nts::t_ast_node* Parser::createNode(std::string value, nts::ASTNodeType type, std::string lexeme) {
    nts::t_ast_node *newNode;
    std::vector<nts::t_ast_node *> *children = new std::vector<nts::t_ast_node *>();
    newNode= new nts::t_ast_node(children);

    newNode->type = type;
    newNode->value = value;
    newNode->lexeme = lexeme;
    newNode->children = new std::vector<nts::t_ast_node *>();
    return newNode;
}

nts::ASTNodeType Parser::getTypeNode(std::string line) {
    std::string res = line.substr(0, line.find_first_of(" "));

    if (res.length() == 0)
        return (nts::ASTNodeType::NEWLINE);
    else if (res.at(0) == '#')
        return (nts::ASTNodeType::STRING);
    else if (res.compare(".chipsets:") == 0 || res.compare(".links:") == 0)
        return (nts::ASTNodeType::SECTION);
    else if (res.compare("input") == 0 || res.compare("output") == 0 || res.compare("4081") == 0)
        return (nts::ASTNodeType::COMPONENT);
    return (nts::ASTNodeType::DEFAULT);
}
std::string Parser::getLexeme(std::string line) {
    std::size_t found = line.find_first_of(" ");
    return (line.substr(0, found));
}
std::string Parser::getComposantName(std::string line) {
    if (line.length() == 0)
        return "";
    std::size_t found = line.find_first_of(" ");
    return (line.substr(found + 1, line.length()));
}

void Parser::setFile(std::string file) {
    if (std::ifstream(file)) {
        _file.open(file);
    }
    else
    {
        throw nts::Error(std::cerr, "No such file named '" + file + "'");
    }
}


void Parser::setOpt(std::vector<std::string> opt) {
    if (_argc < 2)
        opt.empty();
    else {
        for (unsigned int i = 2; i < _argc; i++) {
            _opt.push_back(opt[i]);
        }

        for(int unsigned i=0 ; i < _opt.size() ; i++){
            std::cout << _opt[i] << std::endl;
        }
    }
}
