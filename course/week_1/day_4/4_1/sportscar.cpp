#include "sportscar.h"

SportsCar::SportsCar(const std::string &id,
                     const std::string &name,
                     const double &tankCapacity,
                     const double &consumption)
                     :Car(id,
                          name,
                          tankCapacity,
                          consumption){
    _top = closed;
}

void SportsCar::roof(Roof top) {
    _top = top;
    if(_top==open){
        std::cout << "Closing the top" << std::endl;
        _top=closed;
    }else{
        std::cout << "Opening the top" << std::endl;
        _top=open;
    }
}
