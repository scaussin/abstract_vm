#ifndef LEXER_HPP
# define LEXER_HPP

typedef struct	sMatchInstr
{
	std::regex regex;
	eInstrType type;
	sMatchInstr(std::regex reg, eInstrType inst) : regex(reg), type(inst)
	{
	}
}				tMatchInstr;

typedef struct	sMatchValue
{
	std::regex regex;
	eValueType type;
	sMatchValue(std::regex reg, eValueType value) : regex(reg), type(value)
	{
	}
}				tMatchValue;


class Lexer {
	public :
		Lexer();
		Lexer(std::vector<std::string>);
		Lexer(Lexer const &);
		Lexer &operator=(Lexer const &rhs);
		~Lexer();
		std::vector<std::string> _data;
		tToken *_tokens;
		std::vector<tMatchInstr> _matchInstr;
		std::vector<tMatchValue> _matchValue;

	private :
		void vectorToToken(std::vector<std::string>);
		void identifyTokens(tToken *token);
		void initMatchVector();
		
};

#endif