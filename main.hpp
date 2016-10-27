#ifndef MAIN_HPP
# define MAIN_HPP

enum eOperandType
{
    Int8,
    Int16,
    Int32,
    Float,
    Double
};

enum eTokenType
{
    err,
    instr,
    val,
    com
};

typedef struct	eToken
{
	std::string data;
	int line;
    eTokenType type;
	struct eToken *down;
	struct eToken *right;
	struct eToken *left;
}				tToken;


#endif
