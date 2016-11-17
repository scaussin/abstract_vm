#include "main.hpp"

Vm::Vm()
{
}

Vm::Vm(tToken *tokens) : _tokens(tokens)
{
	_valueTypeToOperandType[ValueInt8] = eInt8;
	_valueTypeToOperandType[ValueInt16] = eInt16;
	_valueTypeToOperandType[ValueInt32] = eInt32;
	_valueTypeToOperandType[ValueFloat] = eFloat;
	_valueTypeToOperandType[ValueDouble] = eDouble;

	_tabInstr[InstrNone] = &Vm::instrExit;
	_tabInstr[InstrPush] = &Vm::instrPush;

	_tabInstr[InstrAdd] = &Vm::instrAdd;
	_tabInstr[InstrSub] = &Vm::instrSub;
	_tabInstr[InstrMul] = &Vm::instrMul;
	_tabInstr[InstrDiv] = &Vm::instrDiv;
	_tabInstr[InstrMod] = &Vm::instrMod;

	_tabInstr[InstrExit] = &Vm::instrExit;
	_tabInstr[InstrPop] = &Vm::instrPop;
	_tabInstr[InstrDump] = &Vm::instrDump;
	_tabInstr[InstrAssert] = &Vm::instrAssert;
	_tabInstr[InstrPrint] = &Vm::instrPrint;
	try
	{
		execute(_tokens);
	}
	catch(std::exception const& e)
	{
		std::cerr << e.what() << std::endl;
		throw;
	}
}

Vm::Vm(Vm const &rhs)
{
	*this = rhs;
}

Vm::~Vm()
{
}

Vm &Vm::operator=(Vm const &rhs)
{
	_tokens = rhs._tokens;
	_stack = rhs._stack;
	return (*this);
}

void Vm::instrPush(tToken *token)
{
	IOperand const *res = iOperandFactory.createOperand(_valueTypeToOperandType[token->right->valueType], token->right->data);
	_stack.push_front(res);
}

void Vm::instrAdd(tToken *token)
{
	checkArithmeticInstr(token);
	IOperand const *res = (*_stack[0] + *_stack[1]);
	_stack.pop_front();
	_stack.pop_front();
	_stack.push_front(res);
}

void Vm::instrSub(tToken *token)
{
	checkArithmeticInstr(token);
	IOperand const *res = (*_stack[1] - *_stack[0]);
	_stack.pop_front();
	_stack.pop_front();
	_stack.push_front(res);
}

void Vm::instrMul(tToken *token)
{
	checkArithmeticInstr(token);
	IOperand const *res = (*_stack[0] * *_stack[1]);
	_stack.pop_front();
	_stack.pop_front();
	_stack.push_front(res);
}

void Vm::instrDiv(tToken *token)
{
	checkArithmeticInstr(token);
	checkDivisionByZero(token);
	IOperand const *res = (*_stack[1] / *_stack[0]);
	_stack.pop_front();
	_stack.pop_front();
	_stack.push_front(res);
}

void Vm::instrMod(tToken *token)
{
	checkArithmeticInstr(token);
	checkDivisionByZero(token);

	IOperand const *res = (*_stack[1] % *_stack[0]);
	_stack.pop_front();
	_stack.pop_front();
	_stack.push_front(res);
}

void Vm::instrPop(tToken *token)
{
	if (_stack.size() == 0)
		throw(AbstractException("line: " + std::to_string(token->line) + " \033[31mError run time:\033[m Instruction pop on an empty stack\n\t" + token->data));
	_stack.pop_front();
}

void Vm::instrPrint(tToken *token)
{
	if (_stack.size() < 1)
		throw(AbstractException("line: " + std::to_string(token->line) + " \033[31mError run time:\033[m Instruction print on an empty stack\n\t" + token->data));
	if (eInt8 == _stack[0]->getType())
	{
		TOperand<int8_t> const & operand = dynamic_cast<TOperand<int8_t> const &>(*_stack[0]);
		std::cout << operand._value << std::endl;
	}
	else
		throw(AbstractException("line: " + std::to_string(token->line) + " \033[31mError run time:\033[m Instruction print on a wrong type (int8 required)\n\t" + token->data));
}

void Vm::instrAssert(tToken *token)
{
	if (_stack.size() == 0)
		throw(AbstractException("line: " + std::to_string(token->line) + " \033[31mError run time:\033[m Instruction assert on an empty stack\n\t" + token->data + " " + token->right->data));
	try {
		TOperand<int8_t> const & operand = dynamic_cast<TOperand<int8_t> const &>(*_stack[0]);
		if (_valueTypeToOperandType[token->right->valueType] == operand._type)
		{
			IOperand const *res = iOperandFactory.createOperand(_valueTypeToOperandType[token->right->valueType], token->right->data);
			TOperand<int8_t> const & assert = dynamic_cast<TOperand<int8_t> const &>(*res);
			if (operand._value != assert._value)
				throw(AbstractException("line: " + std::to_string(token->line) + " \033[31mError run time:\033[m Instruction assert is not true (different value)\n\t" + token->data + " " + token->right->data));
		}
		else
			throw(AbstractException("line: " + std::to_string(token->line) + " \033[31mError run time:\033[m Instruction assert is not true (different type)\n\t" + token->data + " " + token->right->data));
	}
	catch(const std::bad_cast& e) {}
	try {
		TOperand<int16_t> const & operand = dynamic_cast<TOperand<int16_t> const &>(*_stack[0]);
		if (_valueTypeToOperandType[token->right->valueType] == operand._type)
		{
			IOperand const *res = iOperandFactory.createOperand(_valueTypeToOperandType[token->right->valueType], token->right->data);
			TOperand<int16_t> const & assert = dynamic_cast<TOperand<int16_t> const &>(*res);
			if (operand._value != assert._value)
				throw(AbstractException("line: " + std::to_string(token->line) + " \033[31mError run time:\033[m Instruction assert is not true (different value)\n\t" + token->data + " " + token->right->data));
		}
		else
			throw(AbstractException("line: " + std::to_string(token->line) + " \033[31mError run time:\033[m Instruction assert is not true (different type)\n\t" + token->data + " " + token->right->data));
	}
	catch(const std::bad_cast& e) {}
	try {
		TOperand<int32_t> const & operand = dynamic_cast<TOperand<int32_t> const &>(*_stack[0]);
		if (_valueTypeToOperandType[token->right->valueType] == operand._type)
		{
			IOperand const *res = iOperandFactory.createOperand(_valueTypeToOperandType[token->right->valueType], token->right->data);
			TOperand<int32_t> const & assert = dynamic_cast<TOperand<int32_t> const &>(*res);
			if (operand._value != assert._value)
				throw(AbstractException("line: " + std::to_string(token->line) + " \033[31mError run time:\033[m Instruction assert is not true (different value)\n\t" + token->data + " " + token->right->data));
		}
		else
			throw(AbstractException("line: " + std::to_string(token->line) + " \033[31mError run time:\033[m Instruction assert is not true (different type)\n\t" + token->data + " " + token->right->data));
	}
	catch(const std::bad_cast& e) {}
	try {
		TOperand<float> const & operand = dynamic_cast<TOperand<float> const &>(*_stack[0]);
		if (_valueTypeToOperandType[token->right->valueType] == operand._type)
		{
			IOperand const *res = iOperandFactory.createOperand(_valueTypeToOperandType[token->right->valueType], token->right->data);
			TOperand<float> const & assert = dynamic_cast<TOperand<float> const &>(*res);
			if (operand._value != assert._value)
				throw(AbstractException("line: " + std::to_string(token->line) + " \033[31mError run time:\033[m Instruction assert is not true (different value)\n\t" + token->data + " " + token->right->data));
		}
		else
			throw(AbstractException("line: " + std::to_string(token->line) + " \033[31mError run time:\033[m Instruction assert is not true (different type)\n\t" + token->data + " " + token->right->data));
	}
	catch(const std::bad_cast& e) {}
	try {
		TOperand<double> const & operand = dynamic_cast<TOperand<double> const &>(*_stack[0]);
		if (_valueTypeToOperandType[token->right->valueType] == operand._type)
		{
			IOperand const *res = iOperandFactory.createOperand(_valueTypeToOperandType[token->right->valueType], token->right->data);
			TOperand<double> const & assert = dynamic_cast<TOperand<double> const &>(*res);
			if (operand._value != assert._value)
				throw(AbstractException("line: " + std::to_string(token->line) + " \033[31mError run time:\033[m Instruction assert is not true (different value)\n\t" + token->data + " " + token->right->data));
		}
		else
			throw(AbstractException("line: " + std::to_string(token->line) + " \033[31mError run time:\033[m Instruction assert is not true (different type)\n\t" + token->data + " " + token->right->data));
	}
	catch(const std::bad_cast& e) {}
}


void Vm::instrDump(tToken *token)
{
	(void)token;
	size_t i = 0;
	while (i < _stack.size())
	{
		try {
			TOperand<int8_t> const & operand = dynamic_cast<TOperand<int8_t> const &>(*_stack[i]);
			std::cout << (int)operand._value << std::endl;
		}
		catch(const std::bad_cast& e) {}
		try {
			TOperand<int16_t> const & operand = dynamic_cast<TOperand<int16_t> const &>(*_stack[i]);
			std::cout << operand._value << std::endl;
		}
		catch(const std::bad_cast& e) {}
		try {
			TOperand<int32_t> const & operand = dynamic_cast<TOperand<int32_t> const &>(*_stack[i]);
			std::cout << operand._value << std::endl;
		}
		catch(const std::bad_cast& e) {}
		try {
			TOperand<float> const & operand = dynamic_cast<TOperand<float> const &>(*_stack[i]);
			std::cout << operand._value << std::endl;
		}
		catch(const std::bad_cast& e) {}
		try {
			TOperand<double> const & operand = dynamic_cast<TOperand<double> const &>(*_stack[i]);
			std::cout << operand._value << std::endl;
		}
		catch(const std::bad_cast& e) {}
		i++;
	}
}

void Vm::checkDivisionByZero(tToken *token)
{
	try {
		TOperand<int8_t> const & divider = dynamic_cast<TOperand<int8_t> const &>(*_stack[1]);
		if (divider._value == 0)
	 		throw(AbstractException("line: " + std::to_string(token->line) + " \033[31mError run time:\033[m Division by zero\n\t" + token->data));
	}
	catch(const std::bad_cast& e) {}
	try {
		TOperand<int16_t> const & divider = dynamic_cast<TOperand<int16_t> const &>(*_stack[1]);
		if (divider._value == 0)
	 		throw(AbstractException("line: " + std::to_string(token->line) + " \033[31mError run time:\033[m Division by zero\n\t" + token->data));
	}
	catch(const std::bad_cast& e) {}
	try {
		TOperand<int32_t> const & divider = dynamic_cast<TOperand<int32_t> const &>(*_stack[1]);
		if (divider._value == 0)
	 		throw(AbstractException("line: " + std::to_string(token->line) + " \033[31mError run time:\033[m Division by zero\n\t" + token->data));
	}
	catch(const std::bad_cast& e) {}
	try {
		TOperand<float> const & divider = dynamic_cast<TOperand<float> const &>(*_stack[1]);
		if (divider._value == 0)
	 		throw(AbstractException("line: " + std::to_string(token->line) + " \033[31mError run time:\033[m Division by zero\n\t" + token->data));
	}
	catch(const std::bad_cast& e) {}
	try {
		TOperand<double> const & divider = dynamic_cast<TOperand<double> const &>(*_stack[1]);
		if (divider._value == 0)
	 		throw(AbstractException("line: " + std::to_string(token->line) + " \033[31mError run time:\033[m Division by zero\n\t" + token->data));
	}
	catch(const std::bad_cast& e) {}
}

void Vm::checkArithmeticInstr(tToken *token)
{
	if (_stack.size() < 2)
		throw(AbstractException("line: " + std::to_string(token->line) + " \033[31mError run time:\033[m The stack is composed of strictly less that two values when an arithmetic instruction is executed\n\t" + token->data));
}

void Vm::instrExit(tToken *token)
{
	(void)token;
}

void Vm::execute(tToken *token)
{
	// std::cout << token->line << token->data << std::endl << "    [type: " << token->type << " value: " << token->valueType << " instr: " << token->instrType << "]"<<std::endl;
	(this->*_tabInstr[token->instrType])(token);
	if (token->down)
		execute(token->down);
}
