// Game.h

#pragma once
#include "Player.h"
#include "Planet.h"
#include "Ship.h"
#include "Shipyard.h"

class Game{
    private:
        Player player;
        Planet planets[5];
        Ship ship;
        Shipyard shipyard;
        int curr_planet_idx;
        int BASE_FUEL_COST;

    public:
        void initialise();
        void run();

        void save_game();
        bool load_game();

        void market_menu(int choice);
        int travel_menu();
};