
MainWindow::MainWindow( QWidget *parent )
    : QMainWindow( parent )
{
    ui.setupUi( this );

    connect( ui.TimeLineView->getTimeSlider(), SIGNAL( timeScaleChanged( int ) ), this, SLOT( onTimeScaleChanged( int ) ) );
    connect( ui.TimeLineView->getTimeSlider(), SIGNAL( durationChanged( int ) ), this, SLOT( onDurationChanged( int )) );
    connect( ui.TimeScale, SIGNAL( valueChanged( int ) ), ui.TimeLineView, SLOT( onTimeScaleChanged( int ) ) );
    connect( ui.TimeRange, SIGNAL( valueChanged( int ) ), ui.TimeLineView, SLOT( onTimeRangeChanged( int ) ) );

    ui.TimeLineView->getTimeSlider()->setDuration( 100 );

    Clip* clip = new Clip( QRectF( 5, 0, 100, 100 ) );
    ui.TimeLineView->getScene()->addItem( clip );
}

void MainWindow::onTimeScaleChanged( int value )
{
    int duration = ui.TimeLineView->getTimeSlider()->getDuration();
    int range = ui.TimeLineView->getTimeSlider()->getRange();

    int max = duration - range;

    int oldMax = qMax( 1, ui.TimeRange->maximum() );
    int oldVal = ui.TimeRange->value();
    int val = oldVal / oldMax * max;
    
    ui.TimeRange->setMaximum( max );
    ui.TimeRange->setValue( val );

    //qDebug() <<oldVal << " " << ui.TimeRange->value();
}

void MainWindow::onDurationChanged( int val )
{
    ui.TimeScale->setMaximum( val );
    ui.TimeScale->setValue( val );
}
