#include "acquaticanimal.h"
#include <QRandomGenerator>

AcquaticAnimal::AcquaticAnimal(QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent)
    , speed(2.0)
{
    initialize();
}

void AcquaticAnimal::initialize()
{
    spawn_side = QRandomGenerator::global()->bounded(2) == 0 ? Side::Left : Side::Right;
    swim_direction = (spawn_side == Side::Left) ? Direction::LeftToRight : Direction::RightToLeft;
}

Side AcquaticAnimal::getSpawnSide() const
{
    return spawn_side;
}

qreal AcquaticAnimal::getSpawnY() const
{
    return MIN_WATER_Y + QRandomGenerator::global()->bounded(MAX_WATER_Y - MIN_WATER_Y);
}

Direction AcquaticAnimal::getSwimDirection() const
{
    return swim_direction;
}

void AcquaticAnimal::updatePosition()
{
    if (swim_direction == Direction::LeftToRight) {
        setPos(x() + speed, y());
    } else {
        setPos(x() - speed, y());
    }
}

bool AcquaticAnimal::isOffscreen(qreal sceneWidth) const
{
    qreal itemWidth = boundingRect().width();
    
    if (swim_direction == Direction::LeftToRight) {
        return x() > sceneWidth;
    } else {
        return x() + itemWidth < 0;
    }
}

qreal AcquaticAnimal::getSpeed() const
{
    return speed;
}

void AcquaticAnimal::setSpeed(qreal newSpeed)
{
    speed = newSpeed;
}

