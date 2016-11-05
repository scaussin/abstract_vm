#include "Controller.hpp"

Controller::Controller()
{
}

Controller::Controller(std::istream *in, std::string endInstruct) : _in(in), _endInstruct(endInstruct)
{
	Lexer lexer;
	Parser parser;
	std::vector<std::string> data;

	data = readIn();
	
	try {
		lexer = Lexer(data, endInstruct);
		parser = Parser(lexer._tokens);
	}
	catch(std::exception const& e) {
		std::cerr << "AbstractVM stopped." << std::endl;
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
		data.push_back(s);
		if (_endInstruct == END_STDIN && s == END_STDIN)
			break;
		if (data.back().find(';') != std::string::npos)
			data.back().resize(data.back().find(';'));
		/*if (data.back() == "")
			data.pop_back();*/
		i++;
	}
	return (data);
}