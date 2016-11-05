#ifndef PARSER_HPP
# define PARSER_HPP

#include <string>
#include <vector>
#include "Lexer.hpp"
#include "main.hpp"
#include "AbstractException.hpp"



class Parser {

	

	public :
		Parser();
		Parser(tToken *);
		Parser(Parser const &);
		Parser &operator=(Parser const &rhs);
		~Parser();
		void checkTokens(tToken *);
		void initCheckVector();
		void checkInt8(tToken *);

		tToken *_tokens;

		typedef struct	sCheckValue
		{
			eValueType type;
			void (Parser::*func)(tToken *);
			sCheckValue(eValueType type, void (Parser::*funct)(tToken *)) :type(type), func(funct)
			{
			}
		}				tCheckValue;

		std::vector<tCheckValue> _checkInstr;
	private :
};



#endif