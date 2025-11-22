#ifndef ACQUATICANIMAL_H
#define ACQUATICANIMAL_H

#include <QGraphicsPixmapItem>
#include "game.h"

class AcquaticAnimal : public QGraphicsPixmapItem
{
public:
    explicit AcquaticAnimal(QGraphicsItem* parent = nullptr);
    virtual ~AcquaticAnimal() = default;
    
    Side getSpawnSide() const;
    qreal getSpawnY() const;
    Direction getSwimDirection() const;
    
    void updatePosition();
    bool isOffscreen(qreal sceneWidth) const;
    
    qreal getSpeed() const;
    void setSpeed(qreal speed);

protected:
    void initialize();
    
    Side spawn_side;
    Direction swim_direction;
    qreal speed;
    
    static constexpr qreal MIN_WATER_Y = 320.0;
    static constexpr qreal MAX_WATER_Y = 650.0;
};

#endif // ACQUATICANIMAL_H

