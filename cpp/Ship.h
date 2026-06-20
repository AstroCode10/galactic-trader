// Ship.h

#pragma once
#include <string>
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

        std::string get_type() const;
        std::string get_ship_type() const;
        int get_max_fuel() const;
        int get_max_cargo() const;
        int get_damage_cost() const;

        void display_ship_specs() const;
        void del_cargo_slots(int amount);
        void set_damage_cost(int amount);
        void set_max_cargo(int amount);
};
