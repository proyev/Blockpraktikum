#include "getNumber.h"
#include <chrono>
#include <random>

uint16_t getNumber(uint16_t low, uint16_t high){
    std::srand(std::time(0));

    int randomNumber = std::rand();

    int guessNumber = low + (randomNumber % (high - low + 1));
    return guessNumber;
}