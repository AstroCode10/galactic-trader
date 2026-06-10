// Game.cpp

#include "Game.h"
#include <iostream>
#include <cmath>

// Procedure to run game
void Game::run(){
    int user_choice;
    int fuel_cost;
    bool running = true;
    initialise();

    while(player.get_credits() > 0 && running){
        player.display_stats();
        user_choice = travel_menu();
        if (user_choice == 5) {
            running = false;
            break;
        }

        if (user_choice == curr_planet_idx){
            std::cout << "You are already orbiting " << planets[user_choice].name << std::endl;
            market_menu(user_choice);
            continue;
        }

        fuel_cost = BASE_FUEL_COST * std::abs(user_choice - curr_planet_idx);

        if (fuel_cost > player.get_fuel()){
            std::cout << "Insufficient fuel! Hyperspace Jump requires: " << fuel_cost << std::endl;
            std::cout << "Please buy more fuel or choose a closer location" << std::endl;
            market_menu(curr_planet_idx);
            continue;
        }

        player.remove_fuel(fuel_cost);
        curr_planet_idx = user_choice;

        for(int i = 0; i < 5; i++) {
            planets[i].randomise_prices();
        }

        std::cout << "[HYPERSPACE JUMP] Burned " << fuel_cost << " units of fuel." << std::endl;
        std::cout << "Arriving at " << planets[user_choice].name << "..." << std::endl << std::endl;
        market_menu(user_choice);
    }

    std::cout << "Thank you for playing with us!";

}

// Procedure to initialise game
void Game::initialise(){
    std::string player_name;

    planets[0] = Planet("Tatooine");
    planets[1] = Planet("Coruscant");
    planets[2] = Planet("Hoth");
    planets[3] = Planet("Endor");
    planets[4] = Planet("Naboo");

    std::cout << "Enter player name: ";
    std::getline(std::cin, player_name);
    player = Player(player_name);
};

// Function to show market menu
void Game::market_menu(int choice){
    int resource_choice;
    int number;
    int cost;
    int market_action;
    bool show_market = true;;

    do {
        std::cout << "=== Welcome to the " << planets[choice].name << " Market ===" << std::endl;
        planets[choice].display_stats();
        std::cout << "=================================" << std::endl;
        std::cout << "1. Buy Resources" << std::endl;
        std::cout << "2. Sell Resources" << std::endl;
        std::cout << "3. Exit Market" << std::endl;
        std::cout << "Choose an action: ";
        std::cin >> market_action;

        switch (market_action){
            // Buying cargo
            case 1: {
                do {
                    std::cout << "-- Buy Cargo ---" << std::endl;
                    std::cout << "1. Buy Iron (You have: " << player.get_inventory(0) << ")" << std::endl;
                    std::cout << "2. Buy Water (You have: " << player.get_inventory(1) << ")" << std::endl;
                    std::cout << "3. Buy Fuel (You have: " << player.get_fuel() << ")" << std::endl;
                    std::cout << "4. Cancel" << std::endl;

                    std::cin >> resource_choice;

                    if (resource_choice < 1 || resource_choice > 4){
                    std::cout << "Please enter a valid choice (1 - 4)" << std::endl; 
                    }

                } while (resource_choice < 1 || resource_choice > 4);
                
                if (resource_choice != 4){
                    do {
                        std::cout << "How many units would you like to buy? " << std::endl;
                        std::cin >> number;
                        cost = number * planets[choice].get_prices(resource_choice-1);

                        if (cost > player.get_credits()){
                            std::cout << "Sorry you cannot make the purchase" << std::endl;
                            std::cout << "Total cost of " << cost << " Star Coins 
                            is greater than your balance of "
                            << player.get_credits() << " Star Coins" << std::endl;
                            std::cout << "Please try again" << std::endl;
                        }

                    } while (cost > player.get_credits());

                    player.remove_credits(cost);
                    std::cout << "Payment of " << cost << " Star Coins successful!" << std::endl;

                    if (resource_choice == 3){
                        player.add_fuel(number);
                    }
                }
                break;
            }

            // Selling cargo
            case 2: {
                    std::cout << "-- Sell Cargo ---" << std::endl;
                    std::cout << "1. Sell Iron (You have: " << player.get_inventory(0) << ")" << std::endl;
                    std::cout << "2. Sell Water (You have: " << player.get_inventory(1) << ")" << std::endl;
                    std::cout << "3. Cancel" << std::endl;

                do {
                    std::cout << "Enter your choice:  ";
                    std::cin >> resource_choice;
                    
                    if (resource_choice < 1 || resource_choice > 3) {
                        std::cout << "Please enter a valid choice (1 - 3)" << std::endl;
                    }

                } while (resource_choice < 1 || resource_choice > 3);

                do {
                    std::cout << "How many units would you like to sell? " << std::endl;
                    std::cin >> number;

                    if (inventory.get_inventory(resource_choice-1) < number){
                        std::cout << "Not enough units in inventory." << std::endl;
                        std::cout << "Only " << inventory.get_inventory(resource_choice-1) <<
                        " in inventory." << std::endl;
                    }

                    else {
                        cost = number * planets[choice].get_prices[resource_choice-1];
                        player.remove_item(resource_choice-1, number);
                        player.add_credits(cost);

                        std::cout << "Sold " << qty_to_sell << " units for " << earnings << " Star Coins!" << std::endl;
                    }

                } while (inventory.get_inventory(resource_choice-1) < number);

                break;
            }

            // Exiting market menu
            case 3:
                show_market = false;
                break;
                
            default:
                std::cout << "Please enter a valid action (1 - 3)"
        }
    } (while show_market && (market_action < 1 || market_action > 3));

}

// Procedure to show travel menu
int Game::travel_menu(){
    int choice;
    
    std::cout << "Explorable Planets: " << std::endl;
    for(int i = 0; i < sizeof(planets)/sizeof(planets[0]); i++){
        std::cout << i+1 << ". " << planets[i].name << std::endl;
    }

    std::cout << "6. Quit Game" << std::endl;

    do{
        std::cout << "Where would you like to travel to? (1 - 5): ";
        std::cin >> choice;

        if(choice < 1 || choice > 6){
            std::cout << "Please enter an option from (1 - 6)" << std::endl; 
        }

    } while(choice < 1 || choice > 6);

    return choice - 1;
}