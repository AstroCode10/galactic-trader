// Game.h

#pragma once
#include <random>
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
        int FLAT_TOLL;
        int DERELICT_FUEL;

    public:
        void initialise();
        void run();

        void save_game();
        bool load_game();

        void market_menu(int choice);
        int travel_menu();

        void check_random_encounter(std::mt19937 &eng);
        void handle_debris();
        void handle_solar_flare(std::mt19937 &eng);
        void handle_salvage(std::mt19937 &eng);
        void handle_pirate_event(std::mt19937 &eng);
        void handle_alien_merchant();
};