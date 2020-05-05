//
// Component.cpp for Component in /home/tekm/tek2/cpp_nanotekspice
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Mon Feb 27 19:29:33 2017 leroy_0
// Last update Mon Feb 27 19:29:34 2017 leroy_0
//

#include "Component.hpp"
#include "C4081.hpp"
#include "C4071.hpp"
#include "C4001.hpp"
#include "C4030.hpp"
#include "C4069.hpp"
#include "C4011.hpp"
#include "C4514.hpp"

Component::Component()
{
	_gates = NULL;

	_ptrs_fnc = new t_fnc_ptr[13];
	_ptrs_fnc[0].type = std::string("4081");
	_ptrs_fnc[0].function = &Component::create4081;
	_ptrs_fnc[1].type = std::string("4071");
	_ptrs_fnc[1].function = &Component::create4071;
	_ptrs_fnc[2].type = std::string("4011");
	_ptrs_fnc[2].function = &Component::create4011;
	_ptrs_fnc[3].type = std::string("4001");
	_ptrs_fnc[3].function = &Component::create4001;
	_ptrs_fnc[4].type = std::string("4030");
	_ptrs_fnc[4].function = &Component::create4030;
	_ptrs_fnc[5].type = std::string("4069");
	_ptrs_fnc[5].function = &Component::create4069;
	_ptrs_fnc[6].type = std::string("4514");
	_ptrs_fnc[6].function = &Component::create4514;
	_ptrs_fnc[7].type = std::string("output");
	_ptrs_fnc[7].function = &Component::createOutput;
	_ptrs_fnc[8].type = std::string("input");
	_ptrs_fnc[8].function = &Component::createInput;
	_ptrs_fnc[9].type = std::string("true");
	_ptrs_fnc[9].function = &Component::createTrue;
	_ptrs_fnc[10].type = std::string("false");
	_ptrs_fnc[10].function = &Component::createFalse;
	_ptrs_fnc[11].type = std::string("clock");
	_ptrs_fnc[11].function = &Component::createClock;
	_ptrs_fnc[12].type = std::string("");
}

std::string	 	Component::getName() const
{
	return (_name);
}

std::string	 	Component::getType() const
{
	return (_type);
}

Pin 			*Component::getPins()
{
	return (_pins);
}

t_gates 		*Component::getGates()
{
	return (_gates);
}

void 			Component::setName(const std::string &name)
{
	_name = name;
}

void 			Component::setType(const std::string &type)
{
	_type = type;
}

void 			Component::setPins(Pin * pin)
{
	_pins = pin;
}

void 			Component::setGate(const int *values, const int &value_size, const GateType &state, const int *pins, const int &pins_size)
{
	int 		x = 0;

	while (x < _gates[0].size && _gates[x].state != GateType::UNDEFINED)
		x++;

	if (x >= _gates[0].size)
		return ;

	_gates[x].state = state;
	_gates[x].value = new int[value_size];
	_gates[x].inputs = new int[pins_size];

	for (int i = 0; i < pins_size; ++i)
		_gates[x].inputs[i] = pins[i];
	for (int i = 0; i < value_size; ++i)
		_gates[x].value[i] = values[i];
}

void 			Component::initGates(const int &size, const GateType &state)
{
  int 			i = 0;

  _gates = new t_gates[size];
  while (i < size)
  {
    _gates[i].state = state;
    _gates[i].size = size;
    i++;
  }
}

nts::Tristate 	Component::Compute(size_t pin_num_this)
{
	std::cout << "compute: " << _name << ": pin: " << pin_num_this << std::endl;
	return (_pins->getState(pin_num_this));
}

void 			Component::SetLink(size_t pin_num_this, nts::IComponent &component, size_t pin_num_target)
{
	pin_num_this -= 1;
	pin_num_target -= 1;

	Component *compo = (Component *)&component;

	_pins->setState(pin_num_target, compo->getPins()->getState(pin_num_this));
	_pins->setLinkComp(component, pin_num_target, pin_num_this);
}

void 			Component::Dump(void) const
{
	int 		x = 0;

	std::cout << _name << ":" << std::endl;
	if (_type.compare("output") == 0 || _type.compare("input") == 0
		|| _type.compare("true") == 0 || _type.compare("false") == 0
		|| _type.compare("clock") == 0)
		std::cout << _type << " - value: " << _pins->getState(0) << std::endl;
	else
		std::cout << "Chipset " << _type << std::endl;

	while (x < _pins->getSize(0))
	{
		std::cout << "\tpin #" << x + 1 << ": ";
		if (_type.compare("output") == 0 || _type.compare("input") == 0
		|| _type.compare("true") == 0 || _type.compare("false") == 0
		|| _type.compare("clock") == 0)
		{
			std::cout << "linked" << std::endl;
		}
		else
		{
			if (_pins->getState(x) == nts::Tristate::UNDEFINED)
				std::cout << "NULL" << std::endl;
			else
				std::cout << _pins->getState(x) << std::endl;
		}
		x++;
	}
}

void 			Component::DECODERoperation(const int & value)
{
	bool 		state1;
	bool 		state2;
	bool 		state3;
	bool 		state4;
	bool 		inhibit;
	nts::Tristate 	*out = new nts::Tristate[16];

	if (getPins()->getLinkPins(getGates()[value].inputs[0] - 1) == NULL
		|| getPins()->getLinkPins(getGates()[value].inputs[1] - 1) == NULL
		|| getPins()->getLinkPins(getGates()[value].inputs[2] - 1) == NULL
		|| getPins()->getLinkPins(getGates()[value].inputs[3] - 1) == NULL
		|| getPins()->getLinkPins(getGates()[value].inputs[4] - 1) == NULL
		|| getGates() == NULL)
		return ;

	state1 = getPins()->getLinkPins(getGates()[value].inputs[0] - 1)->getState(getPins()->getLinkValue(getGates()[value].inputs[0] - 1));
	state2 = getPins()->getLinkPins(getGates()[value].inputs[1] - 1)->getState(getPins()->getLinkValue(getGates()[value].inputs[1] - 1));
	state3 = getPins()->getLinkPins(getGates()[value].inputs[2] - 1)->getState(getPins()->getLinkValue(getGates()[value].inputs[2] - 1));
	state4 = getPins()->getLinkPins(getGates()[value].inputs[3] - 1)->getState(getPins()->getLinkValue(getGates()[value].inputs[3] - 1));
	inhibit = getPins()->getLinkPins(getGates()[value].inputs[4] - 1)->getState(getPins()->getLinkValue(getGates()[value].inputs[4] - 1));

	if (!inhibit)
	{
		out[0] = nts::Tristate((bool)(~state1 & ~state2 & ~state3 & ~state4));
		out[1] = nts::Tristate((bool)(state1 & ~state2 & ~state3 & ~state4));
		out[2] = nts::Tristate((bool)(~state1 & state2 & ~state3 & ~state4));
		out[3] = nts::Tristate((bool)(state1 & state2 & ~state3 & ~state4));
		out[4] = nts::Tristate((bool)(~state1 & ~state2 & state3 & ~state4));
		out[5] = nts::Tristate((bool)(state1 & ~state2 & state3 & ~state4));
		out[6] = nts::Tristate((bool)(~state1 & state2 & state3 & ~state4));
		out[7] = nts::Tristate((bool)(state1 & state2 & state3 & ~state4));
		out[8] = nts::Tristate((bool)(~state1 & ~state2 & ~state3 & state4));
		out[9] = nts::Tristate((bool)(state1 & ~state2 & ~state3 & state4));
		out[10] = nts::Tristate((bool)(~state1 & state2 & ~state3 & state4));
		out[11] = nts::Tristate((bool)(state1 & state2 & ~state3 & state4));
		out[12] = nts::Tristate((bool)(~state1 & ~state2 & state3 & state4));
		out[13] = nts::Tristate((bool)(state1 & ~state2 & state3 & state4));
		out[14] = nts::Tristate((bool)(~state1 & state2 & state3 & state4));
		out[15] = nts::Tristate((bool)(state1 & state2 & state3 & state4));

		for (int i = 0; i < 16; i++)
		{
			getPins()->setState(getGates()[value].value[i] - 1, out[i]);
		}
	}
	else
	{
		for (int i = 0; i < 16; i++)
		{
			getPins()->setState(getGates()[value].value[i] - 1, nts::Tristate::FALSE);
		}
	}
}

void 			Component::FLIPFLOPRSoperation(const int & value)
{
	bool			state1;
	bool			state2;

	if (getPins()->getLinkPins(getGates()[value].inputs[0] - 1) == NULL || getPins()->getLinkPins(getGates()[value].inputs[1] - 1) == NULL)
		return ;

	state1 = getPins()->getLinkPins(getGates()[value].inputs[0] - 1)->getState(getPins()->getLinkValue(getGates()[value].inputs[0] - 1));
	state2 = getPins()->getLinkPins(getGates()[value].inputs[1] - 1)->getState(getPins()->getLinkValue(getGates()[value].inputs[1] - 1));

	if ((state1 && !state2) || (!state1 && state2))
	{
		if (getPins()->getLinkPins(getGates()[value].value[0] - 1))
			getPins()->getLinkPins(getGates()[value].value[0] - 1)->setState(getPins()->getLinkValue(getGates()[value].inputs[0] - 1), (nts::Tristate)state2);
		if (getPins()->getLinkPins(getGates()[value].value[1] - 1))
			getPins()->getLinkPins(getGates()[value].value[1] - 1)->setState(getPins()->getLinkValue(getGates()[value].inputs[1] - 1), (nts::Tristate)((bool)!state2));
		getPins()->setState(getGates()[value].value[0] - 1, (nts::Tristate)state2);
		getPins()->setState(getGates()[value].value[1] - 1, (nts::Tristate)((bool)!state2));
	}
	else if (!state1 && !state2)
	{
		if (getPins()->getLinkPins(getGates()[value].value[0] - 1))
			getPins()->getLinkPins(getGates()[value].value[0] - 1)->setState(getPins()->getLinkValue(getGates()[value].inputs[0] - 1), (nts::Tristate)state2);
		if (getPins()->getLinkPins(getGates()[value].value[1] - 1))
			getPins()->getLinkPins(getGates()[value].value[1] - 1)->setState(getPins()->getLinkValue(getGates()[value].inputs[1] - 1), (nts::Tristate)((bool)!state2));
		getPins()->setState(getGates()[value].value[0] - 1, nts::Tristate::TRUE);
		getPins()->setState(getGates()[value].value[1] - 1, nts::Tristate::TRUE);
	}
	else
	{
		if (getPins()->getState(getGates()[value].value[0] - 1) == nts::Tristate::UNDEFINED)
		{
			if (getPins()->getLinkPins(getGates()[value].value[0] - 1))
				getPins()->getLinkPins(getGates()[value].value[0] - 1)->setState(getPins()->getLinkValue(getGates()[value].inputs[0] - 1), nts::Tristate::FALSE);
			getPins()->setState(getGates()[value].value[0] - 1, nts::Tristate::FALSE);
		}
		if (getPins()->getState(getGates()[value].value[1] - 1) == (nts::Tristate::UNDEFINED))
		{
			if (getPins()->getLinkPins(getGates()[value].value[1] - 1))
				getPins()->getLinkPins(getGates()[value].value[1] - 1)->setState(getPins()->getLinkValue(getGates()[value].inputs[1] - 1), nts::Tristate::FALSE);
			getPins()->setState(getGates()[value].value[1] - 1, nts::Tristate::FALSE);
		}
	}
}

void 			Component::XORoperation(const int & value)
{
	bool			state1;
	bool			state2;
	nts::Tristate	out;

	if (getPins()->getLinkPins(getGates()[value].inputs[0] - 1) == NULL || getPins()->getLinkPins(getGates()[value].inputs[1] - 1) == NULL)
		return ;

	state1 = getPins()->getLinkPins(getGates()[value].inputs[0] - 1)->getState(getPins()->getLinkValue(getGates()[value].inputs[0] - 1));
	state2 = getPins()->getLinkPins(getGates()[value].inputs[1] - 1)->getState(getPins()->getLinkValue(getGates()[value].inputs[1] - 1));

	out = (nts::Tristate)(state1 ^ state2);

	if (getPins()->getLinkPins(getGates()[value].value[0] - 1))
		getPins()->getLinkPins(getGates()[value].value[0] - 1)->setState(getPins()->getLinkValue(getGates()[value].inputs[0] - 1), out);

	getPins()->setState(getGates()[value].value[0] - 1, out);
}

void 			Component::NOToperation(const int & value)
{
	bool			state1;
	nts::Tristate	out;

	if (getPins()->getLinkPins(getGates()[value].inputs[0] - 1) == NULL)
		return ;

	state1 = getPins()->getLinkPins(getGates()[value].inputs[0] - 1)->getState(getPins()->getLinkValue(getGates()[value].inputs[0] - 1));

	out = (nts::Tristate)((bool)(!state1));

	if (getPins()->getLinkPins(getGates()[value].value[0] - 1))
		getPins()->getLinkPins(getGates()[value].value[0] - 1)->setState(getPins()->getLinkValue(getGates()[value].inputs[0] - 1), out);
	getPins()->setState(getGates()[value].value[0] - 1, out);
}	

void 			Component::NORoperation(const int & value)
{
	bool			state1;
	bool			state2;
	nts::Tristate	out;

	if (getPins()->getLinkPins(getGates()[value].inputs[0] - 1) == NULL || getPins()->getLinkPins(getGates()[value].inputs[1] - 1) == NULL)
		return ;

	state1 = getPins()->getLinkPins(getGates()[value].inputs[0] - 1)->getState(getPins()->getLinkValue(getGates()[value].inputs[0] - 1));
	state2 = getPins()->getLinkPins(getGates()[value].inputs[1] - 1)->getState(getPins()->getLinkValue(getGates()[value].inputs[1] - 1));

	out = (nts::Tristate)(bool)(!(state1 || state2));

	if (getPins()->getLinkPins(getGates()[value].value[0] - 1))
		getPins()->getLinkPins(getGates()[value].value[0] - 1)->setState(getPins()->getLinkValue(getGates()[value].inputs[0] - 1), out);
	getPins()->setState(getGates()[value].value[0] - 1, out);
}	

void 			Component::NANDoperation(const int & value)
{
	bool			state1;
	bool			state2;
	nts::Tristate	out;

	if (getPins()->getLinkPins(getGates()[value].inputs[0] - 1) == NULL || getPins()->getLinkPins(getGates()[value].inputs[1] - 1) == NULL)
		return ;

	state1 = getPins()->getLinkPins(getGates()[value].inputs[0] - 1)->getState(getPins()->getLinkValue(getGates()[value].inputs[0] - 1));
	state2 = getPins()->getLinkPins(getGates()[value].inputs[1] - 1)->getState(getPins()->getLinkValue(getGates()[value].inputs[1] - 1));

	out = (nts::Tristate)(bool)(!(state1 && state2));

	if (getPins()->getLinkPins(getGates()[value].value[0] - 1))
		getPins()->getLinkPins(getGates()[value].value[0] - 1)->setState(getPins()->getLinkValue(getGates()[value].inputs[0] - 1), out);
	getPins()->setState(getGates()[value].value[0] - 1, out);
}	

void 			Component::ORoperation(const int & value)
{
	bool			state1;
	bool			state2;
	nts::Tristate	out;

	if (getPins()->getLinkPins(getGates()[value].inputs[0] - 1) == NULL || getPins()->getLinkPins(getGates()[value].inputs[1] - 1) == NULL)
		return ;

	state1 = getPins()->getLinkPins(getGates()[value].inputs[0] - 1)->getState(getPins()->getLinkValue(getGates()[value].inputs[0] - 1));
	state2 = getPins()->getLinkPins(getGates()[value].inputs[1] - 1)->getState(getPins()->getLinkValue(getGates()[value].inputs[1] - 1));

	out = (nts::Tristate)(state1 | state2);
	
	if (getPins()->getLinkPins(getGates()[value].value[0] - 1))
		getPins()->getLinkPins(getGates()[value].value[0] - 1)->setState(getPins()->getLinkValue(getGates()[value].inputs[0] - 1), out);
	getPins()->setState(getGates()[value].value[0] - 1, out);
}

void 			Component::ANDoperation(const int & value)
{
	bool			state1;
	bool			state2;
	nts::Tristate	out;

	if (getPins()->getLinkPins(getGates()[value].inputs[0] - 1) == NULL || getPins()->getLinkPins(getGates()[value].inputs[1] - 1) == NULL)
		return ;

	state1 = getPins()->getLinkPins(getGates()[value].inputs[0] - 1)->getState(getPins()->getLinkValue(getGates()[value].inputs[0] - 1));
	state2 = getPins()->getLinkPins(getGates()[value].inputs[1] - 1)->getState(getPins()->getLinkValue(getGates()[value].inputs[1] - 1));

	out = (nts::Tristate)(state1 && state2);

	if (getPins()->getLinkPins(getGates()[value].value[0] - 1))
		getPins()->getLinkPins(getGates()[value].value[0] - 1)->setState(getPins()->getLinkValue(getGates()[value].inputs[0] - 1), out);
	getPins()->setState(getGates()[value].value[0] - 1, out);
}

void 			Component::switchOperations()
{
	for (int i = 0;getGates() && i < getGates()[0].size; i++)
   	{
       	if (getGates()[i].state == GateType::AND)
   			ANDoperation(i);
   		else if (getGates()[i].state == GateType::OR)
   			ORoperation(i);
   		else if (getGates()[i].state == GateType::NAND)
   			NANDoperation(i);
   		else if (getGates()[i].state == GateType::NOR)
   			NORoperation(i);
   		else if (getGates()[i].state == GateType::NOT)
   			NOToperation(i);
   		else if (getGates()[i].state == GateType::XOR)
   			XORoperation(i);
   		else if (getGates()[i].state == GateType::FLIPFLOPRS)
   			FLIPFLOPRSoperation(i);
   		else if (getGates()[i].state == GateType::DECODER)
   			DECODERoperation(i);
  	}
}

nts::IComponent 	*Component::create4081(const std::string &value)
{
	return (new C4081(value));
}

nts::IComponent 	*Component::create4071(const std::string &value)
{
	return (new C4071(value));
}

nts::IComponent 	*Component::create4011(const std::string &value)
{
	return (new C4011(value));
}

nts::IComponent 	*Component::create4001(const std::string &value)
{
	return (new C4001(value));
}

nts::IComponent 	*Component::create4030(const std::string &value)
{
	return (new C4030(value));
}

nts::IComponent 	*Component::create4069(const std::string &value)
{
	return (new C4069(value));
}

nts::IComponent 	*Component::create4514(const std::string &value)
{
	return (new C4514(value));
}


nts::IComponent 	*Component::createInput(const std::string &value)
{
	Component 		*component = new Component();

	component->setName(value);
	component->setType("input");
	component->setPins(new Pin(1, nts::Tristate::UNDEFINED));
	return (component);
}

nts::IComponent 	*Component::createOutput(const std::string &value)
{
	Component 		*component = new Component();

	component->setName(value);
	component->setType("output");
	component->setPins(new Pin(1, nts::Tristate::UNDEFINED));
	return (component);
}

nts::IComponent 	*Component::createTrue(const std::string &value)
{
	Component 		*component = new Component();

	component->setName(value);
	component->setType("true");
	component->setPins(new Pin(1, nts::Tristate::TRUE));
	return (component);
}

nts::IComponent 	*Component::createFalse(const std::string &value)
{
	Component 		*component = new Component();

	component->setName(value);
	component->setType("false");
	component->setPins(new Pin(1, nts::Tristate::FALSE));
	return (component);
}

nts::IComponent 	*Component::createClock(const std::string &value)
{
	Component 		*component = new Component();

	component->setName(value);
	component->setType("clock");
	component->setPins(new Pin(1, nts::Tristate::FALSE));
	return (component);
}

nts::IComponent 	*Component::createComponent(const std::string &type, const std::string &value)
{
	for (int i = 0; !_ptrs_fnc[i].type.empty(); i++)
	{
        if (_ptrs_fnc[i].type.compare(type) == 0)
            return ((this->*_ptrs_fnc[i].function)(value));
    }

    throw nts::Error(std::cerr, "Component or chipset not recognized");
	return (NULL);
}