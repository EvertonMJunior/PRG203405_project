#include "jellyfish.h"

Jellyfish::Jellyfish(QGraphicsItem* parent)
    : AcquaticAnimal(parent)
{
    jellyfishPixmap = QPixmap(":/assets/jellyfish.png");
    jellyfishPixmap = jellyfishPixmap.scaled(60, 70, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPixmap(jellyfishPixmap);
    
    qreal spawnY = getSpawnY();
    if (spawn_side == Side::Left) {
        setPos(-jellyfishPixmap.width(), spawnY);
    } else {
        setPos(1000, spawnY);
    }
}

void Jellyfish::shockPenguin()
{
}

