#include "Controller.hpp"

Controller::Controller()
{

}

Controller::Controller(std::istream *in, bool readInFile) : _in(in), _readInFile(readInFile)
{
	readIn();
}

Controller::Controller(Controller const &rhs)
{
	*this = rhs;
}

Controller::~Controller()
{
	if (_in && _readInFile == true)
		((std::ifstream *)(_in))->close();
}

Controller &Controller::operator=(Controller const &rhs)
{
	_in = rhs._in;
	return (*this);
}

void Controller::readIn()
{
	std::string s;
	*_in >> s;
	std::cout << "value: " << s << std::endl;
	*_in >> s;
	std::cout << "value: " << s << std::endl;
}