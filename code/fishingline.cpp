#include "fishingline.h"
#include <QPainter>
#include <QPainterPath>
#include <algorithm>

FishingLine::FishingLine(qreal startX, qreal startY, QGraphicsItem* parent)
    : QGraphicsObject(parent)
    , startX(startX)
    , startY(startY)
    , currentY(startY + 100)
    , has_bait(true)
{
    linePixmap = QPixmap(":/assets/fishing_line.png");
    wormPixmap = QPixmap(":/assets/worm.png").scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    
    setFlag(QGraphicsItem::ItemHasNoContents, false);
}

QRectF FishingLine::boundingRect() const
{
    qreal minY = std::min(startY, currentY);
    qreal maxY = std::max(startY, currentY);
    
    maxY += wormPixmap.height();
    
    return QRectF(startX - 50, minY, 100, maxY - minY);
}

void FishingLine::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    
    painter->setRenderHint(QPainter::Antialiasing);
    
    QPen linePen(QColor(101, 67, 33), 2);
    painter->setPen(linePen);
    painter->drawLine(QPointF(startX, startY), QPointF(startX, currentY));
    
    if (has_bait) {
        qreal wormX = startX - wormPixmap.width() / 2.0;
        qreal wormY = currentY;
        painter->drawPixmap(QPointF(wormX, wormY), wormPixmap);
    }
}

qreal FishingLine::getY() const
{
    return currentY;
}

void FishingLine::setY(qreal y)
{
    currentY = std::max(MIN_Y, std::min(MAX_Y, y));
    prepareGeometryChange();
    update();
}

bool FishingLine::hasBait() const
{
    return has_bait;
}

void FishingLine::setBait(bool has)
{
    has_bait = has;
    update();
}

QRectF FishingLine::getTipRect() const
{
    qreal wormX = startX - wormPixmap.width() / 2.0;
    qreal wormY = currentY;
    return QRectF(wormX, wormY, wormPixmap.width(), wormPixmap.height());
}

QPainterPath FishingLine::getLinePath() const
{
    QPainterPath path;
    path.moveTo(startX - 3, startY);
    path.lineTo(startX + 3, startY);
    path.lineTo(startX + 3, currentY);
    path.lineTo(startX - 3, currentY);
    path.closeSubpath();
    return path;
}

