import { PLANETS } from './data/planets';
import { PlanetModel } from './models/Planet';
import { PlayerModel } from './models/Player';
import { ShipModel } from './models/Ship';
import { RandomSystem } from './systems/RandomSystem';

export type ShipRegistry = Record<string, boolean>;

export interface PlayerState {
  name: string;
  credits: number;
  fuel: number;
  inventory: {
    iron: number;
    water: number;
  };
  shipRegistry: ShipRegistry;
}

export interface ShipState {
  type: string;
  maxFuel: number;
  maxCargo: number;
  damageCost: number;
}

export interface PlanetState {
  index: number;
  name: string;
  prices: {
    iron: number;
    water: number;
    fuel: number;
  };
}

export interface GameState {
  player: PlayerModel;
  ship: ShipModel;
  planets: PlanetModel[];
  currentPlanetIdx: number;
}

export function createInitialGameState(playerName = 'Player', random = new RandomSystem()): GameState {
  return {
    player: new PlayerModel(playerName),
    ship: new ShipModel(),
    planets: PLANETS.map((planet) => PlanetModel.create(planet.index, planet.name, random)),
    currentPlanetIdx: 0
  };
}
