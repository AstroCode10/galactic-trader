// Player.h

#pragma once
#include <iostream>

class Player {
    private:
        int credits;
        int fuel;
        int inventory [2];

    public:
        std::string name;

        Player();
        Player(std::string name);

        int get_credits();
        int get_fuel();
        int get_item(int idx);
        int get_total_item_num();

        void remove_credits(int amount);
        void add_credits(int amount);
        
        void remove_fuel(int amount);
        void add_fuel(int amount);

        void remove_item(int idx, int amount);
        void add_item(int idx, int amount);

        void display_stats();

};