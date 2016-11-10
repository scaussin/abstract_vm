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
#include <deque>


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

/*class AbstractException;
class Lexer;
class Factory;
class Parser;
class TOperand;
class IOperand;*/

#include "Controller.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "AbstractException.hpp"
#include "IOperand.hpp"
#include "Factory.hpp"
#include "TOperand.hpp"
#include "Vm.hpp"


#endif
