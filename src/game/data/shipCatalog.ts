export interface ShipCatalogEntry {
  type: string;
  maxFuel: number;
  maxCargo: number;
  cost: number;
}

export const SHIP_CATALOG: ShipCatalogEntry[] = [
  { type: 'Rusty Scout', maxFuel: 100, maxCargo: 20, cost: 0 },
  { type: 'Cargo Hauler', maxFuel: 80, maxCargo: 60, cost: 400 },
  { type: 'Falcon Scout', maxFuel: 250, maxCargo: 15, cost: 600 }
];
