#ifndef INC_4_1_CITYCAR_H
#define INC_4_1_CITYCAR_H
#include "car.h"

class CityCar : public Car{
    public:
        CityCar(const std::string &id,
                const std::string &name,
                const double &tankCapacity,
                const double &consumption,
                const double &maxLoad);

        void load(const double &weight);
        void unload(const double &weight);
        void printLoad();

    private:
        const double _maxLoad;
        double _currentLoad;
};


#endif //INC_4_1_CITYCAR_H
