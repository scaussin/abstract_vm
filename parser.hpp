#ifndef PARSER_HPP
# define PARSER_HPP

#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include "main.hpp"

class Parser {

	public :
		Parser();
		Parser(std::vector<std::string>, std::string);
		Parser(Parser const &);
		Parser &operator=(Parser const &rhs);
		~Parser();
		std::vector<std::string> _data;
		std::string _endInstruct;
		t_token _tokens;
	private :
		void vectorToToken(std::vector<std::string>);
		
};

#endif