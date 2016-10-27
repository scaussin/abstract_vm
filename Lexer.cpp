#include "lexer.hpp"

Lexer::Lexer()
{
}

Lexer::Lexer(std::vector<std::string> data, std::string endInstruct) : _data(data), _endInstruct(endInstruct)
{
	vectorToToken(data);
	identifyTokens(_tokens);
}

Lexer::Lexer(Lexer const &rhs)
{
	*this = rhs;
}

Lexer::~Lexer()
{
}

Lexer &Lexer::operator=(Lexer const &rhs)
{
	_data = rhs._data;
	_tokens = rhs._tokens;
	_endInstruct = rhs._endInstruct;
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
		while(newToken->left)
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
	std::cout << token->data << std::endl;
	if (token->right)
		identifyTokens(token->right);
	else if(token->down)
		identifyTokens(token->down);
}
















