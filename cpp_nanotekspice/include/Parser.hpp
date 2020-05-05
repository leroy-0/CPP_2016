//
// Parser.hpp for nts in /home/bruere_s/Projet/cpp_nanotekspice/include
// 
// Made by Sebastien Bruere
// Login   <sebastien.bruere@epitech.eu>
// 
// Started on  Mon Feb 13 13:01:56 2017 Sebastien Bruere
// Last update Mon Feb 13 14:14:09 2017 Sebastien Bruere
//

#ifndef		PARSER_HPP_
#define		PARSER_HPP_

#include	<iostream>
#include	<fstream>
#include    <signal.h>
#include    <sstream>

#include    "Component.hpp"
#include	"IParser.hpp"
#include    "Error.hpp"

class	Parser : public nts::IParser
{

public:
    Parser(const unsigned int argc, char **argv);
    ~Parser();

    void                setFile(std::string file);
    void                setOpt(std::vector<std::string> opt);

    void                feed(std::string const& input);
    void                parseTree(nts::t_ast_node& root);
    nts::t_ast_node     *createTree();
    nts::t_ast_node     *createNode(std::string value, nts::ASTNodeType type, std::string lexem);
    nts::t_ast_node     *createSection(std::string value);
    nts::t_ast_node*    getAllChipset();
    nts::t_ast_node*    getAllLinks();
    nts::t_ast_node*    parseLinks(std::string line);
    std::string         getComposantName(std::string);
    std::string         getLexeme(std::string);
    bool                checkNextSection(std::string line);
    std::string         epurString(std::string line);
    nts::t_ast_node*    checkTypeNode(std::string line);
    void                displayType(nts::ASTNodeType type);
    void                parseSection(nts::t_ast_node& node, Component manager);
    void                parseComponents(nts::t_ast_node& node, Component manager);
    void                createLinks(nts::t_ast_node& node);

    void                launch();

    void                simulate();
    void                display();
    void                Dump();
    void                loop();
    void                setNewArg(const std::string &command);

public:

    nts::t_ast_node     *getTree();
    nts::ASTNodeType    getTypeNode(std::string line);
private:

    std::ifstream       _file;
    unsigned int        _argc;
    std::vector<std::string> _argv;
    std::vector<std::string> _opt;
    nts::t_ast_node     *_tree;
    long int            _posFile;

private:
    nts::IComponent     *_model;
    std::vector<nts::IComponent *> _components;
};

void                no_action(int x);
void                loop_signal(int n);

#endif		//PARSER_HPP_
