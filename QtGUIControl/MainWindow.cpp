
MainWindow::MainWindow( QWidget *parent )
    : QMainWindow( parent )
{
    ui.setupUi( this );

    //connect( ui.TimeLineView->getTimeSlider(), SIGNAL( timeScaleChanged( int, int ) ), ui.TimeRange, SLOT( onTimeScaleChanged( int, int ) ) );
    connect( ui.TimeLineView->getTimeSlider(), SIGNAL( durationChanged( int ) ), this, SLOT( onDurationChanged( int ) ) );
    //connect( ui.TimeLineView->getTimeSlider(), SIGNAL( currentFrameChanged( int ) ), ui.TimeRange, SLOT( onCurrentFrameChanged( int )) );
    //connect( ui.TimeScale, SIGNAL( valueChanged( int ) ), ui.TimeLineView, SLOT( onTimeScaleChanged( int ) ) );
    //connect( ui.TimeRange, SIGNAL( valueChanged( int ) ), ui.TimeLineView, SLOT( onTimeRangeChanged( int ) ) );
    connect( ui.TimeScroll, SIGNAL( moved( int, int, int ) ), ui.TimeLineView, SLOT( onTimeRangeChanged( int, int, int ) ) );

    ui.TimeLineView->getTimeSlider()->setDuration( 100 );

    SceneClip* clip = new SceneClip( QRectF( 5, 0, 100, 100 ) );
    ui.TimeLineView->getScene()->addItem( clip );
}

void MainWindow::onDurationChanged( int val )
{
    ui.TimeScroll->setLength( val );
}
