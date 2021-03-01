#include <iostream>
#include "getNumber.h"
#include "playGame.h"

int main() {
    uint16_t low, high;
    std::cout << "Welcome to \"Guess the number\"" << std::endl;
    std::cout << "Set the range to guess the number" << std::endl;

    std::cout << "Lower bound: " << std::flush;
    std::cin >> low;

    std::cout << "Upper bound: " << std::flush;
    std::cin >> high;

    uint16_t guessNumber = getNumber(low, high);
    playGame(guessNumber);

    return 0;
}
