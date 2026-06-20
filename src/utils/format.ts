export function formatCredits(amount: number): string {
  return `${amount.toLocaleString()} Star Coins`;
}

export function formatUnits(amount: number, label = 'units'): string {
  return `${amount.toLocaleString()} ${label}`;
}
