#include "citycar.h"

Car::Car(const std::string &id,
         const std::string &name,
         const double &tankCapacity,
         const double &consumption)
        :
        _id(id),
        _name(name),
        _tankCapacity(tankCapacity),
        _consumption(consumption)
{
    _fuel = 0.0;
    _mileage = 0.0;
    std::cout << "Car object was created" << std::endl;

}

const double Car::fillLevel() {
    return _fuel;
}

const double Car::reach() {
    return _fuel / _consumption * 100;
}

const double Car::milage() {
    return _mileage;
}

void Car::honk() const {
    std::cout << "Beep" << std::endl;
}

const bool Car::refuel(const double &volume) {
    if (_tankCapacity - fillLevel() >= volume){
        _fuel += volume;
        return true;
    }else{
        return false;
    }
}

const bool Car::drive(const double &distance) {
    if (reach() >= distance){
        _fuel -= distance / 100 * _consumption;
        _mileage += distance;
        return true;
    }else{
        return false;
    }
}
