#ifndef INT8_HPP
# define INT8_HPP

#include <string>
#include <vector>
#include "AbstractException.hpp"
#include "IOperand.hpp"
#include "main.hpp"

class Int8 : public IOperand{

	public :
		Int8();
		Int8(int8_t);
		Int8(Int8 const &);
		Int8 &operator=(Int8 const &rhs);
		~Int8();
		int8_t _value;
		std::string _toString;

		virtual int getPrecision( void ) const;
		virtual eOperandType getType( void ) const;
		virtual IOperand const * operator+( IOperand const & rhs ) const;
		virtual IOperand const * operator-( IOperand const & rhs ) const;
		virtual IOperand const * operator*( IOperand const & rhs ) const;
		virtual IOperand const * operator/( IOperand const & rhs ) const;
		virtual IOperand const * operator%( IOperand const & rhs ) const;
		virtual std::string const & toString( void ) const;

	private :

};

#endif