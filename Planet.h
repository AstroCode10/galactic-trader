// Planet.h

#include <iostream>

class Planet{
    private:
        int prices[3];

    public:
        std::string name;

        Planet();
        Planet(std::string name);

        int get_prices(int i);
        void randomise_prices();
        void display_stats();
};