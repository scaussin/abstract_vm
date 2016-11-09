#ifndef FACTORY_HPP
# define FACTORY_HPP

#include <string>
#include <vector>
#include <map>
#include "AbstractException.hpp"
#include "main.hpp"
#include "IOperand.hpp"

class Factory {

	public :
		Factory();
		Factory(tToken *);
		Factory(Factory const &);
		Factory &operator=(Factory const &rhs);
		~Factory();
		tToken *_tokens;
		IOperand const * createOperand( eOperandType type, std::string const & value ) const;
		std::map<eOperandType, IOperand const * (Factory::*)( std::string const & value )> _mapFactoryOperand;

	private :
		IOperand const * createInt8( std::string const & value ) const;
		IOperand const * createInt16( std::string const & value ) const;
		IOperand const * createInt32( std::string const & value ) const;
		IOperand const * createFloat( std::string const & value ) const;
		IOperand const * createDouble( std::string const & value ) const;

};

#endif