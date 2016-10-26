#include "Controller.hpp"
#include "Parser.hpp"

Controller::Controller()
{
}

Controller::Controller(std::istream *in, std::string endInstruct) : _in(in), _endInstruct(endInstruct)
{
	Parser parser;
	std::vector<std::string> data;

	data = readIn();
	parser = Parser(data, endInstruct);
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
		data.push_back(s);
		if (_endInstruct == END_STDIN && s == END_STDIN)
			break;
		i++;
	}
	return (data);
}