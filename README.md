# 🚀 Galactic Trading Simulator

A terminal-based, text-driven space trading simulation built entirely from scratch in modern C++. Command your own starship, navigate a dynamic galaxy with shifting planetary markets, manage crucial resources, purchase goods, and amass a fortune across the stars before running out of fuel or credits.

This project demonstrates foundational software engineering principles including Object-Oriented Programming (OOP), strict data encapsulation, explicit multi-file architecture separation (.h / .cpp configurations), and high-performance data structures.

## 🌌 Core Features

- **Dynamic Planetary Economies**: Visit 5 unique planets (Tatooine, Coruscant, Hoth, Endor, Naboo), each featuring an isolated commodity pricing matrix for core resources (Iron, Water, Fuel).

- **Algorithmic Price Shifts**: Market prices fluctuate dynamically upon every hyperspace travel sequence using standard uniform integer distributions via the modern `<random>` library engine.

- **Modular Shipyard & Registry Database**: Features a dedicated Shipyard purchasing system driven by a hashed database structure (`std::unordered_map`). Ship blueprints map directly to custom statistic structures (Max Fuel, Max Cargo, Purchase Cost).

- **High-Performance Parallel Index Tracking**: Utilizes temporary sequential index directories (`std::vector`) to map numerical user interface inputs cleanly to text-hashed map keys, ensuring $O(1)$ lookup performance when validating trades.

- **Resource & Hull Validation Matrix**: Travel mechanics track financial balances, cargo load constraints, and fuel line safeguards dynamically. Swapping hulls automatically ensures existing cargo fits the new platform and siphons off overflowing fuel tanks.

## 🛠️ File Architecture

The project maintains a strict separation of concerns, isolating entity data profiles from economic transactional logic loop cycles:

```plaintext
GalacticTrader/
│
├── main.cpp          # Application entry point (initializes and runs Game)
├── Game.h            # Interface blueprint for the core simulation engine
├── Game.cpp          # Execution loop orchestration, navigation, and market logic
├── Player.h          # Definition of Player state, permanent ship licenses, and wallet
├── Player.cpp        # Implementation of player statistics and inventory management
├── Planet.h          # Class definition for local planet configurations
├── Planet.cpp        # Randomized price generators and market display interfaces
├── Ship.h            # Physical attribute definitions for the currently piloted hull
├── Ship.cpp          # Implementation of structural limits (max fuel, max cargo)
├── Shipyard.h        # Blueprint for the global ship database and validation systems
└── Shipyard.cpp      # Catalog parsing, currency transaction checks, and hull swaps
```

## 🎮 Gameplay Loop

1. **Initialization**: Define your captain's name. The game instantiates the player, defaults the starter ship configuration, and populates the cosmic marketplace.

2. **Hyperspace Navigation**: Choose an explorable location from the navigation menu. Space coordinates compute relative distances dynamically, extracting precise fuel requirements against active ship capacities.

3. **Market Operations**: Review local commodity sheets. Make purchases based on live currency updates, multiplying quantity constraints safely against private array limits.

4. **Fleet Engineering**: Visit local drydocks to upgrade your hull class. The game verifies transaction feasibility, adjusts cargo transfer weight rules, updates permanent flight ownership licenses, and swaps physical object payloads instantly via reference tracking.

5. **Survival & Victory Parameters**: Maintain active trade loops to avoid total economic insolvency. Running completely out of operational capital, fuel reserves, and cargo arrays triggers a definitive terminal soft-lock game-over loop.

## 💻 Getting Started

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

## 🗺️ Project Roadmap

- [x] **Stage 1 (Foundation)**: Structural multi-file alignment, class design configurations, and loop architectures.
- [x] **Stage 2 (Economy)**: Private resource arrays, automated randomized distributions, and capsule access validation.
- [x] **Stage 3 (Upgrades)**: Implement a dedicated Shipyard system utilizing custom spec structures, hash map registries, and pass-by-reference object transformation mechanics.
- [ ] **Stage 4 (Persistence & Threat Matrices)**: Serialization mechanics for global save profiles via fstream alongside random encounter matrix events (Pirate raids, cosmic storms, hull breaches).

## 📄 License
This repository is open-source and available under the MIT License. Feel free to clone, modify, and expand upon the code to construct your own custom space modules!
