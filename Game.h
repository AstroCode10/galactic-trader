// Game.h

#pragma once
#include "Player.h"
#include "Planet.h"

class Game{
    private:
        Player player;
        Planet planet[5];

    public:
        void initialise();
        void run();
        void market_menu(int choice);
        int travel_menu();
};