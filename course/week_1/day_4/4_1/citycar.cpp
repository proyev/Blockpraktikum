#include "citycar.h"

CityCar::CityCar(const std::string &id,
                 const std::string &name,
                 const double &tankCapacity,
                 const double &consumption,
                 const double &maxLoad)
                 :Car(id,
                      name,
                      tankCapacity,
                      consumption),
                      _maxLoad(maxLoad){
    _currentLoad = 0.0;
}

void CityCar::load(const double &weight) {
    if (_maxLoad - _currentLoad >= weight){
        _currentLoad += weight;
        std::cout << "Loaded: " << weight << std::endl;
    }
}

void CityCar::printLoad() {
    std::cout << "Current load: " << _currentLoad << std::endl;
}

void CityCar::unload(const double &weight) {
    if (_currentLoad >= weight){
        _currentLoad -= weight;
        std::cout << "Unloaded: " << weight << std::endl;
    }
}