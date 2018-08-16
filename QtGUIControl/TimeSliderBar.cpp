#include "TimeSliderBar.h"

TimeSliderBar::TimeSliderBar( QWidget *parent )
    : QFrame( parent )
    , m_range( 3 )
    , m_barWidth( 1 )
    , m_color( Qt::red )
{
    setFrameShape( QFrame::Box );
}

TimeSliderBar::~TimeSliderBar()
{
}

void TimeSliderBar::mousePressEvent( QMouseEvent *event )
{
    // clicked left button
    if (event->button() == Qt::LeftButton)
    {
        m_mousePos = event->pos();
    }

    QFrame::mousePressEvent( event );
}

void TimeSliderBar::mouseMoveEvent( QMouseEvent *event )
{
    if (event->buttons() & Qt::LeftButton)
    {
        QPoint delta = event->pos() - m_mousePos;
        QPoint curPos = pos() + delta;

        emit barMoved( curPos.x() );
    }

    QFrame::mouseMoveEvent( event );
}

void TimeSliderBar::paintEvent( QPaintEvent* event )
{
    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing, true );
    painter.setPen( QPen( m_color, m_barWidth, Qt::SolidLine, Qt::SquareCap ) );

    QPoint start( width()*0.5f, 0 );
    QPoint end( width()*0.5f, height() );

    painter.drawLine( QLine( start, end ) );
}

void TimeSliderBar::onTimelineChanged( QPoint point )
{
    const QObjectList& children = parent()->children();
    if (children.last() != this)
        raise();

    QRect rect( point.x() - m_range*0.5, point.y(), m_range, height() );
    setGeometry( rect );

    update();
}
