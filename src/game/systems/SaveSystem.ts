import { createInitialGameState, type GameState } from '../GameState';
import { ShipyardModel } from '../models/Shipyard';

export const SAVE_KEY = 'galactic-trader-save-v1';

export interface SaveData {
  version: 1;
  playerName: string;
  credits: number;
  fuel: number;
  iron: number;
  water: number;
  shipType: string;
  currentPlanetIdx: number;
  shipRegistry: Record<string, boolean>;
  shipMaxCargo: number;
  shipDamageCost: number;
}

export class SaveSystem {
  hasSave(): boolean {
    return localStorage.getItem(SAVE_KEY) !== null;
  }

  save(state: GameState): void {
    localStorage.setItem(SAVE_KEY, JSON.stringify(this.serialize(state)));
  }

  load(): GameState | null {
    const raw = localStorage.getItem(SAVE_KEY);
    if (!raw) {
      return null;
    }

    try {
      const data = JSON.parse(raw) as SaveData;
      return this.deserialize(data);
    } catch {
      return null;
    }
  }

  clear(): void {
    localStorage.removeItem(SAVE_KEY);
  }

  serialize(state: GameState): SaveData {
    return {
      version: 1,
      playerName: state.player.name,
      credits: state.player.getCredits(),
      fuel: state.player.getFuel(),
      iron: state.player.getItem(0),
      water: state.player.getItem(1),
      shipType: state.ship.getType(),
      currentPlanetIdx: state.currentPlanetIdx,
      shipRegistry: state.player.getRegistry(),
      shipMaxCargo: state.ship.getMaxCargo(),
      shipDamageCost: state.ship.getDamageCost()
    };
  }

  deserialize(data: SaveData): GameState {
    const shipyard = new ShipyardModel();
    const state = createInitialGameState(data.playerName);
    state.player.setCredits(data.credits);
    state.player.setFuel(data.fuel);
    state.player.setItem(0, data.iron);
    state.player.setItem(1, data.water);
    Object.entries(data.shipRegistry).forEach(([shipName, owned]) => {
      state.player.setShipOwned(shipName, owned);
    });
    state.ship = shipyard.getShipBlueprint(data.shipType);
    state.ship.setMaxCargo(data.shipMaxCargo);
    state.ship.setDamageCost(data.shipDamageCost);
    state.currentPlanetIdx = data.currentPlanetIdx;

    return state;
  }
}
