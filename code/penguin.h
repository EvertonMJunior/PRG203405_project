#ifndef PENGUIN_H
#define PENGUIN_H

#include <QGraphicsPixmapItem>

class Penguin : public QGraphicsPixmapItem
{
public:
    explicit Penguin(QGraphicsItem* parent = nullptr);
    
    void shock();
    void clearShockEffect();
    
private:
    QPixmap originalPixmap;
};

#endif // PENGUIN_H

