#ifndef INC_2_3_CAR_H
#define INC_2_3_CAR_H
#include <iostream>
#include <string>

    class Car{
        private:
            const std::string &_id;
            const std::string &_name;
            const double &_tankCapacity;
            const double &_lpkm;
            double _tankState;
            double _kilometerstand;

        public:
            Car ();
            Car (const std::string &id = "",
                 const std::string &name = "",
                 const double &tankCapacity = 0.0,
                 const double &lpkm = 0.0,
                 double tankState = 0.0,
                 double kilometerstand = 0.0);

            double fillLevel();
            double reach();
            double milage();

            bool refuel(double &volume);
            double drive(double &distance);

};

#endif //INC_2_3_CAR_H