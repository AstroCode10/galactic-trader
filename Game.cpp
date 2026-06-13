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

    while(running){
        if(player.get_credits() == 0 && player.get_total_item_num() == 0 && player.get_fuel() == 0){
            std::cout << "--- GAME OVER ---" << std::endl;
            std::cout << "You are stranded in the dark void of space with 0 credits, no cargo, and an empty fuel tank." << std::endl;
            running = false;
            break;
        }

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
            std::cout << "Insufficient fuel! Hyperspace Jump requires: " << fuel_cost << " units." << std::endl;
            std::cout << "Please buy more fuel or choose a closer location." << std::endl;
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
}

// Procedure to initialise game
void Game::initialise(){
    std::string player_name;
    curr_planet_idx = 0; 
    BASE_FUEL_COST = 15;

    planets[0] = Planet("Tatooine");
    planets[1] = Planet("Coruscant");
    planets[2] = Planet("Hoth");
    planets[3] = Planet("Endor");
    planets[4] = Planet("Naboo");

    std::cout << "Enter player name: ";
    std::getline(std::cin, player_name);
    player = Player(player_name);
}

// Function to show market menu
void Game::market_menu(int choice){
    int resource_choice;
    int number;
    int cost;
    int market_action;
    bool show_market = true;

    do {
        std::cout << "\n=== Welcome to the " << planets[choice].name << " Market ===" << std::endl;
        planets[choice].display_stats();
        std::cout << "=================================" << std::endl;
        std::cout << "1. Buy Resources" << std::endl;
        std::cout << "2. Sell Resources" << std::endl;
        std::cout << "3. View Shipyard" << std::endl;
        std::cout << "4. Exit Market" << std::endl << std::endl;
        
        std::cout << "Choose an action: ";
        std::cin >> market_action;

        switch (market_action){
            // Buying cargo
            case 1: {
                do {
                    std::cout << "--- Buy Cargo ---" << std::endl;
                    std::cout << "1. Buy Iron (You have: " << player.get_inventory(0) << ")" << std::endl;
                    std::cout << "2. Buy Water (You have: " << player.get_inventory(1) << ")" << std::endl;
                    std::cout << "3. Buy Fuel (You have: " << player.get_fuel() << ")" << std::endl;
                    std::cout << "4. Cancel" << std::endl;
                    std::cout << "Enter your choice: ";
                    std::cin >> resource_choice;

                    if (resource_choice < 1 || resource_choice > 4){
                        std::cout << "Please enter a valid choice (1 - 4)" << std::endl; 
                    }

                } while (resource_choice < 1 || resource_choice > 4);
                
                if (resource_choice != 4){
                    do {
                        std::cout << "How many units would you like to buy? ";
                        std::cin >> number;
                        cost = number * planets[choice].get_prices(resource_choice-1);

                        // Check 1: Financial Balance
                        if (cost > player.get_credits()){
                            std::cout << "Sorry you cannot make the purchase" << std::endl;
                            std::cout << "Total cost of " << cost << " Star Coins is greater than your balance of "
                                    << player.get_credits() << " Star Coins" << std::endl;
                            std::cout << "Please try again\n" << std::endl;
                        }

                        /* Check 2: Physical Cargo Limits 
                        (SAFEGUARD: Only runs if they are NOT buying fuel!) */
                        else if (resource_choice != 3 &&
                            (player.get_total_item_num() + number > ship.get_max_cargo())) {
                            std::cout << "Ship's cargo limit is: " << ship.get_max_cargo() << std::endl;
                            std::cout << "You already have " << player.get_total_item_num()
                            << " in your inventory." << std::endl;
                            std::cout << "Cannot buy " << number << " more units. Please try again."
                            << std::endl << std::endl; 
                        }

                        /* Check 3: Fuel Capacity Limits 
                        (SAFEGUARD: Only runs if they ARE buying fuel!) */
                        else if (resource_choice == 3 &&
                            (player.get_fuel() + number > ship.get_max_fuel())) {
                            std::cout << "Ship's fuel capacity is: " << ship.get_max_fuel() << std::endl;
                            std::cout << "You already have " << player.get_fuel()
                            << " in your inventory." << std::endl;
                            std::cout << "Cannot buy " << number << " more gallons of fuel. Please try again."
                            << std::endl << std::endl; 
                        }

                        else {
                            break;
                        }

                    // Loop runs again if either error state is met
                    } while (cost > player.get_credits() || 
                        (resource_choice != 3 &&
                        (player.get_total_item_num() + number > ship.get_max_cargo())) ||
                        (resource_choice == 3 &&
                        (player.get_fuel() + number > ship.get_max_fuel())));

                    // Processing payment after an appropriate number of units are chosen
                    player.remove_credits(cost);
                    std::cout << "Payment of " << cost << " Star Coins successful!" << std::endl;

                    if (resource_choice == 3){
                        player.add_fuel(number);
                    } else {
                        player.add_item(resource_choice-1, number);
                    }
                }
                break;
            } 

            // Selling cargo
            case 2: {
                do {
                    std::cout << "\n--- Sell Cargo ---" << std::endl;
                    std::cout << "1. Sell Iron (You have: " << player.get_inventory(0) << ")" << std::endl;
                    std::cout << "2. Sell Water (You have: " << player.get_inventory(1) << ")" << std::endl;
                    std::cout << "3. Cancel" << std::endl;
                    std::cout << "Enter your choice: ";
                    std::cin >> resource_choice;
                    
                    if (resource_choice < 1 || resource_choice > 3) {
                        std::cout << "Please enter a valid choice (1 - 3)" << std::endl;
                    }

                } while (resource_choice < 1 || resource_choice > 3);

                if (resource_choice != 3) {
                    do {
                        std::cout << "How many units would you like to sell? ";
                        std::cin >> number;

                        if (player.get_inventory(resource_choice-1) < number){
                            std::cout << "Not enough units in inventory." << std::endl;
                            std::cout << "Only " << player.get_inventory(resource_choice-1) << " in inventory.\n" << std::endl;
                        }
                        else {
                            cost = number * planets[choice].get_prices(resource_choice-1);
                            player.remove_item(resource_choice-1, number);
                            player.add_credits(cost);

                            std::cout << "Sold " << number << " units for " << cost
                            << " Star Coins!" << std::endl;
                        }

                    } while (player.get_inventory(resource_choice-1) < number);
                }
                break;
            }
            
            // Showing shipyard
            case 3:
                shipyard.show_shipyard_menu(player, ship);
                break;

            // Exiting market menu
            case 4:
                show_market = false;
                break;
                
            default:
                std::cout << "Please enter a valid action (1 - 3)" << std::endl;
                break;
        }

    } while (show_market);
}

// Procedure to show travel menu
int Game::travel_menu(){
    int choice;
    
    std::cout << "\nExplorable Planets: " << std::endl;
    for(int i = 0; i < 5; i++){
        std::cout << i+1 << ". " << planets[i].name << std::endl;
    }

    std::cout << "6. Quit Game" << std::endl;

    do{
        std::cout << "Where would you like to travel to? (1 - 6): ";
        std::cin >> choice;

        if(choice < 1 || choice > 6){
            std::cout << "Please enter an option from (1 - 6)" << std::endl; 
        }

    } while(choice < 1 || choice > 6);

    return choice - 1;
}