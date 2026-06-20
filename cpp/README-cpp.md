# Galactic Trader

A terminal-based, text-driven space trading simulation built entirely from scratch in modern C++. Command your own starship, navigate a dynamic galaxy with shifting planetary markets, manage crucial resources, purchase goods, and amass a fortune across the stars before running out of fuel or credits.

This project demonstrates foundational software engineering principles including Object-Oriented Programming (OOP), strict data encapsulation, explicit multi-file architecture separation (.h / .cpp configurations), high-performance data structures, and advanced data serialization frameworks.

## Core Features

- **Dynamic Planetary Economies**: Visit 5 unique planets (Tatooine, Coruscant, Hoth, Endor, Naboo), each featuring an isolated commodity pricing matrix for core resources (Iron, Water, Fuel).

- **Algorithmic Price Shifts**: Market prices fluctuate dynamically upon every hyperspace travel sequence using standard uniform integer distributions via the modern `<random>` library engine.

- **Modular Shipyard & Registry Database**: Features a dedicated Shipyard purchasing system driven by a hashed database structure (`std::unordered_map`). Ship blueprints map directly to custom statistic structures (Max Fuel, Max Cargo, Purchase Cost).

- **High-Performance Parallel Index Tracking**: Utilizes temporary sequential index directories (`std::vector`) to map numerical user interface inputs cleanly to text-hashed map keys, ensuring $O(1)$ lookup performance when validating trades.

- **Resource & Hull Validation Matrix**: Travel mechanics track financial balances, cargo load constraints, and fuel line safeguards dynamically. Swapping hulls automatically ensures existing cargo fits the new platform and siphons off overflowing fuel tanks.

- **Dynamic Loop Serialization & Safe File I/O**: Implements an infinitely scalable persistence model via `<fstream>`. The file pipeline records baseline parameters and iterates dynamically through the fleet license registration arrays using explicit string-tokenizing logic separated by targeted delimiters (,).

- **Weighted Threat Matrix & Dynamic Encounters**: Simulates deep-space volatility via an optimized, nested conditional probability engine passed entirely by reference to reduce memory footprints. Mid-transit sequences evaluate multi-tier events including environmental hazards, high-yield derelict salvage operations, interactive pirate ambushes, and ultra-rare wandering alien merchants offering volatile market choices.

## File Architecture

The project maintains a strict separation of concerns, isolating entity data profiles from economic transactional logic loop cycles:

```plaintext
GalacticTrader/
│
├── main.cpp          # Application entry point (initializes and runs Game)
├── Game.h            # Interface blueprint for the core simulation engine
├── Game.cpp          # Execution loop orchestration, navigation, threats, and market logic
├── Player.h          # Definition of Player state, permanent ship licenses, and wallet
├── Player.cpp        # Implementation of player statistics and inventory management
├── Planet.h          # Class definition for local planet configurations
├── Planet.cpp        # Randomized price generators and market display interfaces
├── Ship.h            # Physical attribute definitions for the currently piloted hull
├── Ship.cpp          # Implementation of structural limits (max fuel, max cargo)
├── Shipyard.h        # Blueprint for the global ship database and validation systems
└── Shipyard.cpp      # Catalog parsing, currency transaction checks, and hull swaps
```

## Gameplay Loop

1. **Initialization / Session Restoration**: Upon runtime, the subsystem queries the disk directory for an existing save state configuration. If missing, the game falls back into standard primary sequence triggers. If localized files parse successfully, variables instantly overwrite baseline objects and map out the current planet environment.

2. **Hyperspace Navigation**: Choose an explorable location from the navigation menu. Space coordinates compute relative distances dynamically, extracting precise fuel requirements against active ship capacities.

3. **Mid-Transit Risk Assessment**: Entering warp speeds subjects the crew to the threat matrix. Players must make tactical decisions—paying off pirate tolls, navigating radiation, or running salvage operations. Credit bankruptcy under pressure triggers structural penalties, permanently warping cargo hold walls and shrinking absolute storage capacities.

4. **Market Operations**: Review local commodity sheets. Make purchases based on live currency updates, multiplying quantity constraints safely against private array limits.

5. **Fleet Engineering**: Visit local drydocks to upgrade your hull class. The game verifies transaction feasibility, adjusts cargo transfer weight rules, updates permanent flight ownership licenses, and swaps physical object payloads instantly via reference tracking.

6. **Survival & Termination**: Players must carefully optimize cargo margins. Encountering total economic insolvency (0 Star Coins, empty cargo bays, and 0 operational fuel) triggers an explicit game-over loop termination step. Exiting through standard menu routes safely serializes live states to file before closing memory stacks.

## Getting Started

### Prerequisites
You will need a working C++ compiler supporting at least C++11 or higher (e.g., g++, clang, or MSVC).

### Compilation
Compile all modular components simultaneously from your terminal shell environment:

```bash
g++ -std=c++11 main.cpp Game.cpp Player.cpp Planet.cpp Ship.cpp Shipyard.cpp -o GalacticTrader
```

### Execution
Launch the compiled simulation binary executable:

```bash
./GalacticTrader
```

## Project Roadmap

- [x] **Stage 1 (Foundation)**: Structural multi-file alignment, class design configurations, and loop architectures.
- [x] **Stage 2 (Economy)**: Private resource arrays, automated randomized distributions, and capsule access validation.
- [x] **Stage 3 (Upgrades)**: Implement a dedicated Shipyard system utilizing custom spec structures, hash map registries, and pass-by-reference object transformation mechanics.
- [x] **Stage 4 (Persistence Framework)**: Serializing complex standard maps dynamically, manual delimiter parsing, and stream buffer clearings.
- [x] **Stage 5 (Threat Matrices & Events)**: Mid-transit cosmic interceptors passed by reference, adaptive ship-class scripts, interactive player risk prompts, and alternative credit-insolvency structural damage limits.

## License
This repository is open-source and available under the MIT License. Feel free to clone, modify, and expand upon the code to construct your own custom space modules!
