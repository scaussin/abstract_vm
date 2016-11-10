#ifndef MAIN_HPP
# define MAIN_HPP

#define END_STDIN ";;"

#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <sstream>
#include <regex>
#include <iomanip>
#include <fstream>
#include <exception>
#include <map>

#include "AbstractException.hpp"
#include "Lexer.hpp"
#include "Factory.hpp"
#include "Parser.hpp"
#include "TOperand.hpp"
#include "IOperand.hpp"

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
