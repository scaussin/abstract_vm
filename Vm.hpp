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
		void instrPop(tToken *);
		void instrDump(tToken *);
		void instrDumpR(tToken *);
		void instrExit(tToken *);
		void instrAssert(tToken *);
		void instrPrint(tToken *);
		void instrPrintAll(tToken *);
		void instrPrintAllR(tToken *);

		void instrAdd(tToken *);
		void instrSub(tToken *);
		void instrMul(tToken *);
		void instrDiv(tToken *);
		void instrMod(tToken *);

		void checkArithmeticInstr(tToken *);
        void checkDivisionByZero(tToken *);
};

#endif
