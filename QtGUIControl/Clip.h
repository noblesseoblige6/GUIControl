#pragma once

class Clip : public QGraphicsObject
{
    Q_OBJECT
public:
    Clip( QGraphicsItem *parent = nullptr );
    Clip( const QRectF& rect,  QGraphicsItem *parent = nullptr );
    ~Clip();
    
protected:
    void update();

protected:
    void mousePressEvent( QGraphicsSceneMouseEvent* event );
    void mouseMoveEvent( QGraphicsSceneMouseEvent* event );
    void mouseReleaseEvent( QGraphicsSceneMouseEvent* event );

    QRectF boundingRect() const;
    void paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );

    protected slots:
    void onChanged();

private:
    QRectF  m_rect; // driven from the model
    QPointF m_mousePos;
    QPointF m_prevPos;

    // data which model should have
    int m_currentFrame;
    int m_duration;
};
