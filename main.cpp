#include "Controller.hpp"

int	main(int ac, char **av)
{
	Controller controller;
	std::ifstream *in;
	if (ac == 2)
	{
		in = new std::ifstream();
		in->open(av[1]);
		if (in->is_open())
  		{
			controller = Controller(in, "exit");
			in->close();
		}
		else
			std::cout << "[ERROR] open file" << std::endl;
	}
	else if (ac == 1)
		controller = Controller(&std::cin, ";;");
	else
		std::cout << "usage: ./abstract_vm <file>" << std::endl;
	return (0);
}