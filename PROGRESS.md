# Galactic Trader - Web Port Progress

## Current Phase
Phase 2 - Full mechanic parity

## Status Summary
Phase 1 is implemented and passes `npm.cmd run build`. The browser game now has title/new/continue flow, localStorage save/load, clickable index-ordered star map travel, price refresh on jumps, docked market buy/sell controls, HUD updates, saved indicator, and game-over routing.

## Completed
- Read `.cursor/plans/game-implementation.plan.md` in full and confirmed the required Phase 0 -> 1 -> 2 -> 3 -> 4 build order.
- Read root `README.md` and confirmed the C++ console game feature set and source-file layout.
- Created `PROGRESS.md` as the persistent handoff file for this port.
- Moved original C++ sources into `cpp/`: `main.cpp`, `Game.cpp/.h`, `Player.cpp/.h`, `Planet.cpp/.h`, `Ship.cpp/.h`, and `Shipyard.cpp/.h`.
- Moved the original console README to `cpp/README-cpp.md`.
- Added Vite/TypeScript/Phaser scaffold files: `package.json`, `tsconfig.json`, `vite.config.ts`, `index.html`, `src/vite-env.d.ts`, and a new root `README.md`.
- Added responsive Phaser bootstrap in `src/main.ts` with 1280x720 `FIT` scaling and scene registration.
- Added empty scaffold scenes: `BootScene`, `PreloadScene`, `TitleScene`, `StarMapScene`, `TravelScene`, and `GameOverScene`.
- Added planned folder placeholders for `src/ui`, `src/entities`, `src/sdk`, `src/utils`, and `public/assets/sprites`.
- Added `src/game/data/planets.ts` with the plan's index-ordered coordinates: Tatooine, Coruscant, Hoth, Endor, Naboo.
- Added `src/game/data/shipCatalog.ts` with exact C++ ship specs: Rusty Scout, Cargo Hauler, Falcon Scout.
- Ported first-pass `PlayerModel` defaults and mutators from `Player.cpp`, including credits, fuel, iron/water inventory, registry, and clamped fuel/item removal.
- Ported first-pass `PlanetModel.randomisePrices()` with exact C++ ranges: Iron 50-120, Water 20-80, Fuel 30-100.
- Ported first-pass `ShipModel` defaults, max fuel/cargo accessors, cargo slot damage, damage cost, and max cargo setters from `Ship.cpp`.
- Ported first-pass `ShipyardModel` catalog lookup, buy/equip validation, fuel siphoning, ownership unlock, and repair behavior from `Shipyard.cpp`.
- Added `TravelSystem` with index-based fuel cost, travel validation, fuel deduction, price refresh, and game-over check.
- Added `TradeSystem` with buy/sell validation for iron, water, and fuel based on C++ market rules.
- Added `SaveSystem` using the planned JSON schema with `shipMaxCargo` and `shipDamageCost` extension fields.
- Updated `GameState` and `GameController` to initialize typed models, randomize initial planets, expose travel/trade/save systems, and save after successful travel.
- Added `GameSession.ts` singleton so Phaser scenes share one `GameController`.
- Added `GameController.buy()`, `GameController.sell()`, `hasSavedState()`, and `clearSavedState()` wrappers with autosave on successful trades.
- Added `SaveSystem.hasSave()` and guarded JSON load parsing.
- Enabled Phaser DOM support in `src/main.ts` and added base page styles in `index.html`.
- Rebuilt `TitleScene` with captain name input, New Game, and Continue backed by `SaveSystem`.
- Rebuilt `StarMapScene` as the Phase 1 playable loop: starfield, adjacent route chain, planet nodes, current-planet dock behavior, destination travel, fuel-cost hover tooltip, HUD, market panel, buy/sell tabs, autosave flash, and feedback text.
- Added `GameOverScene` with stranded message and return-to-title flow that clears save.
- Added `src/utils/format.ts` for readable credit/unit formatting.
- Verified Phase 1 with `npm.cmd run build`; TypeScript and Vite build completed successfully.

## In Progress
- No active implementation in progress. Phase 1 is ready for manual playtesting and Phase 2 can begin next.

## Up Next
- Begin Phase 2 by porting `EncounterSystem` from `Game.cpp`, including safe roll, debris, solar flare, salvage, pirate, and alien merchant behavior.
- Add `TravelScene` animation pipeline and dispatch travel through it instead of resolving instantly in `StarMapScene`.
- Add `EventModal` for salvage, pirate, and alien merchant choices.
- Add `ShipyardPanel` tab for buy/equip/repair using the already ported `ShipyardModel`.

## Decisions Made
- Treat `.cursor/plans/game-implementation.plan.md` as the authoritative plan because the requested extensionless path `.cursor/plans/game-implementation.plan` does not exist.
- Keep Phase 0 focused on scaffold and wiring only; exact gameplay logic ports begin in Phase 1 per the plan.
- Mark Phase 0 file scaffold complete even though build verification is blocked by local disk space, not by known code errors.
- Implement Phase 1 logic modules before visual UI panels so the Phaser scenes can call tested domain methods once dependency verification is available.
- Keep Phase 1 trade UI to fixed quantity buttons (1/5/10) rather than free-form numeric entry; this keeps the core loop playable and avoids fragile text input inside Phaser panels. More granular controls can be improved in Phase 3 polish.
- Resolve Phase 1 travel immediately in `StarMapScene`; `TravelScene` animation and encounter interruption remain Phase 2 work per the plan.

## Known Issues / Open Questions
- Sandboxed shell commands timed out before execution in this environment; escalated PowerShell commands are being used for required file inspection and filesystem operations.
- Browser automation could not be completed because the in-app browser connector failed with a Windows sandbox startup error.
- Dev server launch/check commands became unreliable after background launch attempts; use `npm.cmd run dev -- --host 127.0.0.1 --port 5173` manually if needed. Production build verification succeeded.
- `SaveSystem` currently uses raw `localStorage`; CrazyGames SDK data integration is intentionally deferred to Phase 4.
- Vite reports the expected large chunk warning because Phaser is bundled in one chunk; this is not a Phase 1 blocker.

## Files Touched This Session
- `PROGRESS.md`
- `README.md`
- `package.json`
- `tsconfig.json`
- `vite.config.ts`
- `index.html`
- `cpp/README-cpp.md`
- `cpp/main.cpp`
- `cpp/Game.cpp`
- `cpp/Game.h`
- `cpp/Player.cpp`
- `cpp/Player.h`
- `cpp/Planet.cpp`
- `cpp/Planet.h`
- `cpp/Ship.cpp`
- `cpp/Ship.h`
- `cpp/Shipyard.cpp`
- `cpp/Shipyard.h`
- `src/vite-env.d.ts`
- `src/main.ts`
- `src/game/constants.ts`
- `src/game/GameState.ts`
- `src/game/GameController.ts`
- `src/game/GameSession.ts`
- `src/game/models/Player.ts`
- `src/game/models/Planet.ts`
- `src/game/models/Ship.ts`
- `src/game/models/Shipyard.ts`
- `src/game/systems/RandomSystem.ts`
- `src/game/systems/TravelSystem.ts`
- `src/game/systems/TradeSystem.ts`
- `src/game/systems/SaveSystem.ts`
- `src/utils/format.ts`
- `src/game/data/planets.ts`
- `src/game/data/shipCatalog.ts`
- `src/scenes/BootScene.ts`
- `src/scenes/PreloadScene.ts`
- `src/scenes/TitleScene.ts`
- `src/scenes/StarMapScene.ts`
- `src/scenes/TravelScene.ts`
- `src/scenes/GameOverScene.ts`
- `src/ui/.gitkeep`
- `src/entities/.gitkeep`
- `src/sdk/.gitkeep`
- `src/utils/.gitkeep`
- `public/assets/sprites/.gitkeep`
