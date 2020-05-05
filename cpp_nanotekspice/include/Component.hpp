//
// Component.hpp for Component in /home/tekm/tek2/cpp_nanotekspice
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Mon Feb 27 19:15:07 2017 leroy_0
// Last update Mon Feb 27 19:23:11 2017 leroy_0
//

#ifndef _COMPONENT_HPP_
# define _COMPONENT_HPP_

#include <string>
#include <utility>
#include <iostream>
#include <map>
#include <functional>
#include <vector>

#include "IComponent.hpp"
#include "Error.hpp"

enum GateType {
  UNDEFINED = -1,
  NOR,
  NAND,
  NOT,
  OR,
  AND,
  XOR,
  FLIPFLOPRS,
  DECODER
};

typedef struct          s_gates
{
  int                   size;
  int                   *value;
  int                   *inputs;
  GateType              state;
}                       t_gates;

class Pin
{
public:
  Pin(const int &size, const nts::Tristate &state);
  virtual ~Pin() {};

  nts::Tristate getState(const int & value) const;
  int           getSize(const int & value) const;
  void          setState(const int &value, const nts::Tristate &state);
  void          setLinkComp(nts::IComponent &linkpin, size_t &value, size_t &linkValue);
  Pin           *getLinkPins(const int &value) const;
  int           getLinkValue(const int &value) const;

private:
  int           *_size;
  nts::Tristate *_state;
  std::vector<nts::IComponent *>  _linkComps;
  int           *_linkValue;
};

class Component : public nts::IComponent
{
public:
  Component(void);
  virtual ~Component(void) {}

  //REQUIRED
  nts::Tristate Compute(size_t pin_num_this = 1);
  void SetLink(size_t pin_num_this,
     nts::IComponent &component,
     size_t pin_num_target);
  void Dump(void) const;

  //SETTERS
  void        initGates(const int &size, const GateType &state);
  void        setType(const std::string &type);
  void        setName(const std::string &name);
  void        setGate(const int *value, const int &value_size,
    const GateType &state, const int *pins, const int &pins_size);
  void        setArgs(const std::vector<std::string> & args);
  void        setPins(Pin * pin);


  //GETTERS
  std::string getName() const;
  std::string getType() const;
  Pin         *getPins();
  t_gates     *getGates();

  //GATE OPERATIONS
  void     switchOperations();

  void     ANDoperation(const int & value);
  void     ORoperation(const int & value);
  void     NANDoperation(const int & value);
  void     NORoperation(const int & value);
  void     NOToperation(const int & value);
  void     XORoperation(const int & value);
  void     FLIPFLOPRSoperation(const int & value);
  void     DECODERoperation(const int & value);

  //ALL COMPONENTS
  IComponent    *createComponent(const std::string &type, const std::string &value);

  IComponent    *create4081(const std::string &value);
  IComponent    *create4071(const std::string &value);
  IComponent    *create4011(const std::string &value);
  IComponent    *create4001(const std::string &value);
  IComponent    *create4030(const std::string &value);
  IComponent    *create4069(const std::string &value);
  IComponent    *create4514(const std::string &value);

  IComponent    *createInput(const std::string &value);
  IComponent    *createOutput(const std::string &value);
  IComponent    *createTrue(const std::string &value);
  IComponent    *createFalse(const std::string &value);
  IComponent    *createClock(const std::string &value);

public:
  typedef nts::IComponent *(Component::*func)(const std::string &);
  
  typedef struct  s_fnc_ptr
  {
    std::string   type;
    func          function;
  }               t_fnc_ptr;

protected:
  Pin           *_pins;
  t_gates       *_gates;

private:
  std::string   _name;
  std::string   _type;
  t_fnc_ptr     *_ptrs_fnc;
};

#endif /* !_COMPONENT_HPP_ */
