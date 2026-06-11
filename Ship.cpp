// Ship.h

#pragma once
#include <iostream>

Ship::Ship(){
    ship_type = "Rusty Scout";
    max_fuel = 100;
    max_cargo = 20;
}

Ship::Ship(std::string ship_type, int max_fuel, int max_cargo){
    this->ship_type;
    this->max_fuel;
    this->max_cargo;
}

Ship::std::string get_ship_type(){
    return ship_type;
}

Ship::int get_max_fuel(){
    return max_fuel;
}

Ship::int get_max_cargo(){
    return max_cargo;
}

Ship::void display_ship_specs(){
    std::cout << "--- Ship Specifications ---" << std::endl;
    std::cout << "Model: " << ship_type << std::endl;
    std::cout << "Max Fuel Tank: " << max_fuel_capacity << " units" << std::endl;
    std::cout << "Max Cargo Hold: " << max_cargo_capacity << " slots" << std::endl;
}