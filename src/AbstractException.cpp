#include "main.hpp"


AbstractException::AbstractException(const std::string & what_arg) : std::runtime_error(what_arg)
{
	_msg = what_arg;
}

const char* AbstractException::what() const throw()
{
	return (_msg.c_str());
}

AbstractException::~AbstractException() throw()
{
}

AbstractException &AbstractException::operator=(AbstractException const &rhs)
{
	_msg = rhs._msg;
	return (*this);
}
