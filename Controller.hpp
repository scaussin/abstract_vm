#ifndef CONTROLLER_HPP
# define CONTROLLER_HPP

#include <string>
#include <iostream>
#include <fstream>

class Controller {

	public :
		Controller();
		Controller(std::istream *, bool);
		Controller(Controller const &);
		Controller &operator=(Controller const &rhs);
		~Controller();
		std::istream *_in;
		bool _readInFile;
	private :
		void readIn();
};

#endif