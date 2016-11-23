#include "main.hpp"

Parser::Parser()
{}

Parser::Parser(tToken *tokens) : _tokens(tokens)
{
	int countInstrEnd = 0;

	initCheckVector();
	checkTokens(tokens, &countInstrEnd);
	try {
		if (countInstrEnd == 0)
			throw(AbstractException("\033[31mError parser:\033[m Instruction exit is required"));
		else if (countInstrEnd > 1)
			throw(AbstractException("\033[31mError parser:\033[m Multiple exit instruction"));
	}
	catch(std::exception const& e)
	{
		std::cerr << e.what() << std::endl;
		throw;
	}
}

Parser::Parser(Parser const &rhs)
{
	*this = rhs;
}

Parser::~Parser()
{}

Parser &Parser::operator=(Parser const &rhs)
{
	_tokens = rhs._tokens;
	_checkValue = rhs._checkValue;
	_checkInstr = rhs._checkInstr;
	return (*this);
}

void Parser::initCheckVector()
{
	_checkInstr.push_back(sCheckInstr(InstrPush, &Parser::checkInstrWhithValue));
	_checkInstr.push_back(sCheckInstr(InstrPop, &Parser::checkInstr));
	_checkInstr.push_back(sCheckInstr(InstrDump, &Parser::checkInstr));
	_checkInstr.push_back(sCheckInstr(InstrAssert, &Parser::checkInstrWhithValue));
	_checkInstr.push_back(sCheckInstr(InstrAdd, &Parser::checkInstr));
	_checkInstr.push_back(sCheckInstr(InstrSub, &Parser::checkInstr));
	_checkInstr.push_back(sCheckInstr(InstrMul, &Parser::checkInstr));
	_checkInstr.push_back(sCheckInstr(InstrDiv, &Parser::checkInstr));
	_checkInstr.push_back(sCheckInstr(InstrMod, &Parser::checkInstr));
	_checkInstr.push_back(sCheckInstr(InstrPrint, &Parser::checkInstr));
	_checkInstr.push_back(sCheckInstr(InstrExit, &Parser::checkEndInstr));

	_checkInstr.push_back(sCheckInstr(InstrAddAll, &Parser::checkInstr));
	_checkInstr.push_back(sCheckInstr(InstrMulAll, &Parser::checkInstr));
	_checkInstr.push_back(sCheckInstr(InstrPopAll, &Parser::checkInstr));
	_checkInstr.push_back(sCheckInstr(InstrPrintAll, &Parser::checkInstr));
	_checkInstr.push_back(sCheckInstr(InstrPrintAllR, &Parser::checkInstr));
	_checkInstr.push_back(sCheckInstr(InstrDumpR, &Parser::checkInstr));


	_checkValue.push_back(sCheckValue(ValueInt8, &Parser::checkInt8));
	_checkValue.push_back(sCheckValue(ValueInt16, &Parser::checkInt16));
	_checkValue.push_back(sCheckValue(ValueInt32, &Parser::checkInt32));
	_checkValue.push_back(sCheckValue(ValueFloat, &Parser::checkFloat));
	_checkValue.push_back(sCheckValue(ValueDouble, &Parser::checkDouble));
}

void Parser::checkInstrWhithValue(tToken *token)
{
	if (!token->right || token->right->type != val)
	{
		token->type = err;
		throw(AbstractException("line: " + std::to_string(token->line) + " \033[31mError parser:\033[m Value after this instruction is required\n\t" + token->data));
	}
	noTokenAtLeft(token);
}

void Parser::checkInstr(tToken *token)
{
	noTokenAtLeft(token);
	noTokenAtRight(token);
}

void Parser::checkEndInstr(tToken *token)
{
	checkInstr(token);
	if (token->down)
	{
		token->type = err;
		throw(AbstractException("line: " + std::to_string(token->line) + " \033[31mError parser:\033[m Forbidden instruction or value after 'end' instruction\n\t" + token->data));
	}
}

void Parser::noTokenAtRight(tToken *token)
{
	if (token->right)
	{
		token->type = err;
		throw(AbstractException("line: " + std::to_string(token->line) + " \033[31mError parser:\033[m Forbidden right instruction or value\n\t" + token->data + " " + token->right->data));
	}
}

void Parser::noTokenAtLeft(tToken *token)
{
	if (token->left)
	{
		token->type = err;
		throw(AbstractException("line: " + std::to_string(token->line) + " \033[31mError parser:\033[m Forbidden left instruction or value\n\t" + token->left->data + " " + token->data));
	}
}

void Parser::instrAtLeft(tToken *token)
{
	if (!token->left || token->left->type != instr)
	{
		token->type = err;
		throw(AbstractException("line: " + std::to_string(token->line) + " \033[31mError parser:\033[m instruction is required before value\n\t" + token->data));
	}
}

void Parser::checkInt8(tToken *token)
{
	instrAtLeft(token);
	noTokenAtRight(token);
}

void Parser::checkInt16(tToken *token)
{
	instrAtLeft(token);
	noTokenAtRight(token);
}

void Parser::checkInt32(tToken *token)
{
	instrAtLeft(token);
	noTokenAtRight(token);
}

void Parser::checkFloat(tToken *token)
{
	instrAtLeft(token);
	noTokenAtRight(token);
}

void Parser::checkDouble(tToken *token)
{
	instrAtLeft(token);
	noTokenAtRight(token);
}

void Parser::checkTokens(tToken *token, int *countInstrEnd)
{
	// std::cout << token->line << token->data << std::endl << "    [type: " << token->type << " value: " << token->valueType << " instr: " << token->instrType << "]"<<std::endl;
	try
	{
		if (token->type == instr)
		{
			for (std::vector<tCheckInstr>::iterator i = _checkInstr.begin(); i != _checkInstr.end(); ++i)
			{
				if (token->instrType == i->type)
				{
					(this->*i->func)(token);
					if (token->instrType == InstrExit)
					{
						(*countInstrEnd)++;
					}
				}
			}
		}
		if (token->type == val)
		{
			for (std::vector<tCheckValue>::iterator i = _checkValue.begin(); i != _checkValue.end(); ++i)
			{
				if (token->valueType == i->type)
				{
					(this->*i->func)(token);
				}
			}
		}
	}
	catch(std::exception const& e)
	{
		std::cerr << e.what() << std::endl;
		if (token->right)
			checkTokens(token->right, countInstrEnd);
		else if(token->down)
			checkTokens(token->down, countInstrEnd);
		throw;
	}
	if (token->right)
		checkTokens(token->right, countInstrEnd);
	else if(token->down)
		checkTokens(token->down, countInstrEnd);
}

