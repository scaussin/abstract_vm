#include "Parser.hpp"

Parser::Parser()
{}

Parser::Parser(tToken *tokens, std::string endInst) : _tokens(tokens), _endInst(endInst)
{
	int countInstrEnd = 0;
	checkTokens(tokens, &countInstrEnd);
	if (countInstrEnd == 0)
		throw(AbstractException("\033[31mError parser:\033[m 'end' instruction is required"));
	else if (countInstrEnd > 1)
		throw(AbstractException("\033[31mError parser:\033[m Multiple 'end' instruction"));
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
	if (token->data != _endInst)
	{
		token->type = err;
		throw(AbstractException("line: " + std::to_string(token->line) + " \033[31mError parser:\033[m Bad 'end' instruction\n\t" + token->data));
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
	/*try
	{
		std::size_t lastChar;
		int8_t result = std::stoi(str, &lastChar, 10);
		return lastChar == str.size();
	}
	catch (std::invalid_argument&)
	{
		return false;
	}
	catch (std::out_of_range&)
	{
		return false;
	}*/
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
	try
	{
		if (token->type == instr)
		{
			for (std::vector<tCheckInstr>::iterator i = _checkInstr.begin(); i != _checkInstr.end(); ++i)
			{
				if (token->instrType == i->type)
				{
					i->func(token);
					if (token->instrType == InstrExit)
						*countInstrEnd++;
				}
			}
		}
		if (token->type == val)
		{
			for (std::vector<tCheckValue>::iterator i = _checkValue.begin(); i != _checkValue.end(); ++i)
			{
				if (token->valueType == i->type)
				{
					i->func(token);
				}
			}
		}
	}
	catch(std::exception const& e)
	{
		std::cerr << e.what() << std::endl;
		if (token->right)
			identifyTokens(token->right);
		else if(token->down)
			identifyTokens(token->down);
		throw;
	}
	if (token->right)
		checkTokens(token->right);
	else if(token->down)
		checkTokens(token->down);
	//std::cout << token->line << token->data << std::endl << "    [type: " << token->type << " value: " << token->valueType << " instr: " << token->instrType << "]"<<std::endl;
}

