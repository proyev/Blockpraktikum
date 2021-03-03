#include <iostream>
#include "swap.h"

int main() {
    int num1, num2;
    int *ptr1 = &num1, *ptr2 = &num2;
    std::cout << "Enter num1: " << std::flush;
    std::cin >> num1;

    std::cout << "Enter num2: " << std::flush;
    std::cin >> num2;

    swapInt(&num1, &num2);

    std::cout << "Number 1: " << num1 << std::endl;
    std::cout << "Number 2: " << num2 << std::endl;

    std::cout << "-------POINTERS-------" << std::endl;

    std::cout << "Pointer 1: " << ptr1 << std::endl;
    std::cout << "Pointer 2: " << ptr2 << std::endl;

    std::cout << "====SWAP====" << std::endl;
    swapIntPointer(&ptr1, &ptr2);

    std::cout << "Pointer 1: " << ptr1 << std::endl;
    std::cout << "Pointer 2: " << ptr2 << std::endl;

    return 0;
}
