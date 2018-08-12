
MainWindow::MainWindow( QWidget *parent )
    : QMainWindow( parent )
{
    ui.setupUi( this );

    connect( ui.TimeScale, SIGNAL( valueChanged( int ) ), ui.TrackView, SLOT( onTimeScaleChanged( int ) ) );
    connect( ui.TimeRange, SIGNAL( valueChanged( int ) ), ui.TrackView, SLOT( onTimeRangeChanged( int ) ) );
}

void MainWindow::onTimeScaleChanged( int val )
{
    float scale = (val + 1) / 100.0f;
    ui.TimeRange->setMaximum( scale *99 );
}
