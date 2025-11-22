#ifndef FISHINGLINE_H
#define FISHINGLINE_H

#include <QGraphicsObject>
#include <QPixmap>

class FishingLine : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit FishingLine(qreal startX, qreal startY, QGraphicsItem* parent = nullptr);
    
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    
    qreal getY() const;
    void setY(qreal y);
    
    bool hasBait() const;
    void setBait(bool has);
    
    QRectF getTipRect() const;
    QPainterPath getLinePath() const;

private:
    qreal startX;
    qreal startY;
    qreal currentY;
    bool has_bait;
    
    QPixmap linePixmap;
    QPixmap wormPixmap;
    
    static constexpr qreal MIN_Y = 300.0;
    static constexpr qreal MAX_Y = 650.0;
};

#endif // FISHINGLINE_H

