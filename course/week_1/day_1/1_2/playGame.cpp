#include "playGame.h"

    void playGame(uint16_t  guessNumber){
        uint16_t guess;
        std::cout << "Guess the number: " << std::flush;
        std::cin >> guess;

        while (guess != guessNumber){
            if(guess > guessNumber){
                std::cout << "Your number is too large" << std::endl;
            }else{
                std::cout << "Your number is too small" << std::endl;
            }

            std::cout << "Guess the number: " << std::flush;
            std::cin >> guess;
        }

        std::cout << "Congratulations, you won!" << std::endl;

}
