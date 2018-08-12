
TrackScene::TrackScene( QObject *parent )
    : QGraphicsScene( parent )
    , m_length( 0 )
    , m_timeScale( 1.0f )
{
}

TrackScene::~TrackScene()
{
}

void TrackScene::addItem( Clip *item )
{
    connect( this, SIGNAL( timeScaleChanged() ), item, SLOT( onTimeScaleChanged() ));
    
    QGraphicsScene::addItem( item );
}

QGraphicsProxyWidget* TrackScene::addWidget( QWidget *widget, Qt::WindowFlags wFlags )
{
    connect( widget, SIGNAL( lengthChanged(int) ), this, SLOT( onLengthChanged(int) ) );

    return QGraphicsScene::addWidget( widget, wFlags );
}

void TrackScene::onLengthChanged( int length)
{
    setLength( length );
}
