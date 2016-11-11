#ifndef ABSTRACTEXCEPTION_HPP
# define ABSTRACTEXCEPTION_HPP

class AbstractException: public std::exception{

	public :
		AbstractException();
//    explicit  AbstractException (const std::string& what_arg);
		AbstractException(std::string) throw();
		AbstractException(AbstractException const &);
		AbstractException &operator=(AbstractException const &rhs);
		~AbstractException() throw();
		const char* what() const throw();
		std::string _msg;

	private :
};

#endif
