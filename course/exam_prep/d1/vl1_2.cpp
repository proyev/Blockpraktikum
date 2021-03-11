#include <iostream>

int main(int argc, char **argv){
	std::cout << "Parameter 1: " << argv[0] << std::endl;
	std::cout << "Parameter 2: " << argv[1] << std::endl;
	std::cout << "Parameter " << argc << ": " << argv[argc-1] << std::endl;
	return 0;
}
