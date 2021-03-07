#include <iostream>
#include "car.h"
#include "citycar.h"
#include "sportscar.h"

int main() {

    Car car("AE1298", "Toyota", 35.0, 7.0);

    CityCar cityCar("AA1234", "VW",50.0, 5.0, 50.0);
    cityCar.printLoad();
    cityCar.load(25.0);
    cityCar.load(25.0);
    cityCar.printLoad();
    cityCar.unload(25.0);
    cityCar.honk();

    /*For this to work - the default parameters in class should be set
     * SportsCar *sportscar = new SportsCar;
    sportscar->roof(SportsCar::open);
    sportscar->roof(SportsCar::closed);
     delete sportscar;*/

    SportsCar sportsCar("AA1111", "BMW", 50.0, 13.0);
    sportsCar.roof(SportsCar::open);
    sportsCar.roof(SportsCar::closed);
    sportsCar.honk();

    Car *carPtr;
    carPtr = &car;
    carPtr->honk();

    carPtr = &cityCar;
    carPtr->honk();

    carPtr = &sportsCar;
    carPtr->honk();

    return 0;
}
