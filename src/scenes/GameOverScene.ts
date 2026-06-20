import Phaser from 'phaser';
import { gameController } from '../game/GameSession';

export class GameOverScene extends Phaser.Scene {
  constructor() {
    super('GameOverScene');
  }

  create(): void {
    const { width, height } = this.scale;
    this.cameras.main.setBackgroundColor('#120811');
    this.add
      .text(width / 2, 210, 'GAME OVER', {
        color: '#ff6f91',
        fontFamily: 'monospace',
        fontSize: '58px'
      })
      .setOrigin(0.5);
    this.add
      .text(width / 2, 290, 'Stranded with 0 credits, no cargo, and an empty fuel tank.', {
        color: '#f7d8e1',
        fontFamily: 'monospace',
        fontSize: '20px'
      })
      .setOrigin(0.5);

    const button = this.add.rectangle(width / 2, 390, 260, 48, 0x4a1730).setStrokeStyle(2, 0xff9fba);
    const label = this.add
      .text(width / 2, 390, 'Return to Title', {
        color: '#ffffff',
        fontFamily: 'monospace',
        fontSize: '21px'
      })
      .setOrigin(0.5);

    const restart = (): void => {
      gameController.clearSavedState();
      this.scene.start('TitleScene');
    };

    button.setInteractive({ useHandCursor: true });
    label.setInteractive({ useHandCursor: true });
    button.on('pointerdown', restart);
    label.on('pointerdown', restart);
  }
}
