// Player.cpp

#include "Player.h"
#include <iostream>

Player::Player() {
    name = "Player";
    credits = 1000;
    fuel = 100;
    inventory[0] = 0;
    inventory[1] = 0;

    ship_registry["Rusty Scout"] = true;
    ship_registry["Cargo Hauler"] = false;
    ship_registry["Falcon Scout"] = false;
}

Player::Player(std::string name) {
    this->name = name;
    credits = 1000;
    fuel = 100;
    inventory[0] = 0;
    inventory[1] = 0;

    ship_registry["Rusty Scout"] = true;
    ship_registry["Cargo Hauler"] = false;
    ship_registry["Falcon Scout"] = false;
}

int Player::get_credits() const {
    return credits;
}

int Player::get_fuel() const {
    return fuel;
}

int Player::get_item(int idx) const {
    return inventory[idx];
}

int Player::get_inventory(int idx) const {
    return inventory[idx];
}

int Player::get_total_item_num() const {
    return inventory[0] + inventory[1];
}

const std::unordered_map<std::string, bool> &Player::get_registry() const {
    return ship_registry;
}

void Player::remove_credits(int amount) {
    credits -= amount;
}

void Player::add_credits(int amount) {
    credits += amount;
}

void Player::remove_fuel(int amount) {
    if (fuel - amount < 0) {
        fuel = 0;
    } else {
        fuel -= amount;
    }
}

void Player::add_fuel(int amount) {
    fuel += amount;
}

void Player::remove_item(int idx, int amount) {
    if (inventory[idx] - amount < 0) {
        inventory[idx] = 0;
    } else {
        inventory[idx] -= amount;
    }
}

void Player::add_item(int idx, int amount) {
    inventory[idx] += amount;
}

void Player::unlock_ship(std::string name) {
    ship_registry[name] = true;
}

void Player::set_ship_owned(std::string name, bool owned) {
    ship_registry[name] = owned;
}

void Player::set_name(std::string name) {
    this->name = name;
}

void Player::set_credits(int amount) {
    credits = amount;
}

void Player::set_fuel(int amount) {
    fuel = amount;
}

void Player::set_item(int idx, int amount) {
    inventory[idx] = amount;
}

void Player::display_stats() const {
    std::cout << "\n=== " << name << "'s Status ===" << std::endl;
    std::cout << "Credits: " << credits << " Star Coins" << std::endl;
    std::cout << "Fuel Tank: " << fuel << " units" << std::endl;
    std::cout << "Cargo Hold: " << get_total_item_num() << " units loaded" << std::endl;
    std::cout << "  - Iron: " << inventory[0] << " units" << std::endl;
    std::cout << "  - Water: " << inventory[1] << " units" << std::endl;
    std::cout << "==========================" << std::endl;
}
