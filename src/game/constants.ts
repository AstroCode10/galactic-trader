export const BASE_FUEL_COST = 15;
export const FLAT_TOLL = 200;
export const DERELICT_FUEL = 5;

export const COMMODITIES = ['Iron', 'Water', 'Fuel'] as const;
export type Commodity = (typeof COMMODITIES)[number];
