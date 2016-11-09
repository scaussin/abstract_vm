#include "TOperand.hpp"

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
TOperand &TOperand<T>::operator=(TOperand const &rhs)
{
	_value = _value;
	_type = ths._type;
	_value = rhs._value;
	return (*this);
}

virtual int TOperand<T>::getPrecision( void ) const
{
	return ((int)_type);
}

virtual eOperandType TOperand<T>::getType( void ) const
{
	return (_type);
}

virtual IOperand const * TOperand<T>::operator+( IOperand const & rhs ) const
{
	(void)rhs;
	return (iOperandFactory.createOperand(_type, std::to_string("1")));
}

virtual IOperand const * TOperand<T>::operator-( IOperand const & rhs ) const
{
	(void)rhs;
	return (iOperandFactory.createOperand(_type, std::to_string("1")));
}

virtual IOperand const * TOperand<T>::operator*( IOperand const & rhs ) const
{
	(void)rhs;
	return (iOperandFactory.createOperand(_type, std::to_string("1")));
}

virtual IOperand const * TOperand<T>::operator/( IOperand const & rhs ) const
{
	(void)rhs;
	return (iOperandFactory.createOperand(_type, std::to_string("1")));
}

virtual IOperand const * TOperand<T>::operator%( IOperand const & rhs ) const
{
	(void)rhs;
	return (iOperandFactory.createOperand(_type, std::to_string("1")));
}

virtual std::string const & TOperand<T>::toString( void ) const
{
	return (_toString);
}
