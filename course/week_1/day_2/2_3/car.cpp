#include "car.h"
Car::Car()
:   _id(""),
    _name(""),
    _tankCapacity(0.0),
    _lpkm(0),
    _tankState(0.0),
    _kilometerstand(0.0)
{
    std::cout << "Default constructor was called" << std::endl;
}

Car::Car(const std::string &id,
         const std::string &name,
         const double &tankCapacity,
         const double &lpkm):
         _id(id),
         _name(name),
         _tankCapacity(tankCapacity),
         _lpkm(lpkm)
{
    std::cout << "Constructor was called" << std::endl;
}

bool Car::refuel(double &volume) {

    if (tankCapacity - fillLevel() > volume){
        tankState += volume;
        return true;
    }else {
        return false;
    }
}

double Car::drive(double &distance) {

    if (reach() < distance){
        kilometerstand += distance;
        tankState -= distance/100 * lpkm;
        return distance;
    }else{
        distance = reach();
        kilometerstand += distance;
        tankState = 0;
        return distance;
    }

}

double Car::milage() {
    return kilometerstand;
}

double Car::reach() {
    return tankState/lpkm * 100;
}

double Car::fillLevel() {
    return tankState;
}
