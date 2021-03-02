#include <iostream>
#include "swapInt.h"
using std::cout, std::endl, std::cin;
int main() {
    int num1, num2;

    cout << "Enter the first number: " << std::flush;
    cin >> num1;

    cout << "Enter the second number: " << std::flush;
    cin >> num2;

    cout << "The first number is " << num1 << "\n"
        << "The second number is " << num2 << endl;

    swapInt(num1, num2);

   cout << "-------Swaped numbers-------" << "\n"
        << "The first number is " << num1 << "\n"
        << "The second number is " << num2 << endl;

    return 0;
}
