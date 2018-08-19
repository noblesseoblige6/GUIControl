#pragma once

class SceneClip : public Clip
{
    Q_OBJECT

public:
    SceneClip( QGraphicsItem *parent = nullptr);
    SceneClip( const QRectF& rect, QGraphicsItem *parent = nullptr );
    ~SceneClip();

protected:
    void mousePressEvent( QGraphicsSceneMouseEvent* event );
    void mouseMoveEvent( QGraphicsSceneMouseEvent* event );
    void mouseReleaseEvent( QGraphicsSceneMouseEvent* event );

private:
    Clip * m_ghost;
};
