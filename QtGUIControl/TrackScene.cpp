
TrackScene::TrackScene( QObject *parent )
    : QGraphicsScene( parent )
    , m_length( 0 )
    , m_timeScale( 1.0f )
{
}

TrackScene::~TrackScene()
{
}

void TrackScene::addItem( Clip *item )
{
    connect( this, SIGNAL( timeScaleChanged() ), item, SLOT( onTimeScaleChanged() ));
    
    QGraphicsScene::addItem( item );
}

QGraphicsProxyWidget* TrackScene::setTimeSliderWidget( TimeSlider* timeSlider )
{
    connect( timeSlider, SIGNAL( lengthChanged( int ) ), this, SLOT( onLengthChanged( int ) ) );

    m_proxyTimeSlider = QGraphicsScene::addWidget( timeSlider );

    return m_proxyTimeSlider;
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

    QPointF pos( slider->getSliderPositionFromValue(val), 0 );
    QPointF itemPos = m_proxyTimeSlider->mapToScene( pos );

    return itemPos.x();
}

void TrackScene::onLengthChanged( int length)
{
    setLength( length );
}
