#include <iostream>
#include "vl1_3.hpp"


int main(int argc, char **argv){
	
	int num1 = getInput();
	int num2 = getInput();
	
	std::cout << "Sum: " << add(num1, num2) << std::endl;

	return 0;
}
