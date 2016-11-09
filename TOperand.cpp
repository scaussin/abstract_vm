#include "TOperand.hpp"

extern Factory iOperandFactory;

template <typename T>
TOperand<T>::TOperand()
{
}

template <typename T>
TOperand<T>::TOperand(T value) : _value(value)
{
	_toString = "TOperand";
}

template <typename T>
TOperand<T>::TOperand(TOperand const &rhs)
{
	*this = rhs;
}

template <typename T>
TOperand<T>::~TOperand()
{
}

template <typename T>
IOperand & TOperand<T>::operator=(TOperand const &rhs)
{
	_value = rhs._value;
	_type = rhs._type;
	_value = rhs._value;
	return (this);
}

template <typename T>
int TOperand<T>::getPrecision( void ) const
{
	return ((int)_type);
}

template <typename T>
eOperandType TOperand<T>::getType( void ) const
{
	return (_type);
}
template <typename T>
IOperand const * TOperand<T>::operator+( IOperand const & rhs ) const
{
	(void)rhs;
	return (iOperandFactory.createOperand(_type, std::string("1")));
}
template <typename T>
IOperand const * TOperand<T>::operator-( IOperand const & rhs ) const
{
	(void)rhs;
    return (iOperandFactory.createOperand(_type, std::string("1")));
}

template <typename T>
IOperand const * TOperand<T>::operator*( IOperand const & rhs ) const
{
	(void)rhs;
	return (iOperandFactory.createOperand(_type, std::string("1")));
}

template <typename T>
IOperand const * TOperand<T>::operator/( IOperand const & rhs ) const
{
	(void)rhs;
	return (iOperandFactory.createOperand(_type, std::string("1")));
}

template <typename T>
IOperand const * TOperand<T>::operator%( IOperand const & rhs ) const
{
	(void)rhs;
	return (iOperandFactory.createOperand(_type, std::string("1")));
}

template <typename T>
std::string const & TOperand<T>::toString( void ) const
{
	return (_toString);
}
