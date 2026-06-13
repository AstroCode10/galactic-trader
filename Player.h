// Player.h

#pragma once
#include <iostream>
#include unordered_map

class Player {
    private:
        int credits;
        int fuel;
        int inventory [2];
        std::unordered_map<std::string, bool> ship_registry;

    public:
        std::string name;

        Player();
        Player(std::string name);


        // Getters
        int get_credits();
        int get_fuel();
        int get_item(int idx);
        int get_total_item_num();
        bool get_ship_status(std::string key);

        // Setters
        void remove_credits(int amount);
        void add_credits(int amount);
        
        void remove_fuel(int amount);
        void add_fuel(int amount);

        void remove_item(int idx, int amount);
        void add_item(int idx, int amount);

        void display_stats();

};