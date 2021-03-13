#include <iostream>

void rotate(int &num1, int &num2, int &num3){
	int tmp;
	tmp = num1;
	num1 = num2;
	num2 = num3;
	num3 = tmp;	
}

void doNothing(int num1, int num2, int num3){
	int tmp;
	tmp = num1;
	num1 = num2;
	num2 = num3;
	num3 = tmp;	
}


int main(int argc, char **argv){
	
	int num1, num2, num3;
	std::cout << "Enter number 1: " << std::flush;
	std::cin >> num1;
		
	std::cout << "Enter number 2: " << std::flush;
	std::cin >> num2;
	
	std::cout << "Enter number 3: " << std::flush;
	std::cin >> num3;

	int &ref1 = num1, &ref2 = num2, &ref3 = num3;
	
	rotate(num1, num2, num3);
	std::cout << "num1: " << num1 << std::endl;
	std::cout << "num2: " << num2 << std::endl;
	std::cout << "num3: " << num3 << std::endl;
	
	std::cout << "plz1: " << &num1 << std::endl;
	std::cout << "plz2: " << &num2 << std::endl;
	std::cout << "plz3: " << &num3 << std::endl;

	rotate(ref1, ref2, ref3);
	
	std::cout << "num1: " << num1 << std::endl;
	std::cout << "num2: " << num2 << std::endl;
	std::cout << "num3: " << num3 << std::endl;
	
	std::cout << "plz1: " << &num1 << std::endl;
	std::cout << "plz2: " << &num2 << std::endl;
	std::cout << "plz3: " << &num3 << std::endl;

	return 0;
}
