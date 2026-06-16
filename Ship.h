// Ship.h

#pragma once
#include <iostream>

class Ship {
    protected:
        std::string ship_type;
        int max_fuel;
        int max_cargo;
        int damage_cost;

    public:
        Ship();
        Ship(std::string ship_type, int max_fuel, int max_cargo);

        std::string get_ship_type();
        int get_max_fuel();
        int get_max_cargo();
        int get_damage_cost();

        void display_ship_specs();
        void del_cargo_slots(int amount);
        void set_damage_cost(int amount);
        void set_max_cargo(int amount);

};