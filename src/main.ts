import Phaser from 'phaser';
import { BootScene } from './scenes/BootScene';
import { GameOverScene } from './scenes/GameOverScene';
import { PreloadScene } from './scenes/PreloadScene';
import { StarMapScene } from './scenes/StarMapScene';
import { TitleScene } from './scenes/TitleScene';
import { TravelScene } from './scenes/TravelScene';

const config: Phaser.Types.Core.GameConfig = {
  type: Phaser.AUTO,
  parent: 'game',
  backgroundColor: '#080b18',
  scale: {
    mode: Phaser.Scale.FIT,
    autoCenter: Phaser.Scale.CENTER_BOTH,
    width: 1280,
    height: 720
  },
  dom: {
    createContainer: true
  },
  scene: [BootScene, PreloadScene, TitleScene, StarMapScene, TravelScene, GameOverScene]
};

new Phaser.Game(config);
