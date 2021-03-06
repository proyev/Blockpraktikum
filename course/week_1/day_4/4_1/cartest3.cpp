#include <iostream>
#include "car.h"
#include "citycar.h"
#include "sportscar.h"

int main() {

    CityCar cityCar("AA1234", "VW",50.0, 5.0, 50.0);
    cityCar.printLoad();
    cityCar.load(25.0);
    cityCar.load(25.0);
    cityCar.printLoad();
    cityCar.unload(25.0);

    /*For this to work - the default parameters in class should be set
     * SportsCar *sportscar = new SportsCar;
    sportscar->roof(SportsCar::open);
    sportscar->roof(SportsCar::closed);
     delete sportscar;*/

    SportsCar sportsCar("AA1234", "BMW", 50.0, 13.0);
    sportsCar.roof(SportsCar::open);
    sportsCar.roof(SportsCar::closed);


    return 0;
}
