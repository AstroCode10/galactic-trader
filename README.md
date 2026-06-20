# Galactic Trader Web Port

Galactic Trader is being ported from the finished C++ console game into a Phaser 3 + TypeScript + Vite browser game. The original C++ implementation now lives in `cpp/` and is the gameplay logic specification for the web version.

## Development

Install dependencies, then start the Vite dev server:

```bash
npm install
npm run dev
```

Build the browser game:

```bash
npm run build
```

## Implementation Notes

- Follow `.cursor/plans/game-implementation.plan.md` for the phased build order.
- Keep formulas, validation order, catalogs, and encounter probabilities aligned with the C++ sources in `cpp/`.
- CrazyGames SDK integration is reserved for Phase 4 and must be verified against the current official SDK v3 docs before coding.
