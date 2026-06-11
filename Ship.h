// Ship.h

#pragma once
#include <iostream>

class Ship {
    protected:
        std::string ship_type;
        int max_fuel;
        int max_cargo;

    public:
        Ship();
        Ship(std::string ship_type, int max_fuel, int max_cargo);

        std::string get_ship_type();
        int get_max_fuel();
        int get_max_cargo();

        void display_ship_specs();

};