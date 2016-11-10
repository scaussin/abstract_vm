#ifndef CONTROLLER_HPP
# define CONTROLLER_HPP

#include "main.hpp"

class Controller {

	public :
		Controller();
		Controller(std::istream *, std::string);
		Controller(Controller const &);
		Controller &operator=(Controller const &rhs);
		~Controller();
		std::istream *_in;
		std::string _endInstruct;

	private :
		std::vector<std::string> readIn();
};

#endif