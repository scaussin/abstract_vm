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
	/*_tabInstr[InstrPop] = &Vm::instrPop;
	_tabInstr[InstrDump] = &Vm::instrDump;
	_tabInstr[InstrAssert] = &Vm::instrAssert;
	_tabInstr[InstrPrint] = &Vm::instrPrint;*/
	try
	{
		execute(_tokens);
	}
	catch(std::exception const& e)
	{
		std::cerr << e.what() << std::endl;
		throw;
	}
	IOperand const * item = _stack.front();
	(void)item;
	/*TOperand  const *ee = dynamic_cast<TOperand const *>(item);
	std::cout << ee->_value << std::endl;*/
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
	IOperand const *res = (*_stack[0] - *_stack[1]);
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
	IOperand const *res = (*_stack[0] / *_stack[1]);
	_stack.pop_front();
	_stack.pop_front();
	_stack.push_front(res);
}

void Vm::instrMod(tToken *token)
{
	checkArithmeticInstr(token);

 	TOperand<int8_t> const & divider = dynamic_cast<TOperand<int8_t> const &>(*_stack[1]);
 	if (divider._value == 0)
 		throw(AbstractException("line: " + std::to_string(token->line) + " \033[31mError run time:\033[m Division by zero\n\t" + token->data));
	IOperand const *res = (*_stack[0] % *_stack[1]);
	_stack.pop_front();
	_stack.pop_front();
	_stack.push_front(res);
}

void Vm::checkArithmeticInstr(tToken *token)
{
	if (_stack.size() < 2)
	{
		throw(AbstractException("line: " + std::to_string(token->line) + " \033[31mError run time:\033[m The stack is composed of strictly less that two values when an arithmetic instruction is executed\n\t" + token->data));
	}
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
