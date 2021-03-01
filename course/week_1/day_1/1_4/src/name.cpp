#include <iostream>
#include <string>
#include "printNameAndAge.h"

int main()//int argc - arg count -
//count the number of parameters which will be given from the console
//
//char* argv[] - list of parameter values, which will be given from the console
//Para, 0 - always gonna be .out file
//rest - will be processed in their positional form

{
    int age;
    std::string firstName, lastName;


    
    std::cout << "Your name: ";
    std::cin >> firstName;
    std::cin >> lastName;
    std::cout << std::endl;

//    std::cin >> name;

    std::cout << "Your age: ";
    std::cin >> age;
    std::cout << std::endl;

    printNameAndAge(firstName, lastName, age);

    if (age < 18){
        std::cout << "Your are a baby!" << std::endl;
    }else if(age < 30){
        std::cout << "You are quite young" << std::endl;
    }else if(age < 50){
        std::cout << "Getting wiser" << std::endl;
    }else{
        std::cout << "You've seen stuff" << std::endl;
    }

    return 0;
}
