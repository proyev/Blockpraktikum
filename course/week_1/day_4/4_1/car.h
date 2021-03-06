#ifndef INC_4_1_CAR_H
#define INC_4_1_CAR_H
#include <iostream>
#include <string>

class Car{
public:
    Car(const std::string &id,
        const std::string &name,
        const double &tankCapacity,
        const double &consumption);

    const bool refuel(const double &volume);
    const bool drive(const double &distance);

    const double fillLevel();
    const double reach();
    const double milage();

private:
    const std::string _id;
    const std::string _name;
    const double _tankCapacity;
    const double _consumption;
    double _fuel;
    double _mileage;

};

#endif //INC_4_1_CAR_H
