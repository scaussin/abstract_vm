#ifndef TOPERAND_HPP
# define TOPERAND_HPP

#include "Factory.hpp"
#include <string>
#include <vector>
#include "AbstractException.hpp"
#include "IOperand.hpp"
#include "main.hpp"

template<typename T>
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
		virtual IOperand const * operator+( IOperand const & rhs ) const;
		virtual IOperand const * operator-( IOperand const & rhs ) const;
		virtual IOperand const * operator*( IOperand const & rhs ) const;
		virtual IOperand const * operator/( IOperand const & rhs ) const;
		virtual IOperand const * operator%( IOperand const & rhs ) const;
		virtual std::string const & toString( void ) const;
        //virtual ~IOperand( void ) {}

	private :

};

#endif
