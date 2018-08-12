
Clip::Clip( QGraphicsItem *parent)
    : Clip(QRectF(), parent)
{
}

Clip::Clip( const QRectF& rect, QGraphicsItem *parent )
    : QGraphicsObject( parent )
    , m_rect( rect )
{
    setFlags( QGraphicsItem::ItemIsMovable );
}

Clip::~Clip()
{
}

void Clip::mousePressEvent( QGraphicsSceneMouseEvent* event )
{
    m_mousePos = event->scenePos();
    m_prevPos = pos();

    QGraphicsObject::mousePressEvent( event );
}

void Clip::mouseMoveEvent( QGraphicsSceneMouseEvent* event )
{
    QPointF delta = event->scenePos() - m_mousePos;

    setPos(m_prevPos.x() + delta.x(), 0 );
}

void Clip::mouseReleaseEvent( QGraphicsSceneMouseEvent* event )
{
    QPointF delta = event->scenePos() - m_mousePos;
    
    TrackScene* curScene = static_cast<TrackScene*>(scene());
    if (curScene == nullptr)
        return;

    float pitch = curScene->getPitch();

    int count = delta.x() / pitch;

    setPos( m_prevPos.x() + pitch * count, 0 );
}

QRectF Clip::boundingRect() const
{
    return m_rect;
}


void Clip::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
    QPolygon polygon;
    painter->setBrush( Qt::red );
    painter->drawPolygon( m_rect );
    //painter->drawPolygon( polygon );
    
    Q_UNUSED( option );
    Q_UNUSED( widget );
}

void Clip::onTimeScaleChanged()
{
    // モデルの値に応じて位置を変更する
}
