#include "Parser.hpp"

Parser::Parser()
{
}

Parser::Parser(tToken *tokens) : _tokens(tokens)
{

}

Parser::Parser(Parser const &rhs)
{
	*this = rhs;
}

Parser::~Parser()
{
}

Parser &Parser::operator=(Parser const &rhs)
{
	_tokens = rhs._tokens;
	return (*this);
}

void Parser::initCheckVector()
{
	_checkInstr.push_back(sCheckValue(ValueInt8, &Parser::checkInt8));
}

void Parser::checkInt8(tToken *token)
{
	token = token + 1 - 1;
}

void Parser::checkTokens(tToken *token)
{
	/*for (std::vector<tMatchInstr>::iterator i = _matchInstr.begin(); i != _matchInstr.end(); ++i)
	{
		if (std::regex_match(token->data, i->regex))
		{
			token->type = instr;
			token->instrType = i->type;
		}
	}
	for (std::vector<tMatchValue>::iterator i = _matchValue.begin(); i != _matchValue.end(); ++i)
	{
		if (std::regex_match(token->data, i->regex))
		{
			token->type = val;
			token->valueType = i->type;
		}
	}
	try
	{
		if (token->type == err)
			throw(AbstractException("line: " + std::to_string(token->line) + " \033[31mError:\033[m Unknown instruction\n\t" + token->data));
	}
	catch(std::exception const& e)
	{
		std::cerr << e.what() << std::endl;
		if (token->right)
			identifyTokens(token->right);
		else if(token->down)
			identifyTokens(token->down);
		throw;
	}*/
	//std::cout << token->line << token->data << std::endl << "    [type: " << token->type << " value: " << token->valueType << " instr: " << token->instrType << "]"<<std::endl;
	if (token->right)
		checkTokens(token->right);
	else if(token->down)
		checkTokens(token->down);
}

