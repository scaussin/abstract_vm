#ifndef LEXER_HPP
# define LEXER_HPP

#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <sstream>
#include "main.hpp"

class Lexer {

	public :
		Lexer();
		Lexer(std::vector<std::string>, std::string);
		Lexer(Lexer const &);
		Lexer &operator=(Lexer const &rhs);
		~Lexer();
		std::vector<std::string> _data;
		std::string _endInstruct;
		tToken *_tokens;
	private :
		void vectorToToken(std::vector<std::string>);
        void identifyTokens(tToken *token);
		
};

#endif