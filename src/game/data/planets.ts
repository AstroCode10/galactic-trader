export interface PlanetDefinition {
  index: number;
  name: string;
  biome: string;
  spriteKey: string;
  x: number;
  y: number;
}

export const PLANETS: PlanetDefinition[] = [
  { index: 0, name: 'Tatooine', biome: 'desert', spriteKey: 'planet_desert', x: 160, y: 380 },
  { index: 1, name: 'Coruscant', biome: 'city', spriteKey: 'planet_city', x: 380, y: 300 },
  { index: 2, name: 'Hoth', biome: 'ice', spriteKey: 'planet_ice', x: 640, y: 420 },
  { index: 3, name: 'Endor', biome: 'forest', spriteKey: 'planet_forest', x: 860, y: 320 },
  { index: 4, name: 'Naboo', biome: 'ocean', spriteKey: 'planet_ocean', x: 1080, y: 400 }
];
