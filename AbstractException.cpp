#include "AbstractException.hpp"

AbstractException::AbstractException()
{
}

AbstractException::AbstractException(std::string msg) throw() : _msg(msg)
{
}

const char* AbstractException::what() const throw()
{
	return (_msg.c_str());
}

AbstractException::AbstractException(AbstractException const &rhs)
{
	*this = rhs;
}

AbstractException::~AbstractException() throw()
{
}

AbstractException &AbstractException::operator=(AbstractException const &rhs)
{
	_msg = rhs._msg;
	return (*this);
}
