
TimeLine::TimeLine(QWidget *parent)
    : QGraphicsView(parent)
{
    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

    m_scene = new TimeLineScene(parent);

    m_timeSlider = new TimeSlider();
    m_scene->setTimeSliderWidget( m_timeSlider );

    setScene( m_scene );

    setAlignment( Qt::AlignTop | Qt::AlignLeft );
    setMouseTracking( true );
}

TimeLine::~TimeLine()
{
}

void TimeLine::mousePressEvent( QMouseEvent* event )
{
    QGraphicsView::mousePressEvent( event );
}

void TimeLine::resizeEvent( QResizeEvent *event )
{
    int w = event->size().width();
    int h = event->size().height();
    m_scene->setSceneRect( 0, 0, w, h );

    m_scene->resizeTimeSlider( event->size() );

    QGraphicsView::resizeEvent( event );
}

void TimeLine::onTimeScaleChanged( int val )
{
    m_timeSlider->onTimeScaleChanged( val );

    emit m_scene->timeScaleChanged();
}

void TimeLine::onTimeRangeChanged( int val, int left, int right )
{
    m_timeSlider->onTimeRangeChanged( val, left, right );

    emit m_scene->timeRangeChanged();
}
