#ifndef JELLYFISH_H
#define JELLYFISH_H

#include "acquaticanimal.h"

class Jellyfish : public AcquaticAnimal
{
public:
    explicit Jellyfish(QGraphicsItem* parent = nullptr);
    
    void shockPenguin();

private:
    QPixmap jellyfishPixmap;
};

#endif // JELLYFISH_H

