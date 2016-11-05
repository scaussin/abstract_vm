#include "Lexer.hpp"
#include "AbstractException.hpp"

Lexer::Lexer()
{
}

Lexer::Lexer(std::vector<std::string> data, std::string endInstruct) : _data(data), _endInstruct(endInstruct)
{
	initMatchVector();
	vectorToToken(data);
	try {
		identifyTokens(_tokens);
	}
	catch(std::exception const& e) {
		std::cerr << "ERROR" << std::endl;
	}
}

Lexer::Lexer(Lexer const &rhs)
{
	*this = rhs;
}

Lexer::~Lexer()
{
}

void Lexer::initMatchVector()
{
	_matchInstr.push_back(sMatchInstr(std::regex("^push$"), InstrPush));
	_matchInstr.push_back(sMatchInstr(std::regex("^pop$"), InstrPop));
	_matchInstr.push_back(sMatchInstr(std::regex("^dump$"), InstrDump));
	_matchInstr.push_back(sMatchInstr(std::regex("^assert$"), InstrAssert));
	_matchInstr.push_back(sMatchInstr(std::regex("^add$"), InstrAdd));
	_matchInstr.push_back(sMatchInstr(std::regex("^sub$"), InstrSub));
	_matchInstr.push_back(sMatchInstr(std::regex("^mul$"), InstrMul));
	_matchInstr.push_back(sMatchInstr(std::regex("^div$"), InstrDiv));
	_matchInstr.push_back(sMatchInstr(std::regex("^mod$"), InstrMod));
	_matchInstr.push_back(sMatchInstr(std::regex("^print$"), InstrPrint));
	_matchInstr.push_back(sMatchInstr(std::regex("^exit$"), InstrExit));

	_matchValue.push_back(sMatchValue(std::regex("^Int8\\(-?[0-9]+\\)$"), ValueInt8));
	_matchValue.push_back(sMatchValue(std::regex("^Int16\\(-?[0-9]+\\)$"), ValueInt16));
	_matchValue.push_back(sMatchValue(std::regex("^Int32\\(-?[0-9]+\\)$"), ValueInt32));
	_matchValue.push_back(sMatchValue(std::regex("^Float\\(-?\\d+\\.{1}\\d+\\)$"), ValueFloat));
	_matchValue.push_back(sMatchValue(std::regex("^Double\\(-?\\d+\\.{1}\\d+\\)$"), ValueDouble));	
}

Lexer &Lexer::operator=(Lexer const &rhs)
{
	_data = rhs._data;
	_tokens = rhs._tokens;
	_endInstruct = rhs._endInstruct;
	_matchInstr = rhs._matchInstr;
	_matchValue = rhs._matchValue;
	return (*this);
}

void Lexer::vectorToToken(std::vector<std::string> data)
{
	tToken *newToken = NULL;
	tToken *tmpDown = NULL;
	tToken *tmpLeft;
	int line = (int)data.size();

	for (std::vector<std::string>::reverse_iterator i = data.rbegin(); i != data.rend(); ++i)
	{
		tmpLeft = NULL;
		std::istringstream stream(*i);
		std::string strData;
		while (std::getline(stream, strData, ' '))
		{
			if (strData != "")
			{
				newToken = (tToken *)malloc(sizeof(tToken));
				newToken->type = err;
				newToken->valueType = ValueNone;
				newToken->instrType = InstrNone;
				newToken->data = strData;
				newToken->line = line;
				newToken->down = tmpDown;
				newToken->left = tmpLeft;
				newToken->right = NULL;
				if (tmpLeft)
					tmpLeft->right = newToken;
				tmpLeft = newToken;
			}
		}
		while(newToken && newToken->left)
		{
			newToken = newToken->left;
		}
		tmpDown = newToken;
		line--;
	}
	_tokens = newToken;
}

void Lexer::identifyTokens(tToken *token)
{
	for (std::vector<tMatchInstr>::iterator i = _matchInstr.begin(); i != _matchInstr.end(); ++i)
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
			throw(AbstractException(std::to_string(token->line)));
	}
	catch(std::exception const& e)
	{
		std::cerr << "lexer error at line: " << e.what() << std::endl;
		if (token->right)
			identifyTokens(token->right);
		else if(token->down)
			identifyTokens(token->down);
		throw;
	}
 
	//std::cout << token->line << token->data << std::endl << "    [type: " << token->type << " value: " << token->valueType << " instr: " << token->instrType << "]"<<std::endl;
	if (token->right)
		identifyTokens(token->right);
	else if(token->down)
		identifyTokens(token->down);
}
















