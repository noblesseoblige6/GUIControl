
TimeSlider::TimeSlider( QWidget *parent )
    : QSlider( parent )
    , m_currentFrame( 0 )
    , m_duration( 100 )
    , m_timeScale( 1.0f )
    , m_interval( 10 )
    , m_longBarCount( 5 )
    , m_labelSize( 10 )
    , m_handleColor( QColor( 255, 0, 0, 128 ) )
    , m_grooveColor( Qt::black )
{
    // time vertical bar
    m_pTimeBar = new TimeSliderBar(this);
    m_pTimeBar->setObjectName( "TimeLineBar" );
    m_pTimeBar->setColor( m_handleColor );

    setValue( 0 );
    setRange( 0, m_duration );

    setOrientation( Qt::Horizontal );

    installEventFilter( this );

    m_handleShape = QVector<QPoint>
    {
        QPoint( -10, -10 ),
        QPoint( 10, -10 ),
        QPoint( 0, 10 ),
    };

    // signal/slot
    connect( this, SIGNAL( valueChanged( int ) ), SLOT( onSliderValueChanged( int ) ) );
    connect( this, SIGNAL( rangeChanged( int, int ) ), SLOT( onSliderRangeChanged() ) );
    connect( this, SIGNAL( sliderMoved( QPoint ) ), m_pTimeBar, SLOT( onTimelineChanged( QPoint ) ) );
    connect( m_pTimeBar, SIGNAL( barMoved( int ) ), this, SLOT( onTimeBarChanged( int ) ) );
}

TimeSlider::~TimeSlider()
{
}

void TimeSlider::setDuration( int length )
{
    m_duration = length; 

    int min = minimum();
    int max = m_duration;

    setRange( min, max );

    emit durationChanged( m_duration );
}

int TimeSlider::getSliderPositionFromValue( int val )
{
    QStyleOptionSlider opt;

    opt.subControls = QStyle::SC_SliderHandle;
    QRect rect = style()->subControlRect( QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this );

    int length = width() - rect.width();

    return (float)(val-minimum()) / (float)getRange() * length;
}

void TimeSlider::onTimeScaleChanged( int val )
{
    m_timeScale = static_cast<float>(val + 1) / 100.0f;

    int range = qMax( 10, static_cast<int>(m_duration * m_timeScale * 0.5) );
    
    int min, max;
    if (isFrameInRange())
    {
        min = qMax( 0, m_currentFrame - range );
        max = qMin( m_currentFrame + range, m_duration );
    }
    else
    {
        min = minimum();
        max = qMin( min + range, m_duration );
    }

    setRange( min, max );

    // overwrite value because handle position is based on this value
    setValue( m_currentFrame );
}

void TimeSlider::onTimeRangeChanged( int val )
{
    int range = qMax( 10, static_cast<int>(m_duration * m_timeScale) );
    int min = static_cast<float>(val) / 99.0f * m_duration;
    int max = qMin( min + range, m_duration );

    if (max == m_duration)
        min = max - range;

    setRange( min, max );

    // overwrite value because handle position is based on this value
    setValue( m_currentFrame );
}

void TimeSlider::onSliderValueChanged( int val )
{
    if (isFrameInRange() && m_currentFrame != val)
        m_currentFrame = val;
}

void TimeSlider::onTimeBarChanged( int pos )
{
    int val = QStyle::sliderValueFromPosition( minimum(), maximum(), pos, width() );
    setCurrentFrame( val );
}

bool TimeSlider::eventFilter( QObject* watched, QEvent* event )
{
    if (watched == this)
    {
        if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseMove)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

            if (mouseEvent->buttons() & Qt::LeftButton)
            {
                // find slider value from mouse clicked position
                int val = QStyle::sliderValueFromPosition( minimum(), maximum(), mouseEvent->x(), width() );

                if (val != getCurrentFrame())
                {
                    setCurrentFrame( val );
                }

                QStyle::sliderPositionFromValue(minimum(), maximum(), val, width() );
                return true;
            }
        }
    }

    return QSlider::eventFilter( watched, event );
}
void TimeSlider::paintEvent( QPaintEvent* event )
{
    QStyleOptionSlider opt;
    initStyleOption( &opt );

    opt.subControls = QStyle::SC_SliderHandle;
    QRect handleRect = style()->subControlRect( QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this );

    opt.subControls = QStyle::SC_SliderGroove;
    QRect grooveRect = style()->subControlRect( QStyle::CC_Slider, &opt, QStyle::SC_SliderGroove, this );

    QSlider::paintEvent( event );

    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing, true );

    // remove already drawn ui
    painter.eraseRect( grooveRect );
    painter.eraseRect( handleRect );

    // start to draw
    drawGroove( painter, handleRect );
    drawHandle( painter, handleRect );
}

void TimeSlider::drawGroove( QPainter& painter, QRect& rect )
{
    painter.setPen( QPen( m_grooveColor, 1, Qt::SolidLine, Qt::SquareCap ) );

    float startX = rect.width()*0.5;
    float startY = rect.center().y(), endY = startY + m_labelSize;

    int largeCount =  qMax( m_longBarCount, static_cast<int>(m_longBarCount * (1.0f - m_timeScale)) );

    QVector<QLine> lines;

    int range = getRange();
    int prev = -m_interval;
    int barCount = 0;

    for (int i = minimum(); i <= maximum(); ++i)
    {
        int x = getSliderPositionFromValue(i) + startX;

        if (x - prev < m_interval)
            continue;

        if (barCount % largeCount == 0)
        {
            lines.append( QLine( x, startY, x, endY ) );

            drawLabel( painter, i, QPoint( x, startY ) );
        }
        else
            lines.append( QLine( x, endY - 5, x, endY ) );

        prev = x;
        barCount++;
    }

    // vertical bar for time line
    lines.append( QLine( startX, endY, prev, endY ) );

    painter.drawLines( lines );
}

void TimeSlider::drawHandle( QPainter& painter, QRect& rect )
{
    bool canDraw = isFrameInRange();
    m_pTimeBar->setVisible( canDraw );

    if (!canDraw)
        return;

    painter.setPen( QPen( m_handleColor, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin ) );
    painter.setBrush( m_handleColor );
    
    painter.translate( rect.center() );

    painter.drawPolygon( m_handleShape );

    emit sliderMoved( rect.center() );
}

void TimeSlider::drawLabel( QPainter& painter, int value, QPoint& point )
{
    QString label;
    label.sprintf( "%d", value );
    painter.drawText( point, label );
}

void TimeSlider::setCurrentFrame( int frame )
{
    m_currentFrame = frame;
    setValue( frame );
}
