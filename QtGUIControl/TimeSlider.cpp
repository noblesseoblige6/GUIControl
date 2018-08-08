#include "TimeSlider.h"

TimeSlider::TimeSlider( QWidget *parent )
    : QSlider( parent )
    , m_currentFrame( 0 )
    , m_length( 100 )
    , m_scale( 1.0f )
    , m_interval( 5.0f )
    , m_longBarCount( 5 )
    , m_offset( QPoint( 5, 10 ) )
    , m_labelSize( 10 )
    , m_labelCount( 5 )
    , m_handleColor( QColor( 255, 0, 0, 128 ) )
    , m_grooveColor( Qt::black )
{
    QVBoxLayout *verticalLayout = new QVBoxLayout();

    m_rangeSlider = new QScrollBar( this );
    m_rangeSlider->setObjectName( QStringLiteral( "scroll" ) );
    m_rangeSlider->setMaximum( 0 );
    m_rangeSlider->setOrientation( Qt::Horizontal );

    m_scaleSlider = new QSlider( this );
    m_scaleSlider->setObjectName( QStringLiteral( "scaler" ) );
    m_scaleSlider->setMinimum( 0 );
    m_scaleSlider->setMaximum( 100 );
    m_scaleSlider->setValue( 100 );
    m_scaleSlider->setOrientation( Qt::Horizontal );

    // time vertical bar
    m_pTimeBar = new TimeSliderBar( parent );
    m_pTimeBar->setObjectName( "TimeLineBar" );
    m_pTimeBar->setColor( m_handleColor );

    verticalLayout->addWidget( m_rangeSlider );
    verticalLayout->addWidget( m_scaleSlider );
    verticalLayout->addWidget( m_pTimeBar );

    setLayout( verticalLayout );

    setValue( 0 );
    setRange( 0, m_length );

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

    connect( m_scaleSlider, SIGNAL( valueChanged( int ) ), this, SLOT( onScaleChanged( int ) ) );
    connect( m_rangeSlider, SIGNAL( valueChanged( int ) ), this, SLOT( onRangeChanged( int ) ) );
}

TimeSlider::~TimeSlider()
{
}

void TimeSlider::onScaleChanged( int val )
{
    m_scale = static_cast<float>(val + 1) / 100.0f;

    m_rangeSlider->setMaximum( m_scale*99 );

    int range = qMax( 1, static_cast<int>(m_length * m_scale) );
    int min = minimum();
    int max = min + range;

    setRange( min, max );

    // overwrite value because handle position is based on this value
    setValue( m_currentFrame );
}

void TimeSlider::onRangeChanged( int val )
{
    int min = static_cast<float>(val) / 99.0f * m_length;
    int max = min + getRange();

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
    drawGroove( painter, grooveRect );
    drawHandle( painter, handleRect );
}

void TimeSlider::drawGroove( QPainter& painter, QRect& rect )
{
    painter.setPen( QPen( m_grooveColor, 1, Qt::SolidLine, Qt::SquareCap ) );

    int startX = rect.left() + m_offset.x(), endX = rect.right() - m_offset.x();
    int startY = rect.center().y(), endY = m_offset.y() + startY;

    int largeCount = qMax( m_longBarCount, static_cast<int>(m_longBarCount * (1.0f - m_scale)) );
    int labelCount = qMax( 3, static_cast<int>(m_labelCount * m_scale) );

    QVector<QLineF> lines;

    // vertical bar for time line
    lines.append( QLineF( startX, endY, endX, endY ) );

    int range = getRange();
    float division = 1.0f / range;

    int w = endX - startX;
    float interval = w * division;
    float prev = -m_interval;
    int barCount = 0;

    for (int i = 0; i <= range; ++i)
    {
        float x = startX + i * interval;

        if (x - prev < m_interval)
            continue;

        if (barCount % largeCount == 0)
        {
            lines.append( QLineF( x, startY, x, endY ) );

            if (barCount % labelCount == 0)
                drawLabel( painter, minimum() + i, QPoint( x, startY ) );
        }
        else
            lines.append( QLineF( x, endY - 5, x, endY ) );

        prev = x;
        barCount++;
    }

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
