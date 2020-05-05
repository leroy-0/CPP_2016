//
// main.cpp for  in /home/bruere_s/Projet/cpp_nanotekspice
// 
// Made by Sebastien Bruere
// Login   <sebastien.bruere@epitech.eu>
// 
// Started on  Mon Feb 13 12:58:29 2017 Sebastien Bruere
// Last update Sun Mar  5 18:33:33 2017 leroy_0
//

#include	<string>
#include	<iostream>
#include	"Parser.hpp"

int main(int ac, char **av)
{
  Parser parser(ac, av);

  parser.parseTree(*parser.createTree());

  parser.launch();  

  return (0);
}
