
TrackScene::TrackScene( QObject *parent )
    : QGraphicsScene( parent )
    , m_duration( 0 )
{
}

TrackScene::~TrackScene()
{
}

void TrackScene::addItem( Clip *item )
{
    connect( this, SIGNAL( timeScaleChanged() ), item, SLOT( onChanged() ) );
    connect( this, SIGNAL( timeRangeChanged() ), item, SLOT( onChanged() ));
    
    QGraphicsScene::addItem( item );
}

void TrackScene::setTimeSliderWidget( TimeSlider* timeSlider )
{
    connect( timeSlider, SIGNAL( durationChanged( int ) ), this, SLOT( onDurationChanged( int ) ) );

    m_proxyTimeSlider = QGraphicsScene::addWidget( timeSlider );
    m_proxyTimeSlider->setZValue( 100.0f );
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
