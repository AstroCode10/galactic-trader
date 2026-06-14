// Shipyard.cpp
#include "Shipyard.h"
#include <iostream>
#include <unordered_map>
#include <vector>

Shipyard::Shipyard() {
    catalog["Rusty Scout"] = {100, 20, 0};
    catalog["Cargo Hauler"] = {80, 60, 400};
    catalog["Falcon Scout"] = {250, 15, 600};
}

Ship Shipyard::get_ship_blueprint(std::string ship_name){
    if (catalog.find(ship_name) != catalog.end()){
        ShipSpecs specs = catalog[ship_name];
        return Ship(ship_name, specs.max_fuel, specs.max_cargo);
    }

    ShipSpecs default_specs = catalog["Rusty Scout"];
    return Ship("Rusty Scout", default_specs.max_fuel, default_specs.max_cargo);
}

void Shipyard::show_shipyard_menu(Player &player, Ship &curr_ship) {
    int choice;
    bool running = true;

    do {
        int n = 0;
        std::vector<std::string> directory;

        std::cout << "\n--- Shipyard ---" << std::endl;
        
        for (const auto &pair : catalog) {
            n++;
            std::string name = pair.first;
            ShipSpecs specs = pair.second;
            directory.push_back(name);

            std::cout << n << ". Model: " << name << std::endl;
            std::cout << " - Max Fuel Capacity: " << specs.max_fuel << " gallons" << std::endl; 
            std::cout << " - Max Cargo Capacity: " << specs.max_cargo << " slots" << std::endl;

            if (!player.get_ship_status(name)) {
                std::cout << " - Cost: " << specs.cost << " Star Coins" << std::endl << std::endl;
            } else {
                std::cout << " [ Owned ]" << std::endl << std::endl;
            }
        }

        do {
            std::cout << "Which ship would you like to buy/equip? (" << n + 1 << " to exit): ";
            std::cin >> choice;

            if (choice < 1 || choice > n + 1) {
                std::cout << "Please enter a valid option (1 - " << n + 1 << ")" << std::endl;
            }

        } while (choice < 1 || choice > n + 1);

        if (choice == n + 1) {
            running = false;
        } 
        else {
            std::string target_name = directory[choice - 1];
            ShipSpecs target_specs = catalog[target_name];
            const unordered_map<std::string, bool> &registry = player.get_registry()

            // Running transaction validations
            
            // Check A: Is it the ship they are currently flying?
            if (curr_ship.get_type() == target_name) {
                std::cout << "You are already piloting the " << target_name << "!" << std::endl;
            }

            // Check B: If they don't own it yet, can they afford it?
            else if (!registry[target_name] && player.get_credits() < target_specs.cost) {
                std::cout << "Transaction Denied: Insufficient Star Coins." << std::endl;
                std::cout << "Cost: " << target_specs.cost << " | Your Balance: "
                << player.get_credits() << std::endl;
            }

            // Check C: Does their current cargo inventory fit in the new ship?
            else if (player.get_total_item_num() > target_specs.max_cargo) {
                std::cout << "Transaction Denied: Your current inventory (" << player.get_total_item_num() 
                          << " units) will not fit into the " << target_name << "'s smaller cargo hold (" 
                          << target_specs.max_cargo << " slots)!" << std::endl;
                std::cout << "Please sell some cargo before switching ships." << std::endl;
            }

            // Processing the purchase/swap if all checks passed
            else {
                if (!registry[target_name]) {
                    player.remove_credits(target_specs.cost);
                    player.unlock_ship(target_name); 
                    std::cout << "Purchased a license for the " << target_name << "!" << std::endl;
                }
                else {
                    std::cout << "Swapped to your owned " << target_name << std::endl;
                }

                curr_ship = Ship(target_name, target_specs.max_fuel, target_specs.max_cargo);
                
                if (player.get_fuel() > target_specs.max_fuel) {
                    player.remove_fuel(player.get_fuel() - target_specs.max_fuel);
                    std::cout << "Excess fuel was siphoned away to fit the new tank size." << std::endl;
                }
                
                running = false;
            }
        }

    } while (running);
}