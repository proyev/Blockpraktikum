#include "fizzbuzz.h"

void fizzbuzz(int number){

    int i = 1;
    while (i <= number){
        if ((i % 3 == 0) && (i % 5 == 0)){
            std::cout << "FizzBuzz" << std::endl;
            i++;
            continue;
        }else if (i % 5 == 0){
            std::cout << "Buzz" << std::endl;
            i++;
            continue;
        }else if(i % 3 == 0){
            std::cout << "Fizz" << std::endl;
            i++;
            continue;
        }
        std::cout << i << std::endl;
        i++;
    }
}
