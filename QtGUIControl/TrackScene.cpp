
TrackScene::TrackScene( QObject *parent )
    : QGraphicsScene( parent )
    , m_duration( 0 )
    , m_proxyTimeSlider( nullptr )
   , m_proxyTimeSliderBar( nullptr )
{
}

TrackScene::~TrackScene()
{
}

void TrackScene::addItem( Clip *item )
{
    connect( this, SIGNAL( timeScaleChanged() ), item, SLOT( onChanged() ) );
    connect( this, SIGNAL( timeRangeChanged() ), item, SLOT( onChanged() ));
    
    item->moveBy( 0, m_proxyTimeSlider->geometry().height() );

    QGraphicsScene::addItem( item );
}

void TrackScene::setTimeSliderWidget( TimeSlider* timeSlider )
{
    connect( timeSlider, SIGNAL( durationChanged( int ) ), this, SLOT( onDurationChanged( int ) ) );

    m_proxyTimeSlider = addWidget( timeSlider );
    m_proxyTimeSlider->setZValue( 100.0f );

    m_proxyTimeSliderBar = addWidget( timeSlider->getVertivalBar() );
    m_proxyTimeSliderBar->setZValue( 99.0f );
}

void TrackScene::resizeTimeSlider( const QSizeF& size )
{
    int w = size.width();
    int h = size.height();

    QList<QGraphicsItem *> itemList = items();
    for (int i = 0; i < itemList.size(); ++i)
    {
        QGraphicsProxyWidget *proxyWidget = qgraphicsitem_cast<QGraphicsProxyWidget *>(itemList[i]);

        if (!proxyWidget)
            continue;

        if (proxyWidget == m_proxyTimeSlider)
        {
            QRectF rect = proxyWidget->geometry();
            rect.setWidth( w );

            proxyWidget->setGeometry( rect );
        }
        else if (proxyWidget == m_proxyTimeSliderBar)
        {
            QRectF rect = proxyWidget->geometry();
            rect.setHeight( h );

            proxyWidget->setGeometry( rect );
        }
    }
}

int TrackScene::getTimeSliderValueFromPosition( QPointF pos )
{
    QPointF itemPos = m_proxyTimeSlider->mapFromScene( pos );

    TimeSlider* slider = static_cast<TimeSlider*>(m_proxyTimeSlider->widget());

    int val = QStyle::sliderValueFromPosition( slider->minimum(),
                                               slider->maximum(),
                                               itemPos.x(),
                                               slider->width() );

    return val;
}

float TrackScene::getTimeSliderPositionFromValue( int val)
{
    TimeSlider* slider = static_cast<TimeSlider*>(m_proxyTimeSlider->widget());

    QPointF pos( slider->getSliderPositionFromValue( val), 0 );
    QPointF itemPos = m_proxyTimeSlider->mapToScene( pos );

    return itemPos.x();
}

bool TrackScene::isInTimeSliderRange( int frame)
{
    TimeSlider* slider = static_cast<TimeSlider*>(m_proxyTimeSlider->widget());

    return frame <= slider->maximum() && frame >= slider->minimum();
}

void TrackScene::onDurationChanged( int length)
{
    setDuration( length );
}
