#ifndef TOPERAND_HPP
# define TOPERAND_HPP

extern Factory iOperandFactory;

template<class T>
class TOperand : public IOperand {

	public :
		TOperand();
		TOperand(T);
		TOperand(TOperand const &);
		IOperand &operator=(TOperand const &rhs);
		~TOperand();
		eOperandType _type;
		T _value;
		std::string _toString;

		virtual int getPrecision( void ) const;
		virtual eOperandType getType( void ) const;
		IOperand const * operator+( IOperand const & rhs ) const;
		/*virtual IOperand const * operator-( IOperand const & rhs ) const;
		virtual IOperand const * operator*( IOperand const & rhs ) const;
		virtual IOperand const * operator/( IOperand const & rhs ) const;
		virtual IOperand const * operator%( IOperand const & rhs ) const;*/
		virtual std::string const & toString( void ) const;
        //virtual ~IOperand( void ) {}

	private :

};

template <typename T>
TOperand<T>::TOperand()
{	
}

template <typename T>
TOperand<T>::TOperand(TOperand const &rhs)
{
	*this = rhs;
}

template <class T>
TOperand<T>::TOperand(T value) : _value(value)
{
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

//Factory iOperandFactory;

template <typename T>
IOperand const * TOperand<T>::operator+( IOperand const & rhs ) const
{
	TOperand const & ee = dynamic_cast<TOperand const &>(rhs);
	return (iOperandFactory.createOperand(_type, std::to_string(_value + ee._value)));
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
