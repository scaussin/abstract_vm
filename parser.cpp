#include "parser.hpp"

Parser::Parser()
{
}

Parser::Parser(std::vector<std::string> data, std::string endInstruct) : _data(data), _endInstruct(endInstruct)
{
	vectorToToken(data);
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
	_data = rhs._data;
	_tokens = rhs._tokens;
	_endInstruct = rhs._endInstruct;
	return (*this);
}

void Parser::vectorToToken(std::vector<std::string> data)
{
	/*char *ret;
	char *dup;*/

	for (std::vector<std::string>::const_iterator i = data.begin(); i != data.end(); ++i)
	{
		std::cout << *i << std::endl;
		/*dup = strdup((*i).c_str());
		ret = std::strtok(dup, "\n ");
		while (ret != NULL)
		{
			printf ("%s\n", ret);

			ret = strtok(NULL, "\n ");
		}
		free(dup);*/
	}
}

