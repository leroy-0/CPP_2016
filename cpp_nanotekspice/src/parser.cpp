//
// parser.cpp for nts in /home/bruere_s/Projet/cpp_nanotekspice
// 
// Made by Sebastien Bruere
// Login   <sebastien.bruere@epitech.eu>
// 
// Started on  Mon Feb 13 13:00:24 2017 Sebastien Bruere
// Last update Mon Feb 13 14:20:54 2017 Sebastien Bruere
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include "Parser.hpp"

bool     isloop;
bool     isThereLinks = false;

Parser::~Parser() {}

Parser::Parser(const unsigned int argc, char **argv) : _argc(argc)
{
    try {
        if (argc == 1)
            throw nts::Error(std::cerr, "Number of arguments should be equal or superior to 2");
    }
    catch (const nts::Error & e) {
        e.getOs() << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    std::vector<nts::t_ast_node *> *children = new std::vector<nts::t_ast_node *>();

    _tree = new nts::t_ast_node(children);
    _tree->type = nts::ASTNodeType::DEFAULT;
    _model = NULL;
    for (unsigned int i = 0; i < _argc; i++) {
        _argv.push_back(argv[i]);
    }
    if (_argv[1].data())
    {
        try {
            this->setFile(_argv[1].data());
        }
        catch (const nts::Error & e) {
            e.getOs() << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}

nts::t_ast_node *Parser::createTree() {
    std::string line;
    nts::t_ast_node *newNode;
    std::vector<nts::t_ast_node *> *children = new std::vector<nts::t_ast_node *>();
    newNode = new nts::t_ast_node(children);

    if (_file.is_open()) {
        while (!_file.eof()) {
            getline(_file, line);
            _posFile = _file.tellg();
            line = epurString(line);
            newNode = checkTypeNode(line);
            _tree->children->push_back(newNode);
        }
        _file.close();
    }
    return _tree;
}

nts::t_ast_node* Parser::parseLinks(std::string line) {
    std::string tmp = line;
    nts::ASTNodeType type;
    std::string value;
    std::string lexeme;
    std::size_t found;


    found = line.find_first_of(" ");
    tmp = line.substr(0, found);

    found = tmp.find_first_of(":");
    lexeme = tmp.substr(0, found);

    value = tmp.substr(found + 1, tmp.length());

    type = nts::ASTNodeType::LINK;
    nts::t_ast_node *newNode = createNode(value, type, lexeme);

    found = line.find_first_of(" ");
    tmp = line.substr(found + 1, line.length());

    found = tmp.find_first_of(":");
    lexeme = tmp.substr(0, found);
    value = tmp.substr(found + 1, tmp.length());
    type = nts::ASTNodeType::LINK_END;
    newNode->children->push_back(createNode(value, type, lexeme));
    return newNode;
}

nts::t_ast_node *Parser::getAllLinks() {
    std::string line = "";
    nts::t_ast_node *newSection = createSection(".links");

    while (getline(_file, line)) {
        if (checkNextSection(line))
            break;
        if (getTypeNode(line) == nts::ASTNodeType::NEWLINE || getTypeNode(line) == nts::ASTNodeType::STRING)
            continue;
        _posFile = _file.tellg();
        line = epurString(line);
        newSection->children->push_back(parseLinks(line));
    }
    return newSection;
}

nts::t_ast_node *Parser::getAllChipset() {
    std::string line = "";
    nts::t_ast_node *newSection = createSection(".chipsets");

    nts::ASTNodeType type;
    std::string value;
    std::string lexeme;

    while (getline(_file, line)) {
        if (checkNextSection(line))
            break;
        _posFile = _file.tellg();
        line = epurString(line);
        type = getTypeNode(line);
        lexeme = getLexeme(line);
        value = getComposantName(line);
        newSection->children->push_back(createNode(value, type, lexeme));
    }
    return newSection;
}

nts::t_ast_node *Parser::checkTypeNode(std::string line) {
    std::size_t found = line.find_first_of(" ");
    std::string res = line.substr(0, found);

    if (res.length() == 0)
        return (createNode("newline", nts::ASTNodeType::NEWLINE, ""));
    else if (res.at(0) == '#')
        return (createNode("commentaire", nts::ASTNodeType::STRING, ""));
    else if (res.compare(".chipsets:") == 0 )
        return (getAllChipset());
    else if (res.compare(".links:") == 0)
        return getAllLinks();
    return (createNode("", nts::ASTNodeType::DEFAULT, ""));
}

void Parser::feed(std::string const & input)
{
    (void)input;
}

void Parser::createLinks(nts::t_ast_node& node)
{
    Component       *compo_beg = NULL;
    Component       *compo_end = NULL;
    Component       *tmp = NULL;

    for (auto it = _components.begin(); it < _components.end(); ++it)
    {
        tmp = (Component *)(*it);
        if (tmp->getName().compare(node.lexeme) == 0)
        {
            compo_beg = tmp;
            break;
        }
    }
    for (auto it = _components.begin(); it < _components.end(); ++it)
    {
        tmp = (Component *)(*it);
        if (tmp->getName().compare(node.children->at(0)->lexeme) == 0)
        {
            compo_end = tmp;
            break;
        }
    }

    if (compo_beg && compo_end)
        compo_end->SetLink((size_t)std::atoi(node.value.c_str()), *compo_beg, (size_t)std::atoi(node.children->at(0)->value.c_str()));
}

void Parser::parseComponents(nts::t_ast_node& node, Component manager)
{
    nts::IComponent          *compo;

    if (node.type != nts::ASTNodeType::NEWLINE)
    {
        try {
            compo = manager.createComponent(node.lexeme, node.value);
        }
        catch (const nts::Error & e) {
            e.getOs() << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }
        if (node.lexeme.compare("input") != 0
            && node.lexeme.compare("output") != 0
            && node.lexeme.compare("") != 0)
        {
            _model = compo;
        }
        _components.push_back(compo);
    }
}

void Parser::parseSection(nts::t_ast_node& node, Component manager)
{
    for (unsigned int x = 0; x < node.children->size(); x++)
    {
        if (node.value.compare(".links") == 0)
        {
            createLinks(*node.children->at(x));
            isThereLinks = true;
        }
        else if (node.value.compare(".chipsets") == 0)
            parseComponents(*node.children->at(x), manager);
    }
}

void Parser::parseTree(nts::t_ast_node& root)
{
    Component           manager;
    Component           *compo;

    //MAKE LINKS BETWEEN COMPONENT
    for (unsigned int x = 0; x < root.children->size(); x++)
    {
        if (root.children->at(x)->type == nts::ASTNodeType::SECTION)
            parseSection(*root.children->at(x), manager);
    }

    try {
        if (isThereLinks == false)
            throw nts::Error(std::cerr, "No links between components");
    }
    catch (const nts::Error & e) {
        e.getOs() << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    //SET VALUES FROM ARGV
    for (unsigned int i = 2; i < _argc; ++i)
    {
        int pos = _argv[i].find_first_of("=");
        std::string name = _argv[i].substr(0, pos);
        std::string value = _argv[i].substr(pos + 1, _argv[i].size());

        Component *compo;
        for (auto it = _components.begin(); it < _components.end(); ++it)
        {
            compo = (Component *)(*it);
            if (compo->getName().compare(name) == 0 && compo->getType().compare("true") != 0 && compo->getType().compare("false") != 0)
                compo->getPins()->setState(0, (nts::Tristate)std::atoi(value.c_str()));
        }
    }

    try {
        for (auto it = _components.begin(); it < _components.end(); ++it)
        {
            compo = (Component *)(*it);
            if ((compo->getType().compare("input") == 0 || compo->getType().compare("clock") == 0) && compo->getPins()->getState(0) == nts::Tristate::UNDEFINED)
                throw nts::Error(std::cerr, "Component '" + compo->getName() + "' must be initialized");
        }
    }
    catch (const nts::Error & e) {
            e.getOs() << e.what() << std::endl;
            exit(EXIT_FAILURE);
    }

    try {
        if (_components.size() == 0 || _model == NULL)
            throw nts::Error(std::cerr, "No component or chipset has been defined");
    }
    catch (const nts::Error & e) {
        e.getOs() << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    simulate();

    display();
}

void Parser::simulate()
{
    Component   *model;
    Component   *chipset;

    chipset = (Component *)_model;
    for (int i = 0; i < chipset->getPins()->getSize(0); ++i)
    {
        for (auto it = _components.begin(); it < _components.end(); ++it)
        {
            model = (Component *)(*it);
            for (int i = 0;model->getPins() && i < model->getPins()->getSize(0); ++i)
            {
                if (model->getPins()->getLinkPins(i) != NULL && model->getType().compare("true") != 0 && model->getType().compare("false") != 0)
                        model->getPins()->setState(i, model->getPins()->getLinkPins(i)->getState(model->getPins()->getLinkValue(i)));
            }
            model->switchOperations();
        }
        chipset->switchOperations();
    }

    for (auto it = _components.begin(); it < _components.end(); ++it)
    {
        model = (Component *)(*it);
        if (model->getType().compare("clock") == 0)
        {
            if (model->getPins()->getState(0) == nts::Tristate::TRUE)
                model->getPins()->setState(0, nts::Tristate::FALSE);
            else if (model->getPins()->getState(0) == nts::Tristate::FALSE)
                model->getPins()->setState(0, nts::Tristate::TRUE);
        }
    }
}

void Parser::display()
{
    Component           *compo;
    std::ostringstream  myout;

    std::vector<std::string>    to_display;
    for (auto it = _components.begin(); it < _components.end(); ++it)
    {
        compo = (Component *)(*it);
        if (compo->getType().compare("output") == 0)
        {
            myout << compo->getName() << "=" << compo->getPins()->getState(0);
            to_display.push_back(myout.str());
            myout.clear();
            myout.str(std::string());
        }
    }

    std::sort(to_display.begin(), to_display.end());
    for (auto it = to_display.begin(); it < to_display.end(); ++it)
        std::cout << (*it) << std::endl;
}

void Parser::Dump()
{
    for (unsigned int i = 0; i < _components.size(); ++i)
    {
        _components[i]->Dump();
    }
}

void Parser::loop()
{
    isloop = true;
    signal(SIGINT, loop_signal);
    while (isloop)
        simulate();
    signal(SIGINT, no_action);
}

void Parser::setNewArg(const std::string &command)
{
    Component       *compo;
    std::string     name = command.substr(0, command.find_first_of("="));
    std::string     value = command.substr(command.find_first_of("=") + 1, command.size());

    for (auto it = _components.begin(); it < _components.end(); ++it)
    {
        compo = (Component *)(*it);
        if (compo->getName().compare(name) == 0 && compo->getType().compare("true") != 0 && compo->getType().compare("false") != 0)
            compo->getPins()->setState(0, (nts::Tristate)std::atoi(value.c_str()));
    }
}

void loop_signal(int n)
{
  (void)n;
  isloop = false;
}

void no_action(int x)
{
    (void)x;
}

void Parser::launch()
{
    std::string     command;

    signal(SIGINT, no_action);
    std::cout << ">";
    while (std::getline(std::cin, command))
    {
        if (command.compare("exit") == 0)
            break;
        else if (command.compare("display") == 0)
        {
            display();
        }
        else if (command.compare("simulate") == 0)
        {
            simulate();
        }
        else if (command.compare("loop") == 0)
        {
            loop();
        }
        else if (command.compare("dump") == 0)
        {
            Dump();
        }
        else if (command.find_first_of("=") != std::string::npos)
        {
            setNewArg(command);
        }
        else
        {
            std::cout << "'" << command << "': unknown command" << std::endl;
        }
        std::cout << ">";
    }
}