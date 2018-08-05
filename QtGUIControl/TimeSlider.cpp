#include "TimeSlider.h"

TimeSlider::TimeSlider( QWidget *parent )
    : QWidget( parent )
    , m_length( 512 )
    , m_scale( 1.0f )
    , m_range( 0 )
    , m_minInterval( 3 )
    , m_largeBarCount( 5 )
    , m_offset(QPoint(20, 10))
    , m_labelSize( 10 )
    , m_labelCount( 10 )
    , m_color( Qt::black )
    , m_lineWidth( 1 )
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

    verticalLayout->addWidget( m_rangeSlider );
    verticalLayout->addWidget( m_scaleSlider );

    setLayout( verticalLayout );

    connect( m_scaleSlider, SIGNAL( valueChanged( int ) ), this, SLOT( onScaleChanged( int ) ) );
    connect( m_rangeSlider, SIGNAL( valueChanged( int ) ), this, SLOT( onRangeChanged( int ) ) );
}

TimeSlider::~TimeSlider()
{
}

void TimeSlider::onScaleChanged( int val )
{
    m_scale = static_cast<float>(val) / 100.0f;

    int maxVal = 100 - val;
    int newVal = qMin( m_rangeSlider->value(), maxVal );
    m_rangeSlider->setMaximum( maxVal );
    m_rangeSlider->setValue( newVal );

    repaint();
}

void TimeSlider::onRangeChanged( int val )
{
    m_range = static_cast<float>(val) / m_rangeSlider->maximum() * m_length;
    int length = qMax( 1, static_cast<int>(m_length * m_scale) );

    if (m_range+ length >= m_length)
        return;

    repaint();
}

void TimeSlider::paintEvent( QPaintEvent* event )
{
    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing, true );
    painter.setPen( QPen( m_color, m_lineWidth, Qt::SolidLine, Qt::SquareCap ) );
    painter.setFont( QFont( "ÉÅÉCÉäÉI", m_labelSize ) );

    int startX = m_offset.x(), endX = width() - m_offset.x();
    int startY = m_labelSize, endY = m_offset.y() + m_labelSize;

    int largeCount = qMax( 1, static_cast<int>(m_largeBarCount * m_scale) );
    int labelCount = qMax( 3, static_cast<int>(m_labelCount * m_scale) );
    int length = qMax( 1, static_cast<int>(m_length * m_scale) );
    QVector<QLine> lines;

    // Vertial bar
    lines.append( QLine( startX, endY, endX, endY ) );

    // Horizonatal first bar
    drawLabel( painter, m_range, QPoint( startX, startY ) );
    lines.append( QLine( startX, startY, startX, endY ) );

    // Horizonatal last bar
    drawLabel( painter, m_range+length, QPoint( endX, startY ) );
    lines.append( QLine( endX, startY, endX, endY ) );

    float division = 1.0f / length;

    int w = endX - startX;
    float interval = w * division;
    int prev = startX;
    int barCount = 1;

    for (int i = 1; i < length; ++i)
    {
        int x = startX + i * interval;

        if (x - prev < m_minInterval)
            continue;

        if (barCount % largeCount == 0)
            lines.append( QLine( x, startY, x, endY ) );
        else
            lines.append( QLine( x, endY - 5, x, endY ) );

        if (barCount % labelCount == 0)
            drawLabel( painter, m_range+i, QPoint( x, startY ) );

        prev = x;
        barCount++;
    }

    painter.drawLines( lines );
}

void TimeSlider::drawLabel( QPainter& painter, int value, QPoint& point )
{
    QString label;
    label.sprintf( "%d", value );
    painter.drawText( point, label );
}
