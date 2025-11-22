#include "penguin.h"
#include <QTimer>
#include <QGraphicsColorizeEffect>

Penguin::Penguin(QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent)
{
    originalPixmap = QPixmap(":/assets/penguin_fishing.png");
    QPixmap scaledPixmap = originalPixmap.scaled(240, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPixmap(scaledPixmap);
    
    setTransformOriginPoint(boundingRect().center());
}

void Penguin::shock()
{
    QGraphicsColorizeEffect* effect = new QGraphicsColorizeEffect();
    effect->setColor(Qt::red);
    effect->setStrength(0.8);
    setGraphicsEffect(effect);
}

void Penguin::clearShockEffect()
{
    setGraphicsEffect(nullptr);
}

