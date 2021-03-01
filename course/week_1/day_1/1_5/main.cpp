#include <iostream>
#include "fizzbuzz.h"

int main() {
    int number;

    std::cout << "Enter the number: " << std::flush;
    std::cin >> number;

    fizzbuzz(number);

    return 0;
}
