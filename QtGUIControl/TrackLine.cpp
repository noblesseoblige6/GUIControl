
TrackLine::TrackLine(QWidget *parent)
    : QGraphicsView(parent)
{
    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

    m_scene = new TrackScene(parent);

    m_timeSlider = new TimeSlider();
    m_scene->setTimeSliderWidget( m_timeSlider );
    m_timeSlider->setDuration( 100 );

    Clip* clip = new Clip( QRectF( 5, 0, 100, 100 ) );
    m_scene->addItem( clip );

    setScene( m_scene );

    setAlignment( Qt::AlignTop | Qt::AlignLeft );
    setMouseTracking( true );
}

TrackLine::~TrackLine()
{
}

void TrackLine::mousePressEvent( QMouseEvent* event )
{
    QGraphicsView::mousePressEvent( event );
}

void TrackLine::resizeEvent( QResizeEvent *event )
{
    int w = event->size().width();
    int h = event->size().height();
    m_scene->setSceneRect( 0, 0, w, h );

    m_scene->resizeTimeSlider( event->size() );

    QGraphicsView::resizeEvent( event );
}

void TrackLine::onTimeScaleChanged( int val )
{
    float scale = (float)(val + 1) / 100;
    m_timeSlider->onTimeScaleChanged( val );

    emit m_scene->timeScaleChanged();
}

void TrackLine::onTimeRangeChanged( int val )
{
    m_timeSlider->onTimeRangeChanged( val );

    emit m_scene->timeRangeChanged();
}
