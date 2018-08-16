
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

    setPos(m_prevPos.x() + delta.x(), y() );
}

void Clip::mouseReleaseEvent( QGraphicsSceneMouseEvent* event )
{
    QPointF scenePos = event->scenePos();
    QPointF d(scenePos.x() - pos().x(), 0.0f);

    TrackScene* curScene = static_cast<TrackScene*>(scene());
    if (curScene == nullptr)
        return;

    m_currentFrame = curScene->getTimeSliderValueFromPosition( scenePos - d );

#if 1
    update();
#else
    // Modified data in the model and notify changes
#endif
}

QRectF Clip::boundingRect() const
{
    return m_rect;
}

void Clip::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
    painter->drawPolygon( m_rect );

    Q_UNUSED( option );
    Q_UNUSED( widget );
}

void Clip::onChanged()
{
    // モデルの値に応じて位置を変更する
    update();
}

void Clip::update()
{
    TrackScene* curScene = static_cast<TrackScene*>(scene());
    if (curScene == nullptr)
        return;

    bool isInRange = curScene->isInTimeSliderRange( m_currentFrame ) |
                     curScene->isInTimeSliderRange( m_currentFrame + m_duration );

    setVisible( isInRange );

    if (isInRange)
    {
        float x = curScene->getTimeSliderPositionFromValue( m_currentFrame );

        setPos( x, pos().y() );
    }
}
