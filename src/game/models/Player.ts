export type InventoryIndex = 0 | 1;

export class PlayerModel {
  name: string;
  private credits: number;
  private fuel: number;
  private inventory: [number, number];
  private shipRegistry: Record<string, boolean>;

  constructor(name = 'Player') {
    this.name = name;
    this.credits = 1000;
    this.fuel = 100;
    this.inventory = [0, 0];
    this.shipRegistry = {
      'Rusty Scout': true,
      'Cargo Hauler': false,
      'Falcon Scout': false
    };
  }

  getCredits(): number {
    return this.credits;
  }

  getFuel(): number {
    return this.fuel;
  }

  getItem(index: InventoryIndex): number {
    return this.inventory[index];
  }

  getInventory(index: InventoryIndex): number {
    return this.inventory[index];
  }

  getTotalItemNum(): number {
    return this.inventory[0] + this.inventory[1];
  }

  getRegistry(): Record<string, boolean> {
    return { ...this.shipRegistry };
  }

  removeCredits(amount: number): void {
    this.credits -= amount;
  }

  addCredits(amount: number): void {
    this.credits += amount;
  }

  removeFuel(amount: number): void {
    this.fuel = Math.max(0, this.fuel - amount);
  }

  addFuel(amount: number): void {
    this.fuel += amount;
  }

  removeItem(index: InventoryIndex, amount: number): void {
    this.inventory[index] = Math.max(0, this.inventory[index] - amount);
  }

  addItem(index: InventoryIndex, amount: number): void {
    this.inventory[index] += amount;
  }

  unlockShip(name: string): void {
    this.shipRegistry[name] = true;
  }

  setShipOwned(name: string, owned: boolean): void {
    this.shipRegistry[name] = owned;
  }

  setName(name: string): void {
    this.name = name;
  }

  setCredits(amount: number): void {
    this.credits = amount;
  }

  setFuel(amount: number): void {
    this.fuel = amount;
  }

  setItem(index: InventoryIndex, amount: number): void {
    this.inventory[index] = amount;
  }
}
