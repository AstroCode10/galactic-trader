// Player.cpp

#include "Player.h"
#include <iostream>

Player::Player(){
    name = "Player";
    credits = 1000;
    fuel = 100;
}

Player::Player(std::string name){
    this->name = name;
    credits = 1000;
    fuel = 100;
}

int Player::get_credits(){
    return credits;
}

int Player::get_fuel(){
    return fuel;
}

void Player::remove_credits(int amount){
    credits -= amount;
}

void Player::add_credits(int amount){
    credits += amount;
}

void Player::remove_fuel(int amount){
    fuel -= amount;
}

void Player::add_fuel(int amount){
    fuel += amount;
}

void Player::display_stats(){
    std::cout << name << "'s credits: " << credits << std::endl;
    std::cout << name << "'s fuel: " << fuel << std::endl;
}