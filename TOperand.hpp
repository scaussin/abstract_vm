#ifndef TOPERAND_HPP
# define TOPERAND_HPP

extern Factory iOperandFactory;

template<typename T>
class TOperand : public IOperand {

	public :
		TOperand();
		TOperand(eOperandType, T);
		TOperand(TOperand const &);
		IOperand &operator=(TOperand const &rhs);
		//bool operator==(IOperand const & rhs );
		~TOperand();
		eOperandType _type;
		T _value;
		std::string _toString;

		virtual int getPrecision( void ) const;
		virtual eOperandType getType( void ) const;
		virtual IOperand const * operator+( IOperand const & rhs ) const;
		virtual IOperand const * operator-( IOperand const & rhs ) const;
		virtual IOperand const * operator*( IOperand const & rhs ) const;
		virtual IOperand const * operator/( IOperand const & rhs ) const;
		virtual IOperand const * operator%( IOperand const & rhs ) const;
		virtual std::string const & toString( void ) const;
        // virtual ~IOperand( void ) {}

	private :

};

template<typename T>
TOperand<T>::TOperand()
{
}

template <typename T>
TOperand<T>::TOperand(TOperand const &rhs)
{
	*this = rhs;
}

template <typename T>
TOperand<T>::TOperand(eOperandType type, T value) : _value(value)
{
	_type = type;
	_toString = "TOperand";
}

template <typename T>
IOperand & TOperand<T>::operator=(TOperand const &rhs)
{
	_value = rhs._value;
	_type = rhs._type;
	_value = rhs._value;
	return (this);
}
/*
template <typename T>
bool TOperand<T>::operator==(IOperand const & rhs )
{
TOperand const & ee = dynamic_cast<TOperand const &>(rhs);
	if (ee._value == _value)
		return (true);
	return (false);
}*/

template <typename T>
IOperand const * TOperand<T>::operator+( IOperand const & rhs ) const
{
	try {
		TOperand<int8_t> const & right = dynamic_cast<TOperand<int8_t> const &>(rhs);
		return (iOperandFactory.createOperand(std::max(_type, right._type), std::to_string((double)_value + (double)right._value)));
	}
	catch(const std::bad_cast& e) {}
	try {
		TOperand<int16_t> const & right = dynamic_cast<TOperand<int16_t> const &>(rhs);
		return (iOperandFactory.createOperand(std::max(_type, right._type), std::to_string((double)_value + (double)right._value)));
	}
	catch(const std::bad_cast& e) {}
	try {
		TOperand<int32_t> const & right = dynamic_cast<TOperand<int32_t> const &>(rhs);
		return (iOperandFactory.createOperand(std::max(_type, right._type), std::to_string((double)_value + (double)right._value)));
	}
	catch(const std::bad_cast& e) {}
	try {
		TOperand<float> const & right = dynamic_cast<TOperand<float> const &>(rhs);
		return (iOperandFactory.createOperand(std::max(_type, right._type), std::to_string((double)_value + (double)right._value)));
	}
	catch(const std::bad_cast& e) {}
	try {
		TOperand<double> const & right = dynamic_cast<TOperand<double> const &>(rhs);
		return (iOperandFactory.createOperand(std::max(_type, right._type), std::to_string((double)_value + (double)right._value)));
	}
	catch(const std::bad_cast& e) {}
	return (iOperandFactory.createOperand(eInt8, "0"));
}

template <typename T>
IOperand const * TOperand<T>::operator-( IOperand const & rhs ) const
{
	try {
		TOperand<int8_t> const & right = dynamic_cast<TOperand<int8_t> const &>(rhs);
		return (iOperandFactory.createOperand(std::max(_type, right._type), std::to_string((double)_value - (double)right._value)));
	}
	catch(const std::bad_cast& e) {}
	try {
		TOperand<int16_t> const & right = dynamic_cast<TOperand<int16_t> const &>(rhs);
		return (iOperandFactory.createOperand(std::max(_type, right._type), std::to_string((double)_value - (double)right._value)));
	}
	catch(const std::bad_cast& e) {}
	try {
		TOperand<int32_t> const & right = dynamic_cast<TOperand<int32_t> const &>(rhs);
		return (iOperandFactory.createOperand(std::max(_type, right._type), std::to_string((double)_value - (double)right._value)));
	}
	catch(const std::bad_cast& e) {}
	try {
		TOperand<float> const & right = dynamic_cast<TOperand<float> const &>(rhs);
		return (iOperandFactory.createOperand(std::max(_type, right._type), std::to_string((double)_value - (double)right._value)));
	}
	catch(const std::bad_cast& e) {}
	try {
		TOperand<double> const & right = dynamic_cast<TOperand<double> const &>(rhs);
		return (iOperandFactory.createOperand(std::max(_type, right._type), std::to_string((double)_value - (double)right._value)));
	}
	catch(const std::bad_cast& e) {}
	return (iOperandFactory.createOperand(eInt8, "0"));
}

template <typename T>
IOperand const * TOperand<T>::operator/( IOperand const & rhs ) const
{
		try {
		TOperand<int8_t> const & right = dynamic_cast<TOperand<int8_t> const &>(rhs);
		return (iOperandFactory.createOperand(std::max(_type, right._type), std::to_string((double)_value / (double)right._value)));
	}
	catch(const std::bad_cast& e) {}
	try {
		TOperand<int16_t> const & right = dynamic_cast<TOperand<int16_t> const &>(rhs);
		return (iOperandFactory.createOperand(std::max(_type, right._type), std::to_string((double)_value / (double)right._value)));
	}
	catch(const std::bad_cast& e) {}
	try {
		TOperand<int32_t> const & right = dynamic_cast<TOperand<int32_t> const &>(rhs);
		return (iOperandFactory.createOperand(std::max(_type, right._type), std::to_string((double)_value / (double)right._value)));
	}
	catch(const std::bad_cast& e) {}
	try {
		TOperand<float> const & right = dynamic_cast<TOperand<float> const &>(rhs);
		return (iOperandFactory.createOperand(std::max(_type, right._type), std::to_string((double)_value / (double)right._value)));
	}
	catch(const std::bad_cast& e) {}
	try {
		TOperand<double> const & right = dynamic_cast<TOperand<double> const &>(rhs);
		return (iOperandFactory.createOperand(std::max(_type, right._type), std::to_string((double)_value / (double)right._value)));
	}
	catch(const std::bad_cast& e) {}
	return (iOperandFactory.createOperand(eInt8, "0"));
}

template <typename T>
IOperand const * TOperand<T>::operator*( IOperand const & rhs ) const
{
	try {
		TOperand<int8_t> const & right = dynamic_cast<TOperand<int8_t> const &>(rhs);
		return (iOperandFactory.createOperand(std::max(_type, right._type), std::to_string((double)_value * (double)right._value)));
	}
	catch(const std::bad_cast& e) {}
	try {
		TOperand<int16_t> const & right = dynamic_cast<TOperand<int16_t> const &>(rhs);
		return (iOperandFactory.createOperand(std::max(_type, right._type), std::to_string((double)_value * (double)right._value)));
	}
	catch(const std::bad_cast& e) {}
	try {
		TOperand<int32_t> const & right = dynamic_cast<TOperand<int32_t> const &>(rhs);
		return (iOperandFactory.createOperand(std::max(_type, right._type), std::to_string((double)_value * (double)right._value)));
	}
	catch(const std::bad_cast& e) {}
	try {
		TOperand<float> const & right = dynamic_cast<TOperand<float> const &>(rhs);
		return (iOperandFactory.createOperand(std::max(_type, right._type), std::to_string((double)_value * (double)right._value)));
	}
	catch(const std::bad_cast& e) {}
	try {
		TOperand<double> const & right = dynamic_cast<TOperand<double> const &>(rhs);
		return (iOperandFactory.createOperand(std::max(_type, right._type), std::to_string((double)_value * (double)right._value)));
	}
	catch(const std::bad_cast& e) {}
	return (iOperandFactory.createOperand(eInt8, "0"));
}

template <typename T>
IOperand const * TOperand<T>::operator%( IOperand const & rhs ) const
{
	try {
		TOperand<int8_t> const & right = dynamic_cast<TOperand<int8_t> const &>(rhs);
		return (iOperandFactory.createOperand(std::max(_type, right._type), std::to_string((int)_value % (int)right._value)));
	}
	catch(const std::bad_cast& e) {}
	try {
		TOperand<int16_t> const & right = dynamic_cast<TOperand<int16_t> const &>(rhs);
		return (iOperandFactory.createOperand(std::max(_type, right._type), std::to_string((int)_value % (int)right._value)));
	}
	catch(const std::bad_cast& e) {}
	try {
		TOperand<int32_t> const & right = dynamic_cast<TOperand<int32_t> const &>(rhs);
		return (iOperandFactory.createOperand(std::max(_type, right._type), std::to_string((int)_value % (int)right._value)));
	}
	catch(const std::bad_cast& e) {}
	try {
		TOperand<float> const & right = dynamic_cast<TOperand<float> const &>(rhs);
		return (iOperandFactory.createOperand(std::max(_type, right._type), std::to_string((int)_value % (int)right._value)));
	}
	catch(const std::bad_cast& e) {}
	try {
		TOperand<double> const & right = dynamic_cast<TOperand<double> const &>(rhs);
		return (iOperandFactory.createOperand(std::max(_type, right._type), std::to_string((int)_value % (int)right._value)));
	}
	catch(const std::bad_cast& e) {}
	return (iOperandFactory.createOperand(eInt8, "0"));
}

template <typename T>
eOperandType TOperand<T>::getType( void ) const
{
	return (_type);
}

template <typename T>
int TOperand<T>::getPrecision( void ) const
{
	return ((int)_type);
}

template <typename T>
std::string const & TOperand<T>::toString( void ) const
{
	return (_toString);
}

template <typename T>
TOperand<T>::~TOperand()
{
}

#endif
