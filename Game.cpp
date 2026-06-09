// Game.cpp

#include "Game.h"
#include <iostream>
#include <cmath>

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

void Game::market_menu(int choice){
    int resource_choice;
    int number;
    int cost;

    std::cout << "Prices at " << planets[choice].name << ": " << std::endl;
    planets[choice].display_stats();

    do {
        std::cout << "Enter the number of the resource you would like to buy (4 to leave planet): "
        << std::endl;
        std::cin >> resource_choice;

        if (resource_choice < 1 || resource_choice > 4){
        std::cout << "Please enter a valid choice (1 - 4)" << std::endl; 
        }

    } while (resource_choice < 1 || resource_choice > 4);
    
    if (resource_choice != 4){
        do {
            std::cout << "How many of the resource would you like to buy? " << std::endl;
            std::cin >> number;
            cost = number * planets[choice].get_prices(resource_choice-1);

            if (cost > player.get_credits()){
                std::cout << "Sorry you cannot make the purchase" << std::endl;
                std::cout << "Total cost of " << cost << " Star Coins is greater than your balance of "
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

}

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