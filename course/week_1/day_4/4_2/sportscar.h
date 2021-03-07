#ifndef INC_4_1_SPORTSCAR_H
#define INC_4_1_SPORTSCAR_H
#include "car.h"

class SportsCar : public Car{
public:
    enum Roof{open, closed};
    SportsCar(const std::string &id,
              const std::string &name,
              const double &tankCapacity,
              const double &consumption);

    void roof(Roof top);
    virtual void honk() const;

private:
    Roof _top;

};


#endif //INC_4_1_SPORTSCAR_H
