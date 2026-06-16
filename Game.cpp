// Game.cpp

#include "Game.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <random>
#include <cmath>

// Procedure to run game
void Game::run(){
    int user_choice;
    int fuel_cost;
    bool running = true;

    std::random_device rd;
    std::mt19937 engine(rd());

    // Initialising if the the save state doesn't load
    if (!load_game()){
        initialise();
    }

    else {
        std::cout << "Resuming orbit around " << planets[curr_planet_idx].name << "..." << std::endl;
        market_menu(curr_planet_idx); 
    }
   
    while(running){
        if(player.get_credits() == 0 && player.get_total_item_num() == 0 && player.get_fuel() == 0){
            std::cout << "--- GAME OVER ---" << std::endl;
            std::cout << "You are stranded in the dark void of space with 0 credits, no cargo, and an empty fuel tank." << std::endl;
            running = false;
            break;
        }

        player.display_stats();
        user_choice = travel_menu();

        if (user_choice == 6){
            save_game();
            continue;
        }

        if (user_choice == 7) {
            save_game();
            std::cout << "Exiting game..." << std::endl;
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
        check_random_encounter(engine);
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

// Procedure to save game
void save_game(){
    std::ofstream save_file("save_file.txt");

    if(!save_file.is_open()){
        std::cout << "ERROR: Could not save file" << std::endl;
        return;
    }

    // Saving data
    save_file << player_name << std::endl;
    save_file << player.get_credits() << std::endl;
    save_file << player.get_fuel() << std::endl;
    save_file << player.get_item(0) << std::endl;
    save_file << player.get_item(1) << std::endl;
    save_file << ship.get_type() << std::endl;
    save_file << curr_planet_idx << std::endl;

    const unordered_map<std::string, bool> &registry = player.get_registry();

    save_file << registry.size() << std::endl;

    // Saving status of ships (bought/not bought)
    for(const auto &pair: registry){
        save_file << pair.first << "," << pair.second << std::endl;
    }

    save_file.close();
    std::cout << "Game progress saved successfully!" << std::endl;
}

bool load_game(){
    std::ifstream saved_file("save_file.txt");

    if(!saved_file.is_open()){
        return false;
    }

    int saved_credits, saved_fuel, saved_iron, saved_water, saved_planet, n_ships;
    std::string saved_name, saved_ship;

    std::getline(saved_file >> std::ws, saved_name);
    saved_file >> saved_credits >> saved_fuel >> saved_iron >> saved_water;
    saved_file.ignore();

    std::getline(saved_file, saved_ship);
    saved_file >> saved_planet >> n_ships;

    for (int i = 0; i < n_ships; i++){
        bool is_owned;
        std::string name;

        std::getline(saved_file >> std::ws, name, ',');
        saved_file >> is_owned;

        if (is_owned){
            player.unlock_ship(name);
        }

    }

    player.set_name(saved_name);
    player.set_fuel(saved_fuel);
    player.set_credits(saved_credits);
    player.set_item(0, saved_iron);
    player.set_item(1, saved_water);
    curr_planet_idx = saved_planet;
    ship = shipyard.get_ship_blueprint(saved_ship);

    std::cout << "Successfully loaded file! Welcome back, Captain " << saved_name << "!" << std::endl;

    saved_file.close();
    return true;
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

    std::cout << "6. Save Progress" << std::endl;
    std::cout << "7. Quit Game" << std::endl;

    do{
        std::cout << "Where would you like to travel to? (1 - 7): ";
        std::cin >> choice;

        if(choice < 1 || choice > 7){
            std::cout << "Please enter an option from (1 - 7)" << std::endl; 
        }

    } while(choice < 1 || choice > 7);

    return choice - 1;
}

// Procedure to check random encounter
void Game::check_random_encounter(std::mt19937 &eng){
    std::uniform_int_distribution<int> prob_dist(1, 100);
    int encounter_roll = prob_dist(eng);

    if (encounter_roll <= 65){
        std::cout << "The hyperspace jump was quiet. You arrive safely at your destination." << std::endl;
        return
    }

    else {
        encounter_roll = prob_dist(eng);
        std::cout << "ALERT: Hyperspace drop-out detected! An anomaly has occurred mid-transit!" << std::endl;

        if (event_roll <= 40) { // 1 to 40 (40% chance)
            std::cout << "[EVENT]: SPACE DEBRIS COLLISION!" << std::endl;
            handle_debris(engine);
        } 
        else if (event_roll <= 75) { // 41 to 75 (35% chance)
            std::cout << "[EVENT]: SOLAR FLARE RADIATION!" << std::endl;
            handle_solar_flare(engine);
        } 
        else if (event_roll <= 90) { // 76 to 90 (15% chance)
            std::cout << "[EVENT]: DERELICT CARGO SALVAGE POOL!" << std::endl;
            handle_salvage(engine);
        } 
        else if (event_roll <= 98) { // 91 to 98 (8% chance)
            std::cout << "[EVENT]: SPACE PIRATE AMBUSH!" << std::endl;
            handle_pirate_event(engine);
        } 
        else { // 99 to 100 (2% chance)
            std::cout << "[EVENT]: WANDERING ALIEN MERCHANT!" << std::endl;
            handle_alien_merchant(engine);
        }
    }

}

// DECREASE CARGO AMOUNT AND ALLOW TO PAY LATER AT SHIPYARD
void Game::handle_debris(){
    std::cout << "\nCLANG!" << std::endl;
    std::cout << "Minor structural damage has occured to your hull" << std::endl;

    std::uniform_int_dist<int> repair_dist(10, 1.5 * player.get_credits());
    int repair_cost = repair_dist(eng);

    if (player.get_credits() < repair_cost) {
        std::cout << "[CRITICAL]: You don't have enough Star Coins to pay for repairs"  << std::endl;

        if (player.get_credits() > 0) {
            std::uniform_int_dist<> inv_lost_dist(5, 20);

            std::cout << "You paid the " << player.get_credits() << " Star Coins you had to repair what you can" << std::endl;
            repair_cost -= player.get_credits();
            player.remove_credits(player.get_credits());
        }

        else {
            std::cout << "You don't have any Star Coins to pay for repairs!" << std::endl;
            std::uniform_int_dist<> inv_lost_dist(20, 60);
        }

        double inv_lost_modifier = item_lost_dist(eng)/100;
        int slots_lost = static_cast<int>(inv_lost_modifier * player.get_item(item_idx));
        std::uniform_int_dist<int> iron_lost_dist(0, slots_lost);
        int iron_lost = iron_lost_dist(eng);
        int water_lost = slots_lost - iron_lost;

        std::cout << "Cargo Loss breakdown:" << std::endl;
        std::cout << "   - " << slots_lost << " slots of cargo on your spaceship" << std::endl;
        ship.del_cargo_slots(slots_lost);
        std::cout << "     " << ship.get_max_cargo() << " slots left" << std::endl;
        if (iron_lost > 0) std::cout << "   - " << iron_lost << " units of pure Iron Ore" << std::endl;
        if (water_lost > 0) std::cout << "   - " << water_lost << " units of  Water Cargo" << std::endl;
        std::cout << "Your inventory has been automatically updated." << std::endl;

        player.remove_item(0, iron_lost);
        player.remove_item(1, water_lost);

        ship.set_damage_cost(repair_cost);
        std::cout << "\nGo to a mechanic at the Shipyard to fully repair your hull and restore the original number of slots" << std::endl;

    }

    else {
        std::cout << "You paid " << repair_cost << " Star Coins for immediate hull repairs" << std::endl;
        player.remove_credits(repair_cost);
    }

}

// Procedure for encountering a solar flare
void Game::handle_solar_flare(std::mt19937 &eng){
    std::cout << "\nThe control planels flicker wildly" << std::endl;
    std::cout << "An emergency ventilaton sequency was activated" << std::endl;

    std::uniform_int_distribution<int> fuel_burn_dist(10, 25);
    int lost_fuel = fuel_burn_dist(eng);
    player.remove_fuel(lost_fuel);

    std::cout << "The solar flare leached " << lost_fuel << " units of fuel!" << std::endl;
}

// Procedure for encountering derelict salvage
void Game::handle_salvage(std::mt19937 &eng){
    int choice;
    DERELICT_FUEL = 5;

    do {
        std::cout << "Your sensors pick up an abandoned corporate freighter drifting near an asteroid field." << std::endl;
        std::cout << "1. Investigate (Costs 5 units of fuel to match velocities and dock)" << std::endl;
        std::cout << "2. Fly Past (Proceed safely to your destination)" << std::endl;
        std::cout << "Choose an action: "; 

        std::cin >> choice;

        if (choice < 1 || choice > 2) {
            std::cout << "Please enter a valid choice (1-2)" << std::endl;
        }

    } while (choice < 1 || choice > 2);

    if (choice != 1) {
        std::cout << "Safe choice, Captain. You leave the derelict behind and jump away." << std::endl;
    }

    else {
        if (player.get_fuel() < DERELICT_FUEL) {
            std::cout << "Insufficient fuel to safely maneuver around the asteroid field!" << std::endl;
            std::cout << "You are forced to fly past." << std::endl;
        }

        else {
            std::cout << "Used up " << DERELICT_FUEL << " gallons of fuel to reach derelict" << std::endl;
            player.remove_fuel(DERELICT_FUEL);

            std::uniform_int_dist<int> success_dist(4, 5);
            if (success <= 4) {

                int max_cargo = ship.get_max_cargo(); 
                int current_cargo = player.get_total_item_num();
                int empty_space = max_cargo - current_cargo;

                if (empty_space <= 0) {
                    std::cout << "You successfully board the ship and find crates of supplies, but your hold is completely full! You can't carry any of it back." << std::endl;
                }

                else {
                    std::uniform_int_dist<> percent_dist(20, 50);
                    double salvage_modifier = percent_dist(eng) / 100;
                    
                    int units_found = static_cast<int>(empty_space * salvage_modifier);
                    if (units_found < 1) {
                        units_found = 1;
                    }

                    std::uniform_int_dist<int> iron_found_dist(0, units_found);
                    int iron_found = iron_found_dist(eng);
                    int water_found = units_found - iron_found;

                    std::cout << "SUCCESS! You cracked open the vault. Salvage breakdown:" 
                    << std::endl;
                    if (iron_found > 0) std::cout << "   + " << iron_found
                    << " units of pure Iron Ore" << std::endl;
                    if (water_found > 0) std::cout << "   + "
                    << water_found << " units of Vaporized Water Cargo" << std::endl;
                    std::cout << "Your inventory has been automatically updated."
                    << std::endl;

                    player.add_item(0, iron_found);
                    player.add_item(1, water_found);

                }
            }

            else {
                std::uniform_int_dist<int> repair_dist(60, 1.1 * player.get_credits());
                int repair_cost = repair_dist(eng);

                std::cout << "[DISASTER]: As you attempt to board, a loose bulkhead collapses into your hull." << std::endl;
                std::cout << "You are forced to make emergency repairs costing " << repair_cost
                << " Star Coins." << std::endl;

                if (player.get_credits() < repair_cost) {
                    std::cout << "[CRITICAL]: You don't have enough Star Coins to pay for repairs"
                    << std::endl;

                    if (player.get_credits() > 0) {
                        std::uniform_int_dist<> item_lost_dist(5, 30);

                        std::cout << "You paid the " << player.get_credits() << " Star Coins you had to repair what you can" << std::endl;
                        player.remove_credits(player.get_credits());
                    }

                    else {
                        std::cout << "You don't have any Star Coins to pay for repairs!" << std::endl;
                        std::uniform_int_dist<> item_lost_dist(30, 70);
                    }

                    std::uniform_int_dist<int> idx_dist(0, 1);

                    int item_idx = idx_dist(eng);
                    double item_lost_modifier = item_lost_dist(eng)/100;
                    int num_lost = static_cast<int>(item_lost_modifier * player.get_item(item_idx));

                    if (item_idx == 0) std::cout << "You lost " << num_lost << " units of Iron blocks" << std::endl;
                    if (item_idx == 1) std::cout << "You lost " << num_lost << " gallons of Water" << std::endl;

                    player.remove_item(item_idx, num_lost);
                }

                else {
                    player.remove_credits(repair_cost);
                    std::cout << "You paid " << repair_cost
                    << " credits for immediate hull repairs." << std::endl;
                }
            }
        }
    }
}

// Procedure for encountering space pirates
void Game::handle_pirate_event(std::mt19937 &eng){
    int choice;

    std::cout << "ALARM! Warning lights flash crimson as an armed Interceptor violently pulls you out of warp!" << std::endl;
    std::cout << "A heavy skull-and-crossbones insignia is painted across its black hull. Weapons locked onto your bridge." << std::endl;
    std::cout << "\n[RADIO TRANSMISSION INTERCEPTED]..." << std::endl;
    
    //  Generate dynamic, character-rich pirate dialogue based on the player's active ship
    
    std::cout << "=========================================================================" << std::endl;
    std::cout << "PIRATE CAPTAIN BRYNN: 'Well, well, look what the solar winds dragged in! '" << std::endl;
    
    if (ship.get_type() == "Rusty Scout") {
        std::cout << "'Flying a pathetic little \"" << active_ship_name << "\", are we? That absolute piece of junk ' " << std::endl;
        std::cout << "'is barely worth the plasma it takes to vaporize it. But I bet your wallet is heavier than your hull!'" << std::endl;
    } 

    else if (ship.get_type()  == "Cargo Hauler") {
        std::cout << "'A fat, slow \"" << active_ship_name << "\". Beautiful! Your holds must be absolutely bursting ' " << std::endl;
        std::cout << "'with expensive trade goods. Today is our lucky day, boys!'" << std::endl;
    } 

    else if (ship.get_type()  == "Falcon Scout") {
        std::cout << "'Think you're slick running a fast \"" << active_ship_name << "\"? You can't outrun a missile lock, ' " << std::endl;
        std::cout << "'hotshot. Turn off your engines before we peel your hull back like a tin can!'" << std::endl;
    } 

    else {
        std::cout << "'Hand over the goods, traveler, or your ship becomes our next floating salvage yard!'" << std::endl;
    }

    // Determining the demand amount between the flat toll and calculated percentage toll
    FLAT_TOLL = 200;
    int percentage_toll = static_cast<int>(player.get_credits() * 0.20);
    int demand_amount = percentage_toll > FLAT_TOIL ? percentage_toll : FLAT_TOLL;

    std::cout << "\n'Here's the deal: transfer over " << demand_amount << " Star Coins as a \"transit tax\", ' " << std::endl;
    std::cout << "'and we let you jump away in one piece. Refuse... and we take it off your cold, floating body.'" << std::endl;
    std::cout << "=========================================================================" << std::endl;
    
    // Present user choices
    do {
        std::cout << "What will you do?" << std::endl;
        std::cout << "1. Pay the toll (" << demand_amout <<" Star Coins)" << std::endl;
        std::cout << "2. Slam the Thrusters and Flee! (50% Chance of escape / 50% Chance of getting blasted)" << std::endl;
        std::cout << "Your choice: " << std::endl;
        std::cin >> choice;

        if(choice < 1 || choice > 2){
            std::cout << "Please enter a valid choice" << std::endl;
        }

    } while (choice < 1 || choice > 2);

    // Option 1: Pay the tax
    if (choice == 1) {

    }

    // Option 2: Attempt to flee
    else {
        std::cout << "\nYou slam the hyperspace hyper-drive override lever!" << std::endl;
        std::cout << "The engines roar to life as you attempt to outmaneuver their targeting computers..."
        << std::endl;       
        
        std::uniform_int_distribution<int> escape_dist(1, 2);
        int escape_roll = escape_dist(engine);

        if (escape_roll == 1) {
            std::cout << "FLUSH ESCAPE! Your ship skews sideways, dodging their plasma fire, and successfully jumps into hyperspace!" << std::endl;
            std::cout << "You left them eating your cosmic dust." << std::endl;
        }
        else {
            std::cout << "THWACK! A heavy missile scores a direct hit against your cargo stabilizers right before you warp out!" << std::endl;
            
            int iron_lost = player.get_item(0) / 2;
            int water_lost = player.get_item(1) / 2;
            player.remove_item(0, iron_lost);
            player.remove_item(1, water_lost);

            std::cout << "As you jump, you see your storage modules rupture on the external cameras." << std::endl;
            std::cout << "Loss Report: -" << iron_lost << " units of Iron Ore, -"
            << water_lost << " units of Vaporized Water." << std::endl;
        }
    }
}

void handle_alien_merchant(){
    int choice;
    int gallons;
    int cost;

    std::cout << "[RADIO FREQUENCY OVERRIDE]" << std::endl;
    std::cout << "A strange, melodic sequence of chimes echoes through your cockpit speakers." << std::endl; 
    std::cout << "A highly modification-heavy, brass-plated starship with glowing neon thrusters drifts into view, flashing a peaceful blue greeting beacon." << std::endl; 

    std::cout << "\n=========================================================================" << std::endl;
    std::cout << "WANDERING MERCHANT XYLAR: 'Utinni! Greetings, fleshy biological carbon-form!" << std::endl;
    std::cout << "I am Xylar, purveyor of cosmic rarities and scrap-metal anomalies!" << std::endl;
    std::cout << "My sensors detect you are currently piloting a fine platform—yes, yes, a grand platform indeed!" << std::endl;
    std::cout << "You look like a traveler with taste... or a wallet desperate for a miracle.'" << std::endl;
    std::cout << "=========================================================================" << std::endl;

    std::cout << "\nWell, I'll give you two options Captain..." << std::endl;

    if (player.get_total_item_num() == 0) {
        std::cout << "'Wait... my scanners show your cargo bays are completely empty! You come to" << std::endl;
        std::cout << "Xylar with nothing to trade? Space is a cold place to drift, traveler." << std::endl;
        std::cout << "Come back when you actually have some goods on board!'" << std::endl;
    }

    else {

        do {
        std::cout << "\n1. 'My manufacturing injectors are running dry!" << std::endl;
        std::cout << "I'll buy every unit of Iron and Water in your hold right now for DOUBLE the maximum market rate." << std::endl;
        std::cout << "No tariffs, no questions.'" << std::endl;

        std::cout << "\n But..." << std::endl;

        std::cout << "2. \nI also tapped an antimatter hydrogen pocket and will fill your tanks right now" << std::endl;
        std::cout << "for a mere 2 credits per gallon. A legendary bargain!" << std::endl;

        std::cout << "What do you say? ";

        std::cin >> choice;

        } while (choice < 1 || choice > 2);

        std::cout << "Great choice Captain!" << std::endl;

        if (choice == 1) {
            std::cout << "Transferring " << player.get_item(0), << " units of Iron Ore and "
            player.get_item(1) << " units of Water to Xylar..." << std::endl;

            // Calculating number of star coins to earn and setting iron and water quantities to 0
            int amount = 2 * (player.get_item(0) * 120 + player.get_item(1) * 80);
            player.set_item(0, 0);
            player.set_item(1, 0);

            std::cout << "Earned " << amount << " Star Coins!" << std::endl;
            std::cout << "Total Star Coins: " << player.get_credits() << std::endl;
        }

        else {
            do {
                std::cout << "How many gallons of fuel would you like? ";
                std::cin >> gallons;

                if (player.get_fuel() + gallons > ship.get_max_fuel();) {
                    std::cout << "Oops! You only have " << ship.get_max_fuel() - player.get_fuel() << " empty gallons of fuel left in your tank." << std::endl;
                    std::cout << "Try again." << std::endl;
                }

                int cost = 2 * gallons;

                if (player.get_credits() - cost < 0) {
                    std::cout << "Oops! You only have " << player.get_creditsl() << " Star Coins." << std::endl;
                    std::cout << "You need " cost - player.get_credits() << " more Star Coins to complete the transaction." << std::endl;
                    std::cout << "Try again and buy fewer gallons of fuel next time." << std::endl;
                }

            } while (player.get_fuel() + gallons > ship.get_max_fuel() || player.get_credits() - cost < 0;);

            std::cout << "Payment of " << cost << " Star Coins complete." << std::endl;
            std::cout << "Refilled " << gallons << " of fuel" << std::endl;

            player.remove_credits(cost);
            player.add_fuel(gallons);
        }

        std::cout << "'\nA pleasure, Captain! May your hyper-drives never stall and your profits stay high!'" << std::endl;
        std::cout << "The neon ship spins and vanishes into a wormhole." << std::endl;
    }
}