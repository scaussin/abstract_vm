#include "main.hpp"

Factory::Factory()
{
	_tabFactoryOperand[eInt8] = &Factory::createInt8;
	_tabFactoryOperand[eInt16] = &Factory::createInt16;
	_tabFactoryOperand[eInt32] = &Factory::createInt32;
	_tabFactoryOperand[eFloat] = &Factory::createFloat;
	_tabFactoryOperand[eDouble] = &Factory::createDouble;

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
	(void)rhs;
	return (*this);
}

IOperand const * Factory::createOperand(eOperandType type, std::string const & value) const
{
	return ((this->*_tabFactoryOperand[(int)type])(value));
}

IOperand const * Factory::createInt8(std::string const & value) const
{
	int result;
	try
	{
		std::size_t lastChar;
		result = std::stoi(value, &lastChar, 10);
	}
	catch (std::out_of_range & e)
	{
		throw(AbstractException("\033[31mError run time:\033[m int8 out of range"));
	}
	if (result > 127)
		throw(AbstractException("\033[31mError run time:\033[m int8 overflow"));
	if (result < -127)
		throw(AbstractException("\033[31mError run time:\033[m int8 underflow"));
	return (new TOperand<int8_t>(eInt8, result));
}

IOperand const * Factory::createInt16(std::string const & value) const
{
	int result;
	try
	{
		std::size_t lastChar;
		result = std::stoi(value, &lastChar, 10);
	}
	catch (std::out_of_range & e)
	{
		throw(AbstractException("\033[31mError run time:\033[m int16 out of range"));
	}
	if (result > 32767)
		throw(AbstractException("\033[31mError run time:\033[m int16 overflow"));
	if (result < -32768)
		throw(AbstractException("\033[31mError run time:\033[m int16 underflow"));
	return (new TOperand<int16_t>(eInt16, result));
}

IOperand const * Factory::createInt32(std::string const & value) const
{
	int result;
	try
	{
		std::size_t lastChar;
		result = std::stoi(value, &lastChar, 10);
	}
	catch (std::out_of_range & e)
	{
		throw(AbstractException("\033[31mError run time:\033[m int32 out of range"));
	}
	return (new TOperand<int32_t>(eInt32, result));
}

IOperand const * Factory::createFloat(std::string const & value) const
{
	float result;
	try
	{
		std::size_t lastChar;
		result = std::stof(value, &lastChar);
	}
	catch (std::out_of_range & e)
	{
		throw(AbstractException("\033[31mError run time:\033[m float out of range"));
	}
	return (new TOperand<float>(eFloat, result));

	/*float result = std::stof(value);
	return (new TOperand<float>(eFloat, result));*/
}

IOperand const * Factory::createDouble(std::string const & value) const
{
	double result = std::stod(value);
	return (new TOperand<double>(eDouble, result));
}
