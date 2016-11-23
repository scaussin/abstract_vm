#include "main.hpp"

Factory iOperandFactory;

Controller::Controller()
{
}

Controller::Controller(std::istream *in, std::string endInstruct) : _in(in), _endInstruct(endInstruct)
{
	Lexer lexer;
	Parser parser;
	Vm vm;
	std::vector<std::string> data;

	data = readIn();
	try {
		lexer = Lexer(data);
		parser = Parser(lexer._tokens);
		vm = Vm(parser._tokens);
	}
	catch(std::exception const& e) {
		std::cerr << "AbstractVM stopped : Error" << std::endl;
	}
}

Controller::Controller(Controller const &rhs)
{
	*this = rhs;
}

Controller::~Controller()
{
}

Controller &Controller::operator=(Controller const &rhs)
{
	_in = rhs._in;
	_endInstruct = rhs._endInstruct;
	return (*this);
}

std::vector<std::string> Controller::readIn()
{
	std::string s;
	int i = 0;
	std::vector<std::string> data;

	while (getline(*_in, s, '\n'))
	{
		std::replace(s.begin(), s.end(), '\t', ' ');
		if (_endInstruct == END_STDIN && s.find(END_STDIN) != std::string::npos)
			break;
		data.push_back(s);
		if (data.back().find(';') != std::string::npos)
			data.back().resize(data.back().find(';'));
		i++;
	}
	return (data);
}
