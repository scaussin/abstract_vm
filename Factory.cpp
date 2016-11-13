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
	(void)type;
	(void)value;
	return ((this->*_tabFactoryOperand[(int)type])(value));
}

IOperand const * Factory::createInt8(std::string const & value) const
{
    int result = std::stoi(value, NULL, 10);
    if (result > 127)
        throw AbstractException("int8_t overflow");
    if (result < -127)
        throw AbstractException("int8_t underflow");
	return (new TOperand<int8_t>(eInt8, result));
}

IOperand const * Factory::createInt16(std::string const & value) const
{
    int result = std::stoi(value, NULL, 10);
	return (new TOperand<int16_t>(eInt16, result));
}

IOperand const * Factory::createInt32(std::string const & value) const
{
    int result = std::stoi(value, NULL, 10);
	return (new TOperand<int32_t>(eInt32, result));
}

IOperand const * Factory::createFloat(std::string const & value) const
{
    float result = std::stof(value);
	return (new TOperand<float>(eFloat, result));
}

IOperand const * Factory::createDouble(std::string const & value) const
{
    double result = std::stod(value);
	return (new TOperand<double>(eDouble, result));
}
