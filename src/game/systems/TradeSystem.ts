import type { GameState } from '../GameState';

export type BuyResource = 'iron' | 'water' | 'fuel';
export type SellResource = 'iron' | 'water';

export type TradeResult =
  | { ok: true; message: string; total: number }
  | { ok: false; message: string; total: number };

const BUY_INDEX: Record<BuyResource, 0 | 1 | 2> = {
  iron: 0,
  water: 1,
  fuel: 2
};

const SELL_INDEX: Record<SellResource, 0 | 1> = {
  iron: 0,
  water: 1
};

export class TradeSystem {
  buy(state: GameState, resource: BuyResource, amount: number): TradeResult {
    if (amount <= 0) {
      return { ok: false, message: 'Please enter a positive number.', total: 0 };
    }

    const planet = state.planets[state.currentPlanetIdx];
    const priceIndex = BUY_INDEX[resource];
    const total = amount * planet.getPrice(priceIndex);

    if (total > state.player.getCredits()) {
      return { ok: false, message: 'Sorry you cannot make the purchase.', total };
    }

    if (resource !== 'fuel' && state.player.getTotalItemNum() + amount > state.ship.getMaxCargo()) {
      return { ok: false, message: `Ship cargo limit is ${state.ship.getMaxCargo()}.`, total };
    }

    if (resource === 'fuel' && state.player.getFuel() + amount > state.ship.getMaxFuel()) {
      return { ok: false, message: `Ship fuel capacity is ${state.ship.getMaxFuel()}.`, total };
    }

    state.player.removeCredits(total);
    if (resource === 'fuel') {
      state.player.addFuel(amount);
    } else {
      const itemIndex = resource === 'iron' ? 0 : 1;
      state.player.addItem(itemIndex, amount);
    }

    return { ok: true, message: `Payment of ${total} Star Coins successful.`, total };
  }

  sell(state: GameState, resource: SellResource, amount: number): TradeResult {
    if (amount <= 0) {
      return { ok: false, message: 'Please enter a positive number.', total: 0 };
    }

    const itemIndex = SELL_INDEX[resource];
    if (state.player.getInventory(itemIndex) < amount) {
      return { ok: false, message: 'Not enough units in inventory.', total: 0 };
    }

    const planet = state.planets[state.currentPlanetIdx];
    const total = amount * planet.getPrice(itemIndex);
    state.player.removeItem(itemIndex, amount);
    state.player.addCredits(total);

    return { ok: true, message: `Sold ${amount} units for ${total} Star Coins.`, total };
  }
}
