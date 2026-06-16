// Shipyard.h

#pragma once
#include <iostream>
#include <unordered_map>
#include "Player.h"
#include "Ship.h"

struct ShipSpecs {
    int max_fuel;
    int max_cargo;
    int cost;
};

class Shipyard {
    private:
        std::unordered_map<std::string, ShipSpecs> catalog;

    public:
        Shipyard();
        Ship get_ship_blueprint(std::string ship_name);
        void show_shipyard_menu(Player &player, Ship &curr_ship);
        void repair_ship(Ship &curr_ship);
}