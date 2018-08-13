
TrackLine::TrackLine(QWidget *parent)
    : QGraphicsView(parent)
{
    setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

    m_scene = new TrackScene(parent);

    m_timeSlider = new TimeSlider();
    m_scene->setTimeSliderWidget( m_timeSlider );

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

    QList<QGraphicsItem *> itemList = m_scene->items();
    for (int i = 0; i < itemList.size(); ++i)
    {
        QGraphicsProxyWidget *proxyWidget = qgraphicsitem_cast<QGraphicsProxyWidget *>(itemList[i]);
        if (!proxyWidget)
            continue;

        if (proxyWidget->widget() != m_timeSlider)
            continue;

        QRectF rect = QRectF( 0.f, 0.f, w, proxyWidget->geometry().height() );
        proxyWidget->setGeometry( rect );
    }
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
