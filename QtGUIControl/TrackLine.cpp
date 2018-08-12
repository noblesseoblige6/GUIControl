
TrackLine::TrackLine(QWidget *parent)
    : QGraphicsView(parent)
{
    ui.setupUi(this);

    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

    m_scene = new TrackScene(parent);

    m_timeSlider = new TimeSlider();
    proxyWidget = m_scene->addWidget( m_timeSlider );
    m_timeSlider->setLength( 20 );
    proxyWidget->setPos( 0, 0 );

    Clip* clip = new Clip( QRectF( 5, proxyWidget->geometry().height(), 100, 100 ) );
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
    //qDebug() << event->pos();
    QGraphicsView::mousePressEvent( event );
}

void TrackLine::resizeEvent( QResizeEvent *event )
{
    int w = event->size().width();
    int h = event->size().height();
    m_scene->setSceneRect( 0, 0, w, h );

    QRectF rect = QRectF( 0.f, 0.f, w, proxyWidget->geometry().height() );
    proxyWidget->setGeometry( rect );

    QGraphicsView::resizeEvent( event );
}

void TrackLine::onTimeScaleChanged( int val )
{
    float scale = (float)(val + 1) / 100;
    m_timeSlider->onScaleChanged( val );
    m_scene->setTimeScale( scale );
}

void TrackLine::onTimeRangeChanged( int val )
{
    m_timeSlider->onRangeChanged( val );
}
