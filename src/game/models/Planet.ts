import { RandomSystem } from '../systems/RandomSystem';

export class PlanetModel {
  constructor(
    public readonly index: number,
    public readonly name: string,
    public ironPrice: number,
    public waterPrice: number,
    public fuelPrice: number
  ) {}

  static create(index: number, name: string, random = new RandomSystem()): PlanetModel {
    const planet = new PlanetModel(index, name, 0, 0, 0);
    planet.randomisePrices(random);
    return planet;
  }

  getPrice(index: 0 | 1 | 2): number {
    return [this.ironPrice, this.waterPrice, this.fuelPrice][index];
  }

  randomisePrices(random = new RandomSystem()): void {
    this.ironPrice = random.uniformInt(50, 120);
    this.waterPrice = random.uniformInt(20, 80);
    this.fuelPrice = random.uniformInt(30, 100);
  }
}
