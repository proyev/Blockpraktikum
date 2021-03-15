#include "car.h"

int main(){
    Car car("AA1234",
            "VW Polo",
            50.0,
            5.0);

    car.refuel(20.0);

    std::cout << "Fuel: " << car.fillLevel() << "\n"
            << "Mileage: " << car.milage() << "\n"
            << "Reach: " << car.reach() << std::endl;

    car.drive(10.0);

    std::cout << "Fuel: " << car.fillLevel() << "\n"
              << "Mileage: " << car.milage() << "\n"
              << "Reach: " << car.reach() << std::endl;

    car.refuel(50.0 - car.fillLevel());

    std::cout << "Fuel: " << car.fillLevel() << "\n"
              << "Mileage: " << car.milage() << "\n"
              << "Reach: " << car.reach() << std::endl;

    car.drive(car.reach());

    std::cout << "Fuel: " << car.fillLevel() << "\n"
              << "Mileage: " << car.milage() << "\n"
              << "Reach: " << car.reach() << std::endl;

    car.drive(10.0);

    std::cout << "Fuel: " << car.fillLevel() << "\n"
              << "Mileage: " << car.milage() << "\n"
              << "Reach: " << car.reach() << std::endl;

    car.refuel(50.0 - car.fillLevel());

    std::cout << "Fuel: " << car.fillLevel() << "\n"
              << "Mileage: " << car.milage() << "\n"
              << "Reach: " << car.reach() << std::endl;

    car.refuel(10.0);

    std::cout << "Fuel: " << car.fillLevel() << "\n"
              << "Mileage: " << car.milage() << "\n"
              << "Reach: " << car.reach() << std::endl;

    return 0;
}