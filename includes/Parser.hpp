#ifndef PARSER_HPP
# define PARSER_HPP

class Parser {
	public :
		Parser();
		Parser(tToken *);
		Parser(Parser const &);
		Parser &operator=(Parser const &rhs);
		~Parser();
		tToken *_tokens;

		typedef struct	sCheckValue
		{
			eValueType type;
			void (Parser::*func)(tToken *);
			sCheckValue(eValueType type, void (Parser::*funct)(tToken *)) :type(type), func(funct)
			{
			}
		}				tCheckValue;

		typedef struct	sCheckInstr
		{
			eInstrType type;
			void (Parser::*func)(tToken *);
			sCheckInstr(eInstrType type, void (Parser::*funct)(tToken *)) :type(type), func(funct)
			{
			}
		}				tCheckInstr;

		std::vector<tCheckValue> _checkValue;
		std::vector<tCheckInstr> _checkInstr;
	private :
		void checkTokens(tToken *, int *);
		void initCheckVector();

		void checkInt8(tToken *);
		void checkInt16(tToken *);
		void checkInt32(tToken *);
		void checkFloat(tToken *);
		void checkDouble(tToken *);

		void noTokenAtRight(tToken *);
		void noTokenAtLeft(tToken *);
		void instrAtLeft(tToken *token);

		void checkInstrWhithValue(tToken *);
		void checkInstr(tToken *);
		void checkEndInstr(tToken *);
};



#endif