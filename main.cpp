#include "Controller.hpp"

int	main(int ac, char **av)
{
	Controller *controller;
	std::ifstream *in;
	if (ac == 2)
	{
		in = new std::ifstream();
		in->open(av[1]);
		controller = new Controller(in, true);
	}
	else if (ac == 1)
		controller = new Controller(&std::cin, false);
	else
		std::cout << "usage: ./abstract_vm <file>" << std::endl;
	delete controller;
	return (0);
}