import { createInitialGameState, type GameState } from './GameState';
import { SaveSystem } from './systems/SaveSystem';
import type { BuyResource, SellResource, TradeResult } from './systems/TradeSystem';
import { TradeSystem } from './systems/TradeSystem';
import { TravelSystem } from './systems/TravelSystem';

export class GameController {
  private state: GameState = createInitialGameState();
  readonly travel = new TravelSystem();
  readonly trade = new TradeSystem();
  readonly save = new SaveSystem();

  initialise(playerName: string): GameState {
    this.state = createInitialGameState(playerName);
    this.save.save(this.state);
    return this.state;
  }

  getState(): GameState {
    return this.state;
  }

  loadSavedState(): boolean {
    const loaded = this.save.load();
    if (!loaded) {
      return false;
    }

    this.state = loaded;
    return true;
  }

  requestTravel(toIndex: number): { ok: boolean; fuelCost: number; message: string } {
    const result = this.travel.travel(this.state, toIndex);
    if (result.ok) {
      this.save.save(this.state);
    }

    return result;
  }

  buy(resource: BuyResource, amount: number): TradeResult {
    const result = this.trade.buy(this.state, resource, amount);
    if (result.ok) {
      this.save.save(this.state);
    }

    return result;
  }

  sell(resource: SellResource, amount: number): TradeResult {
    const result = this.trade.sell(this.state, resource, amount);
    if (result.ok) {
      this.save.save(this.state);
    }

    return result;
  }

  hasSavedState(): boolean {
    return this.save.hasSave();
  }

  clearSavedState(): void {
    this.save.clear();
  }
}
