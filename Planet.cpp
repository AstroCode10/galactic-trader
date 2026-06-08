// Planet.cpp

#include <iostream>
#include <random>
#include "Planet.h"


Planet::Planet(){
    name = "Unknown";

    // Iron, Water, Fuel
    prices[0] = 0;
    prices[1] = 0;
    prices[2] = 0;

};

Planet::Planet(std::string name){
    this->name = name;
    prices[0] = 0;
    prices[1] = 0;
    prices[2] = 0;

};

int Planet::get_prices(int i){
    return prices[i];
};

// Function to randomie prices
void Planet::randomise_prices(){
    std::random_device rd;
    std::mt19937 engine(rd());

    std::uniform_int_distribution<int> iron_dist(50, 120); // Range of iron price: 50 - 120
    std::uniform_int_distribution<int> water_dist(20, 80); // Range of water prices: 20 - 80
    std::uniform_int_distribution<int> fuel_dist(30, 100); // Range of fuel prices: 30 - 100

    prices[0] = iron_dist(engine);
    prices[1] = water_dist(engine);
    prices[2] = fuel_dist(engine);
};

void Planet::display_stats(){
    std::cout << "Iron price: " << prices[0] << std::endl;
    std::cout << "Water price: " << prices[1] << std::endl;
    std::cout << "Fuel price: " << prices[2] << std::endl;
};