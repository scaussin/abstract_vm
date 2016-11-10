#ifndef VM_HPP
# define VM_HPP

extern Factory iOperandFactory;

class Vm {

	public :
		Vm();
		Vm(tToken *);
		Vm(Vm const &);
		Vm &operator=(Vm const &rhs);
		~Vm();
		tToken *_tokens;
		std::deque<IOperand const *> _stack;
		void (Vm::*_tabInstr[30])(tToken *);
		std::map<eValueType, eOperandType> _valueTypeToOperandType;

	private :
		void execute(tToken *);
		void instrPush(tToken *);
		void instrAdd(tToken *);
		void instrExit(tToken *);
};

#endif