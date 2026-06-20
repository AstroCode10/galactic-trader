export class ShipModel {
  type: string;
  maxFuel: number;
  maxCargo: number;
  damageCost: number;

  constructor(type = 'Rusty Scout', maxFuel = 100, maxCargo = 20) {
    this.type = type;
    this.maxFuel = maxFuel;
    this.maxCargo = maxCargo;
    this.damageCost = 0;
  }

  getType(): string {
    return this.type;
  }

  getShipType(): string {
    return this.type;
  }

  getMaxFuel(): number {
    return this.maxFuel;
  }

  getMaxCargo(): number {
    return this.maxCargo;
  }

  getDamageCost(): number {
    return this.damageCost;
  }

  delCargoSlots(amount: number): void {
    this.maxCargo = Math.max(0, this.maxCargo - amount);
  }

  setDamageCost(amount: number): void {
    this.damageCost = amount;
  }

  setMaxCargo(amount: number): void {
    this.maxCargo = amount;
  }
}
