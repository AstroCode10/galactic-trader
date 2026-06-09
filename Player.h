// Player.h

#include <iostream>

class Player {
    private:
        int credits;
        int fuel;

    public:
        std::string name;

        Player();
        Player(std::string name);

        int get_credits();
        int get_fuel();

        void remove_credits(int amount);
        void add_credits(int amount);
        
        void remove_fuel(int amount);
        void add_fuel(int amount);

        void display_stats();

}