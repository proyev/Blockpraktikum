#include <iostream>
#include "enum.cpp"


int main() {
    //using namespace sColor;
    //using namespace fColor;

    ShirtColor shirtColor = ShirtColor::RED;

    switch (shirtColor) {
        case(ShirtColor::RED):
            std::cout << "Your shirt is RED" << std::endl;
            break;
        case (ShirtColor::BLACK):
            std::cout << "Your shirt is BLACK" << std::endl;
            break;
        case (ShirtColor::WHITE):
            std::cout << "Your shirt is WHITE" << std::endl;
            break;
        default:
            std::cout << "Unknown color" << std::endl;
    }


    return 0;
}
