#include "Factory.hpp"
#include <iostream>

Factory::Factory()
{
}

Factory::Factory(tToken * tokens) : _tokens(tokens)
{
	_mapFactoryOperand[eInt8] = &Factory::createInt8;
	_mapFactoryOperand[eInt16] = &Factory::createInt16;
	_mapFactoryOperand[eInt32] = &Factory::createInt32;
	_mapFactoryOperand[eFloat] = &Factory::createFloat;
	_mapFactoryOperand[eDouble] = &Factory::createDouble;
    /*map['c'] = 5;
    std::cout <<  map['c'] ;*/

}

Factory::Factory(Factory const &rhs)
{
	*this = rhs;
}

Factory::~Factory()
{
}

Factory &Factory::operator=(Factory const &rhs)
{
	_tokens = rhs._tokens;
	return (*this);
}

IOperand const * Factory::createOperand( eOperandType type, std::string const & value ) const
{
	(void)type;
	(void)value;
	//(this->*i->func)(token);
	/*IOperand const * res = NULL;
	res = (this->*_mapFactoryOperand[(int)type])(value);*/
	return(new TOperand<int8_t>(0));
}

IOperand const * Factory::createInt8( std::string const & value ) const
{
	//Int8_t i = 0;
    (void)value;
	return (new TOperand<int8_t>(0));
}

IOperand const * Factory::createInt16( std::string const & value ) const
{
    (void)value;
	return (new TOperand<int16_t>(0));
}

IOperand const * Factory::createInt32( std::string const & value ) const
{
    (void)value;
	return (new TOperand<int32_t>(0));
}

IOperand const * Factory::createFloat( std::string const & value ) const
{
    (void)value;
	return (new TOperand<float>(0));
}

IOperand const * Factory::createDouble( std::string const & value ) const
{
    (void)value;
	return (new TOperand<double>(0));
}
