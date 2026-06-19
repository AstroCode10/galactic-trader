// Shipyard.cpp

#include "Shipyard.h"
#include <iostream>
#include <vector>

Shipyard::Shipyard() {
    catalog["Rusty Scout"] = {100, 20, 0};
    catalog["Cargo Hauler"] = {80, 60, 400};
    catalog["Falcon Scout"] = {250, 15, 600};
}

Ship Shipyard::get_ship_blueprint(std::string ship_name) {
    if (catalog.find(ship_name) != catalog.end()) {
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

        do {
            std::cout << "\nWhat would you like to do?" << std::endl;
            std::cout << "1. Buy a Ship" << std::endl;
            std::cout << "2. Repair a Ship" << std::endl;
            std::cout << "Enter choice: ";
            std::cin >> choice;

            if (choice < 1 || choice > 2) {
                std::cout << "Please enter a valid option (1 - 2)" << std::endl;
            }

        } while (choice < 1 || choice > 2);

        if (choice == 1) {
            const std::unordered_map<std::string, bool> &registry = player.get_registry();

            for (const auto &pair : catalog) {
                n++;
                std::string name = pair.first;
                ShipSpecs specs = pair.second;
                directory.push_back(name);

                std::cout << n << ". Model: " << name << std::endl;
                std::cout << " - Max Fuel Capacity: " << specs.max_fuel << " gallons" << std::endl;
                std::cout << " - Max Cargo Capacity: " << specs.max_cargo << " slots" << std::endl;

                if (!registry.at(name)) {
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
            } else {
                std::string target_name = directory[choice - 1];
                ShipSpecs target_specs = catalog[target_name];

                if (curr_ship.get_type() == target_name) {
                    std::cout << "You are already piloting the " << target_name << "!" << std::endl;
                } else if (!registry.at(target_name) && player.get_credits() < target_specs.cost) {
                    std::cout << "Transaction Denied: Insufficient Star Coins." << std::endl;
                    std::cout << "Cost: " << target_specs.cost << " | Your Balance: "
                              << player.get_credits() << std::endl;
                } else if (player.get_total_item_num() > target_specs.max_cargo) {
                    std::cout << "Transaction Denied: Your current inventory (" << player.get_total_item_num()
                              << " units) will not fit into the " << target_name << "'s smaller cargo hold ("
                              << target_specs.max_cargo << " slots)!" << std::endl;
                    std::cout << "Please sell some cargo before switching ships." << std::endl;
                } else {
                    if (!registry.at(target_name)) {
                        player.remove_credits(target_specs.cost);
                        player.unlock_ship(target_name);
                        std::cout << "Purchased a license for the " << target_name << "!" << std::endl;
                    } else {
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
        } else {
            if (curr_ship.get_damage_cost() == 0) {
                std::cout << "Your ship does not need repairs." << std::endl;
                running = false;
            } else if (player.get_credits() >= curr_ship.get_damage_cost()) {
                repair_ship(player, curr_ship);
                running = false;
            } else {
                std::cout << "Cannot repair ship" << std::endl;
                std::cout << "You only have " << player.get_credits() << " Star Coins" << std::endl;
                std::cout << "You need " << curr_ship.get_damage_cost() - player.get_credits()
                          << " more credits to repair the ship." << std::endl;
                running = false;
            }
        }

    } while (running);
}

void Shipyard::repair_ship(Player &player, Ship &curr_ship) {
    std::cout << "Success! Completely fixed hull for " << curr_ship.get_damage_cost()
              << " Star Coins." << std::endl;
    player.remove_credits(curr_ship.get_damage_cost());
    curr_ship.set_damage_cost(0);
    curr_ship.set_max_cargo(catalog[curr_ship.get_type()].max_cargo);
}
