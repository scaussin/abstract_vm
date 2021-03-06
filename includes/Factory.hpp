#ifndef FACTORY_HPP
# define FACTORY_HPP

class Factory {

	public :
		Factory();
		Factory(Factory const &);
		Factory &operator=(Factory const &rhs);
		~Factory();
		IOperand const * createOperand( eOperandType type, std::string const & value ) const;
		IOperand const * (Factory::*_tabFactoryOperand[5])( std::string const & value ) const ;

	private :
		IOperand const * createInt8( std::string const & value ) const;
		IOperand const * createInt16( std::string const & value ) const;
		IOperand const * createInt32( std::string const & value ) const;
		IOperand const * createFloat( std::string const & value ) const;
		IOperand const * createDouble( std::string const & value ) const;

};

#endif
