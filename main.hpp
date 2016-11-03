#ifndef MAIN_HPP
# define MAIN_HPP

enum eTokenType
{
	err,
	instr,
	val
};

enum eValueType
{
	ValueNone,
	ValueInt8,
	ValueInt16,
	ValueInt32,
	ValueFloat,
	ValueDouble
};

enum eInstrType
{
	InstrNone,
	InstrPush,
	InstrPop,
	InstrDump,
	InstrAssert,
	InstrAdd,
	InstrSub,
	InstrMul,
	InstrDiv,
	InstrMod,
	InstrPrint,
	InstrExit
};

typedef struct	eToken
{
	std::string data;
	int line;
	eTokenType type;
	eValueType valueType;
	eInstrType instrType;
	struct eToken *down;
	struct eToken *right;
	struct eToken *left;
}				tToken;

#endif
