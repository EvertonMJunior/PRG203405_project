#ifndef FISH_H
#define FISH_H

#include "acquaticanimal.h"

class Fish : public AcquaticAnimal
{
public:
    explicit Fish(QGraphicsItem* parent = nullptr);
    
    void catchFish();

private:
    QPixmap fishPixmap;
};

#endif // FISH_H

