// Ship.h

#pragma once
#include <iostream>

Ship::Ship(){
    ship_type = "Rusty Scout";
    max_fuel = 100;
    max_cargo = 20;
    damage_cost = 0;
}

Ship::Ship(std::string ship_type, int max_fuel, int max_cargo){
    this->ship_type;
    this->max_fuel;
    this->max_cargo;
    this->damage_cost;
}

std::string Ship::get_ship_type(){
    return ship_type;
}

int Ship::get_max_fuel(){
    return max_fuel;
}

int Ship::get_max_cargo(){
    return max_cargo;
}

int Ship::get_damage_cost(){
    return damage_cost;
}

void Ship::display_ship_specs(){
    std::cout << "--- Ship Specifications ---" << std::endl;
    std::cout << "Model: " << ship_type << std::endl;
    std::cout << "Max Fuel Tank: " << max_fuel_capacity << " units" << std::endl;
    std::cout << "Max Cargo Hold: " << max_cargo_capacity << " slots" << std::endl;
}

void Ship::del_cargo_slots(int amount){
    max_cargo -= amount;
}

void Ship::set_damage_cost(int amount){
    damage_cost = amount;
}

void Ship::set_max_cargo(int amount){
    max_cargo = amount;
}