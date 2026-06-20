import Phaser from 'phaser';
import { gameController } from '../game/GameSession';

export class TitleScene extends Phaser.Scene {
  private nameInput?: HTMLInputElement;

  constructor() {
    super('TitleScene');
  }

  create(): void {
    const { width, height } = this.scale;
    this.cameras.main.setBackgroundColor('#080b18');
    this.addStarfield();

    this.add
      .text(width / 2, 130, 'Galactic Trader', {
        color: '#f7d36b',
        fontFamily: 'monospace',
        fontSize: '56px'
      })
      .setOrigin(0.5);

    this.add
      .text(width / 2, 190, 'Captain a trade ship through five volatile planetary markets.', {
        color: '#a9bad8',
        fontFamily: 'monospace',
        fontSize: '20px'
      })
      .setOrigin(0.5);

    this.createNameInput(width / 2, 285);
    this.createButton(width / 2, 370, 'New Game', () => {
      const captainName = this.nameInput?.value.trim() || 'Player';
      gameController.clearSavedState();
      gameController.initialise(captainName);
      this.scene.start('StarMapScene');
    });

    this.createButton(width / 2, 435, gameController.hasSavedState() ? 'Continue' : 'Continue (No Save)', () => {
      if (!gameController.hasSavedState()) {
        return;
      }

      gameController.loadSavedState();
      this.scene.start('StarMapScene');
    }, !gameController.hasSavedState());
  }

  private createNameInput(x: number, y: number): void {
    const element = document.createElement('input');
    element.type = 'text';
    element.value = 'Captain';
    element.maxLength = 24;
    element.style.width = '320px';
    element.style.height = '44px';
    element.style.border = '2px solid #4f6d9a';
    element.style.background = '#11182a';
    element.style.color = '#f5f7ff';
    element.style.font = '20px Consolas, Monaco, monospace';
    element.style.padding = '0 14px';
    element.style.outline = 'none';
    element.style.textAlign = 'center';
    this.nameInput = element;
    this.add.dom(x, y, element);
  }

  private createButton(x: number, y: number, label: string, onClick: () => void, disabled = false): void {
    const fill = disabled ? 0x2a3142 : 0x183f5f;
    const stroke = disabled ? 0x495064 : 0x69c3ff;
    const textColor = disabled ? '#8b93a8' : '#ffffff';
    const box = this.add.rectangle(x, y, 260, 46, fill).setStrokeStyle(2, stroke);
    const text = this.add
      .text(x, y, label, {
        color: textColor,
        fontFamily: 'monospace',
        fontSize: '22px'
      })
      .setOrigin(0.5);

    if (!disabled) {
      box.setInteractive({ useHandCursor: true });
      box.on('pointerover', () => box.setFillStyle(0x236a8f));
      box.on('pointerout', () => box.setFillStyle(fill));
      box.on('pointerdown', onClick);
      text.setInteractive({ useHandCursor: true });
      text.on('pointerdown', onClick);
    }
  }

  private addStarfield(): void {
    const graphics = this.add.graphics();
    graphics.fillStyle(0xffffff, 1);
    for (let i = 0; i < 120; i++) {
      const x = (i * 97) % 1280;
      const y = (i * 53) % 720;
      const alpha = 0.25 + ((i * 17) % 60) / 100;
      graphics.fillStyle(0xffffff, alpha);
      graphics.fillCircle(x, y, i % 5 === 0 ? 1.5 : 1);
    }
  }
}
