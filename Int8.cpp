#include "Int8.hpp"

Int8::Int8()
{
}

Int8::Int8(int8_t value) : _value(value)
{
	_toString = "Int8";
}

Int8::Int8(Int8 const &rhs)
{
	*this = rhs;
}

Int8::~Int8()
{
}

Int8 &Int8::operator=(Int8 const &rhs)
{
	_value = rhs._value;
	return (*this);
}


int Int8::getPrecision( void ) const
{
	return ((int)eInt8);
}
eOperandType Int8::getType( void ) const
{
	return (eInt8);
}

IOperand const * Int8::operator+( IOperand const & rhs ) const
{
	double res = rhs._value + _value;
	
}

IOperand const * Int8::operator-( IOperand const & rhs ) const
{

}

IOperand const * Int8::operator*( IOperand const & rhs ) const
{

}

IOperand const * Int8::operator/( IOperand const & rhs ) const
{

}

IOperand const * Int8::operator%( IOperand const & rhs ) const
{

}

std::string const & Int8::toString( void ) const
{
	return (_toString);
}
