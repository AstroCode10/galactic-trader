# Galactic Trading Simulator

A terminal-based, text-driven space trading simulation built entirely from scratch in modern C++. Command your own starship, navigate a dynamic galaxy with shifting planetary markets, manage crucial resources, purchase goods, and amass a fortune across the stars before running out of fuel or credits.

This project demonstrates foundational software engineering principles including Object-Oriented Programming (OOP), strict data encapsulation, explicit multi-file architecture separation (.h / .cpp configurations), and structural memory management.

## Core Features

- **Dynamic Planetary Economies**: Visit 5 unique planets (Tatooine, Coruscant, Hoth, Endor, Naboo), each featuring an isolated commodity pricing matrix for core resources (Iron, Water, Fuel).

- **Algorithmic Price Shifts**: Market prices fluctuate dynamically upon every hyperspace travel sequence using standard uniform integer distributions via the modern `<random>` library engine.

- **Resource Management**: Balance your budget (Star Coins) and fuel consumption carefully. Transacting costs are calculated in real time against your player wallet to prevent debt overflows.

- **Data Encapsulation**: System architectures are strictly guarded using private scopes, preventing variable shadowing and unauthorized external manipulation, exposing values safely through clean getter methods.

## File Architecture

The project avoids a "spaghetti nebula" anti-pattern by splitting concerns into dedicated header and source files:

```plaintext
GalacticTrader/
│
├── main.cpp          # Application entry point (initializes and runs Game)
├── Game.h            # Interface blueprint for the core simulation engine
├── Game.cpp          # Execution loop orchestration, menus, and transactions
├── Player.h          # Definition of Player state, wallet, and fuel capacities
├── Player.cpp        # Implementation of player statistics and inventory management
├── Planet.h          # Class definition for market tables and data getters
└── Planet.cpp        # Randomized price generators and display interfaces
```

## Gameplay Loop

1. **Initialization**: Define your captain's name. The game instantiates the sector array, preparing default constructors before applying dynamic profiles.

2. **Hyperspace Navigation**: Choose an explorable location from the navigation menu. Changing space coordinates triggers system alerts and burns fuel reserves.

3. **Market Operations**: Review local commodity sheets. Make purchases based on live currency updates, multiplying quantity constraints safely against private array limits.

4. **Fleet Upgrades**: Reinvest revenue from trade loops to expand storage and optimize hardware systems.

## Getting Started

### Prerequisites
You will need a working C++ compiler supporting at least C++11 or higher (e.g., g++, clang, or MSVC).

### Compilation
Compile all modular components simultaneously from your terminal shell environment:

```bash
g++ -std=c++11 main.cpp Game.cpp Player.cpp Planet.cpp -o GalacticTrader
```

### Execution
Launch the compiled simulation binary executable:

```bash
./GalacticTrader
```

## Project Roadmap

- [x] **Stage 1 (Foundation)**: Structural multi-file alignment, class design configurations, and loop architectures.
- [x] **Stage 2 (Economy)**: Private resource arrays, automated randomized distributions, and capsule access validation.
- [ ] **Stage 3 (Upgrades)**: Implement a dedicated Ship class utilizing classic object inheritance (CargoShip vs. ExplorerShip variants).
- [ ] **Stage 4 (Persistence)**: Serialization mechanics for global save profiles via fstream alongside random encounter matrix events (Pirate raids, cosmic storms).

## License
This repository is open-source and available under the MIT License. Feel free to clone, modify, and expand upon the code to construct your own custom space modules!
