// Player.cpp

#include "Player.h"
#include <iostream>

// Default Player constructor with runs when Game object is first created
Player::Player(){
    name = "Player";
    credits = 1000;
    fuel = 100;

    // Iron, Water
    inventory [0] = 0;
    inventory [1] = 0;
}

// Player constructor
Player::Player(std::string name){
    this->name = name;
    credits = 1000;
    fuel = 100;
}

// Getter to return credits
int Player::get_credits(){
    return credits;
}

// Getter to return fuel
int Player::get_fuel(){
    return fuel;
}

// Getter to return amount of an item remaining
int Player::get_item(int idx){
    return inventory[idx];
}

// Getter to return amount of an item remaining
int Player::get_total_item_num(){
    int count = 0;
    for (int i; i < sizeof(inventory)/sizeof(inventory[0]); i++) {
        count ++
    }
    return count;
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

// Procedure showing player's resource quantity (credits, fuel, iron, water)
void Player::display_stats(){
    std::cout << name << "'s credits: " << credits << std::endl;
    std::cout << name << "'s fuel: " << fuel << std::endl;
    std::cout << name << "'s iron: " << inventory[0] << " units" << std::endl;
    std::cout << name << "'s water: " << inventory[1] << " units" << std::endl;
}