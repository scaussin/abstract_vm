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

	//_tabInstr[InstrNone] = &Vm::instrNone;
	_tabInstr[InstrPush] = &Vm::instrPush;
	_tabInstr[InstrAdd] = &Vm::instrAdd;
	_tabInstr[InstrExit] = &Vm::instrExit;
	/*_tabInstr[InstrPop] = &Vm::instrPop;
	_tabInstr[InstrDump] = &Vm::instrDump;
	_tabInstr[InstrAssert] = &Vm::instrAssert;
	_tabInstr[InstrSub] = &Vm::instrSub;
	_tabInstr[InstrMul] = &Vm::instrMul;
	_tabInstr[InstrDiv] = &Vm::instrDiv;
	_tabInstr[InstrMod] = &Vm::instrMod;
	_tabInstr[InstrPrint] = &Vm::instrPrint;*/
	execute(_tokens);
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
	(void)token;
	IOperand const *res = (*_stack[0] + *_stack[1]);
	_stack.pop_front();
	_stack.pop_front();

	_stack.push_front(res);
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
