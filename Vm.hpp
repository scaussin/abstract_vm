#ifndef VM_HPP
# define VM_HPP

#include <string>
#include <vector>
#include "AbstractException.hpp"
#include "main.hpp"

class Vm {

	public :
		Vm();
		Vm(tToken *);
		Vm(Vm const &);
		Vm &operator=(Vm const &rhs);
		~Vm();
		tToken *_tokens;

	private :

};

#endif