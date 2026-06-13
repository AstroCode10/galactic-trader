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
}

class Shipyard {
    private:
        std::unordered_map<std::string, ShipSpecs> catalog;

    public:
        Shipyard();
        void show_shipyard_menu(Player &player, Ship &curr_ship);
}