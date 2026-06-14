// Player.cpp

#include "Player.h"
#include <iostream>
#include <unordered_map>

// Default Player constructor with runs when Game object is first created
Player::Player(){
    name = "Player";
    credits = 1000;
    fuel = 100;

    // Iron, Water
    inventory [0] = 0;
    inventory [1] = 0;
    
    // Registry of ships bought or not
    ship_registry["Rusty Scout"] = true;
    ship_registry["Cargo Hauler"] = false;
    ship_registry["Falcon Scout"] = false;
}

// Player constructor
Player::Player(std::string name){
    this->name = name;
    credits = 1000;
    fuel = 100;

    // Iron, Water
    inventory [0] = 0;
    inventory [1] = 0;

    // Registry of ships bought or not
    ship_registry["Rusty Scout"] = true;
    ship_registry["Cargo Hauler"] = false;
    ship_registry["Falcon Scout"] = false;
}

// Getter to return credits
int Player::get_credits() const {
    return credits;
}

// Getter to return fuel
int Player::get_fuel() const {
    return fuel;
}

// Getter to return amount of an item remaining
int Player::get_item(int idx) const {
    return inventory[idx];
}

// Getter to return amount of an item remaining
int Player::get_total_item_num() const {
    int count = 0;
    for (int i = 0; i < sizeof(inventory)/sizeof(inventory[0]); i++) {
        count ++;
    }
    return count;
}

// Getter to return status of whether ship was bought or not
const unordered_map<std::string, bool> &get_registry() const{
    return ship_registry;
}


// Setter to deduct credits
void Player::remove_credits(int amount){
    credits -= amount;
}

// Setter to add credits
void Player::add_credits(int amount){
    credits += amount;
}

// Setter to deduct fuel
void Player::remove_fuel(int amount){
    fuel -= amount;
}

// Setter to add fuel
void Player::add_fuel(int amount){
    fuel += amount;
}

// Setter to deduct quantity of an item
void Player::remove_item(int idx, int amount){
    inventory[idx] -= amount;
}

// Setter to increase quantity of an item
void Player::add_item(int idx, int amount){
    inventory[idx] += amount;
}

// Setter to change status of ship (owned/not owned)
void Player::unlock_ship(std::string name){
    ship_registry[name] = true; 
}

// Procedure showing player's resource quantity (credits, fuel, iron, water)
void Player::display_stats() const {
    std::cout << "\n=== " << name << "'s Status ===" << std::endl;
    std::cout << "Credits: " << credits << " Star Coins" << std::endl;
    std::cout << "Fuel Tank: " << fuel << " units" << std::endl;
    std::cout << "Cargo Hold: " << get_total_item_num() << " units loaded" << std::endl;
    std::cout << "  - Iron: " << inventory[0] << " units" << std::endl;
    std::cout << "  - Water: " << inventory[1] << " units" << std::endl;
    std::cout << "==========================" << std::endl;
}