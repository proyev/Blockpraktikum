#include "printNameAndAge.h"
#include <iostream>
#include <string>

void printNameAndAge(std::string firstName, std::string lastName, int age){
    std::cout << firstName << " " << lastName
        << " - " << age << " years" << std::endl;
}