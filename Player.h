// Player.h

#pragma once
#include <iostream>
#include <unordered_map>

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
        int get_credits() const;
        int get_fuel() const;
        int get_item(int idx) const;
        int get_total_item_num() const;
        const unordered_map<std::string, bool> &get_registry() const;

        // Setters to add/remove
        void remove_credits(int amount);
        void add_credits(int amount);
        void remove_fuel(int amount);
        void add_fuel(int amount);
        void remove_item(int idx, int amount);
        void add_item(int idx, int amount);
        void unlock_ship(std::string name);

        // Setters to load saved values
        void set_name(std::string name);
        void set_credits(int amount);
        void set_fuel(int amount);
        void set_item(int idx, int amount);

        // Getter to display player stats
        void display_stats() const;

};