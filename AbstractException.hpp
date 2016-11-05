#ifndef ABSTRACTEXCEPTION_HPP
# define ABSTRACTEXCEPTION_HPP

#include <exception>
#include <string>

class AbstractException: public std::exception {

	public :
		AbstractException();
		AbstractException(std::string) throw();
		AbstractException(AbstractException const &);
		AbstractException &operator=(AbstractException const &rhs);
		~AbstractException() throw();
		const char* what() const throw();
		std::string _msg;

	private :
};

#endif