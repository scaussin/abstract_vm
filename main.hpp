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

enum eOperandType
{
	eInt8,
	eInt16,
	eInt32,
	eFloat,
	eDouble
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

struct tToken
{
	std::string data;
	int line;
	eTokenType type;
	eValueType valueType;
	eInstrType instrType;
	tToken *down;
	tToken *right;
	tToken *left;
};

#endif
