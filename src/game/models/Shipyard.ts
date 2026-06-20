import { SHIP_CATALOG, type ShipCatalogEntry } from '../data/shipCatalog';
import { PlayerModel } from './Player';
import { ShipModel } from './Ship';

export type ShipyardResult =
  | { ok: true; ship: ShipModel; message: string }
  | { ok: false; message: string };

export class ShipyardModel {
  private readonly catalog = new Map(SHIP_CATALOG.map((entry) => [entry.type, entry]));

  getCatalog(): ShipCatalogEntry[] {
    return SHIP_CATALOG;
  }

  getShipBlueprint(shipName: string): ShipModel {
    const specs = this.catalog.get(shipName) ?? this.catalog.get('Rusty Scout');
    if (!specs) {
      return new ShipModel();
    }

    return new ShipModel(specs.type, specs.maxFuel, specs.maxCargo);
  }

  buyOrEquipShip(player: PlayerModel, currentShip: ShipModel, targetName: string): ShipyardResult {
    const targetSpecs = this.catalog.get(targetName);
    if (!targetSpecs) {
      return { ok: false, message: 'Unknown ship model.' };
    }

    const registry = player.getRegistry();
    if (currentShip.getType() === targetName) {
      return { ok: false, message: `You are already piloting the ${targetName}!` };
    }

    if (!registry[targetName] && player.getCredits() < targetSpecs.cost) {
      return { ok: false, message: 'Transaction Denied: Insufficient Star Coins.' };
    }

    if (player.getTotalItemNum() > targetSpecs.maxCargo) {
      return {
        ok: false,
        message: `Transaction Denied: current inventory will not fit into the ${targetName}.`
      };
    }

    if (!registry[targetName]) {
      player.removeCredits(targetSpecs.cost);
      player.unlockShip(targetName);
    }

    const nextShip = new ShipModel(targetName, targetSpecs.maxFuel, targetSpecs.maxCargo);
    if (player.getFuel() > targetSpecs.maxFuel) {
      player.removeFuel(player.getFuel() - targetSpecs.maxFuel);
    }

    return { ok: true, ship: nextShip, message: `Swapped to ${targetName}.` };
  }

  repairShip(player: PlayerModel, currentShip: ShipModel): ShipyardResult {
    if (currentShip.getDamageCost() === 0) {
      return { ok: false, message: 'Your ship does not need repairs.' };
    }

    if (player.getCredits() < currentShip.getDamageCost()) {
      return { ok: false, message: 'Cannot repair ship: insufficient Star Coins.' };
    }

    const specs = this.catalog.get(currentShip.getType());
    player.removeCredits(currentShip.getDamageCost());
    currentShip.setDamageCost(0);
    currentShip.setMaxCargo(specs?.maxCargo ?? currentShip.getMaxCargo());

    return { ok: true, ship: currentShip, message: 'Ship repaired.' };
  }
}
