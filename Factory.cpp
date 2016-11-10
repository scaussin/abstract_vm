#include "main.hpp"

Factory::Factory()
{
}

Factory::Factory(tToken * tokens) : _tokens(tokens)
{
	_tabFactoryOperand[eInt8] = &Factory::createInt8;
	/*_tabFactoryOperand[eInt16] = &Factory::createInt16;
	_tabFactoryOperand[eInt32] = &Factory::createInt32;
	_tabFactoryOperand[eFloat] = &Factory::createFloat;
	_tabFactoryOperand[eDouble] = &Factory::createDouble;*/
    /*mapt['c'] = 5;
    std::cout <<  mapt['c'] ;*/

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
	return ((this->*_tabFactoryOperand[(int)type])(value));
}

IOperand const * Factory::createInt8( std::string const & value ) const
{
	//Int8_t i = 0;
    (void)value;
	return (new TOperand<int8_t>(0));
}
/*
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
}*/
