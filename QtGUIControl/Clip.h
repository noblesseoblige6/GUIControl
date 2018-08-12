#pragma once

class Clip : public QGraphicsObject
{
    Q_OBJECT
public:
    Clip( QGraphicsItem *parent = nullptr );
    Clip( const QRectF& rect,  QGraphicsItem *parent = nullptr );
    ~Clip();

protected:
    void mousePressEvent( QGraphicsSceneMouseEvent* event );
    void mouseMoveEvent( QGraphicsSceneMouseEvent* event );
    void mouseReleaseEvent( QGraphicsSceneMouseEvent* event );

    QRectF boundingRect() const;
    void paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );

    protected slots:
    void onTimeScaleChanged();

private:
    QRectF m_rect;
    QPointF m_mousePos;
    QPointF m_prevPos;
};
