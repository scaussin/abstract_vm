#ifndef ABSTRACTEXCEPTION_HPP
# define ABSTRACTEXCEPTION_HPP

class AbstractException: public std::runtime_error{

	public :
		AbstractException &operator=(AbstractException const &rhs);
		explicit AbstractException (const std::string& what_arg);
		~AbstractException() throw();
		const char* what() const throw();
		std::string _msg;

	private :
};

#endif
