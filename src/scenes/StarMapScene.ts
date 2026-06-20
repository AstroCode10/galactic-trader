import Phaser from 'phaser';
import { PLANETS, type PlanetDefinition } from '../game/data/planets';
import { gameController } from '../game/GameSession';
import type { GameState } from '../game/GameState';
import type { BuyResource, SellResource } from '../game/systems/TradeSystem';
import { formatCredits } from '../utils/format';

type DockTab = 'buy' | 'sell';

export class StarMapScene extends Phaser.Scene {
  private state!: GameState;
  private hudText!: Phaser.GameObjects.Text;
  private marketPanel?: Phaser.GameObjects.Container;
  private feedbackText!: Phaser.GameObjects.Text;
  private savedText!: Phaser.GameObjects.Text;
  private tooltipText!: Phaser.GameObjects.Text;
  private activeTab: DockTab = 'buy';

  constructor() {
    super('StarMapScene');
  }

  create(): void {
    this.state = gameController.getState();
    this.cameras.main.setBackgroundColor('#07101f');
    this.drawStarfield();
    this.drawRoutes();
    this.drawHud();
    this.drawPlanets();
    this.drawFeedback();
    this.openDock();
  }

  private drawStarfield(): void {
    const graphics = this.add.graphics();
    for (let i = 0; i < 150; i++) {
      const x = (i * 89) % 1280;
      const y = (i * 47) % 720;
      const alpha = 0.2 + ((i * 13) % 65) / 100;
      graphics.fillStyle(0xffffff, alpha);
      graphics.fillCircle(x, y, i % 7 === 0 ? 1.7 : 1);
    }
  }

  private drawRoutes(): void {
    const graphics = this.add.graphics();
    graphics.lineStyle(3, 0x2d496d, 0.8);
    for (let i = 0; i < PLANETS.length - 1; i++) {
      const from = PLANETS[i];
      const to = PLANETS[i + 1];
      graphics.lineBetween(from.x, from.y, to.x, to.y);
    }
  }

  private drawHud(): void {
    this.add.rectangle(640, 35, 1280, 70, 0x0b1424, 0.96);
    this.hudText = this.add.text(24, 17, '', {
      color: '#f5f7ff',
      fontFamily: 'monospace',
      fontSize: '19px'
    });

    this.savedText = this.add
      .text(1190, 17, 'Saved', {
        color: '#9fffc2',
        fontFamily: 'monospace',
        fontSize: '18px'
      })
      .setOrigin(1, 0)
      .setAlpha(0);

    this.refreshHud();
  }

  private drawPlanets(): void {
    PLANETS.forEach((planet) => {
      const color = this.colorForBiome(planet.biome);
      const ring = this.add.circle(planet.x, planet.y, 34, 0x000000, 0).setStrokeStyle(2, 0x5c7ca8, 0.75);
      const body = this.add.circle(planet.x, planet.y, 24, color, 1).setStrokeStyle(2, 0xf0f6ff, 0.8);
      const label = this.add
        .text(planet.x, planet.y + 42, planet.name, {
          color: '#d9e6ff',
          fontFamily: 'monospace',
          fontSize: '16px'
        })
        .setOrigin(0.5);

      body.setInteractive({ useHandCursor: true });
      body.on('pointerover', () => {
        ring.setStrokeStyle(3, 0xf7d36b, 1);
        body.setScale(1.12);
        this.showTooltip(planet);
      });
      body.on('pointerout', () => {
        ring.setStrokeStyle(2, 0x5c7ca8, 0.75);
        body.setScale(1);
        this.tooltipText.setVisible(false);
      });
      body.on('pointerdown', () => this.handlePlanetClick(planet));

      if (planet.index === this.state.currentPlanetIdx) {
        this.add.circle(planet.x, planet.y, 42, 0xf7d36b, 0.12).setStrokeStyle(2, 0xf7d36b, 0.9);
        label.setColor('#f7d36b');
      }
    });

    this.tooltipText = this.add
      .text(0, 0, '', {
        color: '#ffffff',
        backgroundColor: '#11182a',
        fontFamily: 'monospace',
        fontSize: '15px',
        padding: { x: 10, y: 6 }
      })
      .setVisible(false)
      .setDepth(10);
  }

  private drawFeedback(): void {
    this.feedbackText = this.add
      .text(640, 668, '', {
        color: '#ffe8a6',
        fontFamily: 'monospace',
        fontSize: '18px'
      })
      .setOrigin(0.5);
  }

  private handlePlanetClick(planet: PlanetDefinition): void {
    if (planet.index === this.state.currentPlanetIdx) {
      this.openDock();
      this.setFeedback(`Docked at ${planet.name}.`);
      return;
    }

    const result = gameController.requestTravel(planet.index);
    this.state = gameController.getState();
    if (!result.ok) {
      this.setFeedback(result.message);
      this.openDock();
      return;
    }

    if (gameController.travel.isGameOver(this.state)) {
      this.scene.start('GameOverScene');
      return;
    }

    this.flashSaved();
    this.scene.restart();
  }

  private openDock(): void {
    this.marketPanel?.destroy(true);
    const current = this.state.planets[this.state.currentPlanetIdx];
    const panel = this.add.container(640, 520);
    this.marketPanel = panel;

    const bg = this.add.rectangle(0, 0, 920, 260, 0x0d1728, 0.97).setStrokeStyle(2, 0x4f6d9a);
    panel.add(bg);
    panel.add(
      this.add
        .text(-430, -112, `${current.name} Market`, {
          color: '#f7d36b',
          fontFamily: 'monospace',
          fontSize: '24px'
        })
        .setOrigin(0, 0.5)
    );

    panel.add(
      this.add.text(-430, -76, `Iron ${current.ironPrice} | Water ${current.waterPrice} | Fuel ${current.fuelPrice}`, {
        color: '#c8d8f4',
        fontFamily: 'monospace',
        fontSize: '18px'
      })
    );

    panel.add(this.createPanelButton(-350, -18, 'Buy', () => this.switchTab('buy'), this.activeTab === 'buy'));
    panel.add(this.createPanelButton(-220, -18, 'Sell', () => this.switchTab('sell'), this.activeTab === 'sell'));

    if (this.activeTab === 'buy') {
      this.addBuyControls(panel);
    } else {
      this.addSellControls(panel);
    }
  }

  private switchTab(tab: DockTab): void {
    this.activeTab = tab;
    this.openDock();
  }

  private addBuyControls(panel: Phaser.GameObjects.Container): void {
    this.addTradeRow(panel, -60, 'Iron', 'iron', [1, 5, 10], 'buy');
    this.addTradeRow(panel, 18, 'Water', 'water', [1, 5, 10], 'buy');
    this.addTradeRow(panel, 96, 'Fuel', 'fuel', [1, 5, 10], 'buy');
  }

  private addSellControls(panel: Phaser.GameObjects.Container): void {
    this.addTradeRow(panel, -24, 'Iron', 'iron', [1, 5, 10], 'sell');
    this.addTradeRow(panel, 58, 'Water', 'water', [1, 5, 10], 'sell');
  }

  private addTradeRow(
    panel: Phaser.GameObjects.Container,
    y: number,
    label: string,
    resource: BuyResource | SellResource,
    amounts: number[],
    mode: 'buy' | 'sell'
  ): void {
    panel.add(
      this.add.text(-430, y, label, {
        color: '#ffffff',
        fontFamily: 'monospace',
        fontSize: '19px'
      })
    );

    amounts.forEach((amount, index) => {
      panel.add(
        this.createPanelButton(-300 + index * 126, y + 12, `${mode === 'buy' ? 'Buy' : 'Sell'} ${amount}`, () => {
          const result =
            mode === 'buy'
              ? gameController.buy(resource as BuyResource, amount)
              : gameController.sell(resource as SellResource, amount);
          this.state = gameController.getState();
          this.setFeedback(result.message);
          if (result.ok) {
            this.flashSaved();
          }
          this.refreshHud();
          this.openDock();
        })
      );
    });
  }

  private createPanelButton(
    x: number,
    y: number,
    label: string,
    onClick: () => void,
    active = false
  ): Phaser.GameObjects.Container {
    const container = this.add.container(x, y);
    const bg = this.add
      .rectangle(0, 0, 108, 36, active ? 0x2b6f8f : 0x17334e, 0.98)
      .setStrokeStyle(2, active ? 0xf7d36b : 0x69c3ff);
    const text = this.add
      .text(0, 0, label, {
        color: '#ffffff',
        fontFamily: 'monospace',
        fontSize: '16px'
      })
      .setOrigin(0.5);

    bg.setInteractive({ useHandCursor: true });
    bg.on('pointerover', () => bg.setFillStyle(0x245a78));
    bg.on('pointerout', () => bg.setFillStyle(active ? 0x2b6f8f : 0x17334e));
    bg.on('pointerdown', onClick);
    text.setInteractive({ useHandCursor: true });
    text.on('pointerdown', onClick);
    container.add([bg, text]);
    return container;
  }

  private refreshHud(): void {
    const player = this.state.player;
    const ship = this.state.ship;
    const planet = this.state.planets[this.state.currentPlanetIdx];
    this.hudText.setText(
      `${player.name} | ${formatCredits(player.getCredits())} | Fuel ${player.getFuel()}/${ship.getMaxFuel()} | Cargo ${player.getTotalItemNum()}/${ship.getMaxCargo()} | ${ship.getType()} | Orbit: ${planet.name}`
    );
  }

  private showTooltip(planet: PlanetDefinition): void {
    const fuelCost = gameController.travel.calcFuelCost(this.state.currentPlanetIdx, planet.index);
    const action = planet.index === this.state.currentPlanetIdx ? 'Click to dock' : `Fuel cost: ${fuelCost}`;
    this.tooltipText
      .setText(`${planet.name}\n${action}`)
      .setPosition(planet.x + 34, planet.y - 52)
      .setVisible(true);
  }

  private setFeedback(message: string): void {
    this.feedbackText.setText(message);
  }

  private flashSaved(): void {
    this.savedText.setAlpha(1);
    this.tweens.add({
      targets: this.savedText,
      alpha: 0,
      duration: 900,
      delay: 500
    });
  }

  private colorForBiome(biome: string): number {
    switch (biome) {
      case 'desert':
        return 0xd8a446;
      case 'city':
        return 0x8fb7ff;
      case 'ice':
        return 0xc8f4ff;
      case 'forest':
        return 0x63b06b;
      case 'ocean':
        return 0x3f8ed8;
      default:
        return 0xffffff;
    }
  }
}
