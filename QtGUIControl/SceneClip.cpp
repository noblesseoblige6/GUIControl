
SceneClip::SceneClip( QGraphicsItem *parent )
: SceneClip( QRectF(), parent )
{
}

SceneClip::SceneClip( const QRectF& rect, QGraphicsItem *parent )
    : Clip(rect, parent)
    , m_ghost(nullptr)
{
    m_ghost = new Clip( rect, this );
}

SceneClip::~SceneClip()
{
}

void SceneClip::mousePressEvent( QGraphicsSceneMouseEvent* event )
{
    scene()->sendEvent( m_ghost, event );

    QGraphicsObject::mousePressEvent( event );
}

void SceneClip::mouseMoveEvent( QGraphicsSceneMouseEvent* event )
{
    if (!m_ghost->isVisible())
    {
        //m_ghost->setPos( 0, 0 );
        m_ghost->setVisible( true );
    }

    scene()->sendEvent( m_ghost, event );
}

void SceneClip::mouseReleaseEvent( QGraphicsSceneMouseEvent* event )
{
    m_ghost->setVisible( false );
    m_currentFrame = m_ghost->getCurrentFrame();

    update();
}