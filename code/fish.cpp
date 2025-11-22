#include "fish.h"

Fish::Fish(QGraphicsItem *parent) : AcquaticAnimal(parent) {
  if (swim_direction == Direction::LeftToRight) {
    fishPixmap = QPixmap(":/assets/fish_ltr.png");
  } else {
    fishPixmap = QPixmap(":/assets/fish_rtl.png");
  }

  fishPixmap =
      fishPixmap.scaled(80, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation);
  setPixmap(fishPixmap);

  qreal spawnY = getSpawnY();
  if (spawn_side == Side::Left) {
    setPos(-fishPixmap.width(), spawnY);
  } else {
    setPos(1000, spawnY);
  }
}

void Fish::catchFish() {}
