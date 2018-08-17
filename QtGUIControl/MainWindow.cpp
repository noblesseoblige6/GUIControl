
MainWindow::MainWindow( QWidget *parent )
    : QMainWindow( parent )
{
    ui.setupUi( this );

    connect( ui.TimeScale, SIGNAL( valueChanged( int ) ), ui.TimeLineView, SLOT( onTimeScaleChanged( int ) ) );
    connect( ui.TimeScale, SIGNAL( valueChanged( int ) ), this, SLOT( onTimeScaleChanged( int ) ) );
    connect( ui.TimeRange, SIGNAL( valueChanged( int ) ), ui.TimeLineView, SLOT( onTimeRangeChanged( int ) ) );
}

void MainWindow::onTimeScaleChanged( int val )
{
    float scale = 1.0f - ((val + 1) / 100.0f);
    
    int max = qMax(1, ui.TimeRange->maximum());

    int newMax = scale * 99;
    int newVal = ui.TimeRange->value() / max * newMax;

    ui.TimeRange->setMaximum( newMax );
    ui.TimeRange->setValue( newVal );
}
