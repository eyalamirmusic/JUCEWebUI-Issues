console.log("Loading...")


import {
  AnimatedSprite,
  Application,
  Assets,
  Texture
} from './pixi.min.mjs';

(async () => {
  const app = new Application();
  await app.init({ background: '#1099bb', resizeTo: window });

  document.body.appendChild(app.canvas);
  await Assets.load('./fighter.json');
  const frames = [];

  for (let i = 0; i < 30; i++) {
    const val = i < 10 ? `0${i}` : i;
    frames.push(Texture.from(`rollSequence00${val}.png`));
  }

  const anim = new AnimatedSprite(frames);

  anim.x = app.screen.width / 2;
  anim.y = app.screen.height / 2;
  anim.anchor.set(0.5);
  anim.animationSpeed = 0.5;
  anim.play();

  app.stage.addChild(anim);

  app.ticker.add(() => {
    anim.rotation += 0.01;
  });
})();
