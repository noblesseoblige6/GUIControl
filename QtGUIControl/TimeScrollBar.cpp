
TimeScrollBar::TimeScrollBar(QWidget *parent)
    : QScrollBar(parent)
    , m_minScope(10)
{
}

TimeScrollBar::~TimeScrollBar()
{
}

void TimeScrollBar::mousePressEvent( QMouseEvent* event )
{
    QScrollBar::mousePressEvent( event );

    QStyleOptionSlider opt;
    initStyleOption( &opt );

    opt.subControls = QStyle::SC_ScrollBarSlider;
    QRect barRect = style()->subControlRect( QStyle::CC_ScrollBar, &opt, QStyle::SC_ScrollBarSlider, this );

    opt.subControls = QStyle::SC_ScrollBarSubLine;
    QRect subRect = style()->subControlRect( QStyle::CC_ScrollBar, &opt, QStyle::SC_ScrollBarSubLine, this );

    int x = event->pos().x();
    int barLeft = barRect.left();
    int barRight = barRect.right();
    int scaleRange = subRect.width();

    if (x >= barLeft && x <= barLeft+scaleRange)
    {
        m_status = SCALE_LEFT;
        m_prevScope = m_leftScope;
    }
    else if (x < barRight - scaleRange)
    {
        m_status = MOVE;
    }
    else if(x <= barRight)
    {
        m_status = SCALE_RIGHT;
        m_prevScope = m_rightScope;
    }

    m_mousePos = event->pos();
}

void TimeScrollBar::mouseMoveEvent( QMouseEvent* event )
{
    int d = event->pos().x() - m_mousePos.x();
    switch (m_status)
    {
    case MOVE:
        QScrollBar::mouseMoveEvent( event );
        emit moved( value(), m_leftScope, m_rightScope );
        break;
    case SCALE_LEFT:
    {
        int tmp = qBound( 0, m_prevScope - d, value()  - minimum());
        m_leftScope = tmp;

        if (m_rightScope + m_leftScope < m_minScope)
            m_leftScope = m_minScope - m_rightScope;

        emit moved( value(), m_leftScope, m_rightScope );
        break;
    }
    case SCALE_RIGHT:
    {
        int tmp = qBound( 0, m_prevScope + d, maximum() - value() );
        m_rightScope = tmp;
        
        if (m_rightScope + m_leftScope < m_minScope)
            m_rightScope = m_minScope - m_leftScope;

        emit moved( value(), m_leftScope, m_rightScope );
        break;
    }
    default:
        break;
    }

    setPageStep( m_leftScope + m_rightScope );
    setSingleStep( m_leftScope + m_rightScope );

    //qDebug() << m_leftScope << " " << m_rightScope << value() ;
}

void TimeScrollBar::mouseReleaseEvent( QMouseEvent* event )
{
    m_status = NONE;
    QScrollBar::mouseReleaseEvent( event );
}

void TimeScrollBar::paintEvent( QPaintEvent* event )
{
    QScrollBar::paintEvent( event );

    QStyleOptionSlider opt;
    initStyleOption( &opt );

    opt.subControls = QStyle::SC_ScrollBarSlider;
    QRect barRect = style()->subControlRect( QStyle::CC_ScrollBar, &opt, QStyle::SC_ScrollBarSlider, this );

    opt.subControls = QStyle::SC_ScrollBarSubLine;
    QRect subRect = style()->subControlRect( QStyle::CC_ScrollBar, &opt, QStyle::SC_ScrollBarSubLine, this );

    QPainter painter(this);
    painter.setRenderHint( QPainter::Antialiasing, true );

    subRect.moveTopLeft( barRect.topLeft() );
    painter.fillRect( subRect, QBrush(Qt::blue) );

    subRect.moveTopRight( barRect.topRight() );
    painter.fillRect( subRect, QBrush( Qt::blue ) );
}

void TimeScrollBar::setLength( int length )
{
    m_length = length; 
    
    setMaximum( length ); 
    
    m_leftScope = 0;
    m_rightScope = length;

    setPageStep( m_leftScope + m_rightScope );
    setSingleStep(m_leftScope + m_rightScope);
}
