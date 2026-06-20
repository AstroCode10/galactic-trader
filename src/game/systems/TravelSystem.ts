import { BASE_FUEL_COST } from '../constants';
import type { GameState } from '../GameState';

export class TravelSystem {
  calcFuelCost(fromIndex: number, toIndex: number): number {
    return BASE_FUEL_COST * Math.abs(toIndex - fromIndex);
  }

  canTravel(state: GameState, toIndex: number): { ok: boolean; fuelCost: number; message: string } {
    if (toIndex < 0 || toIndex >= state.planets.length) {
      return { ok: false, fuelCost: 0, message: 'Unknown destination.' };
    }

    const fuelCost = this.calcFuelCost(state.currentPlanetIdx, toIndex);
    if (fuelCost > state.player.getFuel()) {
      return {
        ok: false,
        fuelCost,
        message: `Insufficient fuel. Hyperspace jump requires ${fuelCost} units.`
      };
    }

    return { ok: true, fuelCost, message: 'Ready for hyperspace jump.' };
  }

  travel(state: GameState, toIndex: number): { ok: boolean; fuelCost: number; message: string } {
    const validation = this.canTravel(state, toIndex);
    if (!validation.ok) {
      return validation;
    }

    state.player.removeFuel(validation.fuelCost);
    state.currentPlanetIdx = toIndex;
    state.planets.forEach((planet) => planet.randomisePrices());

    return {
      ok: true,
      fuelCost: validation.fuelCost,
      message: `Arriving at ${state.planets[toIndex].name}.`
    };
  }

  isGameOver(state: GameState): boolean {
    return state.player.getCredits() === 0 && state.player.getTotalItemNum() === 0 && state.player.getFuel() === 0;
  }
}
