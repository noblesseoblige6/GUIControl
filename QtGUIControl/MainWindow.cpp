#include "MainWindow.h"
#include <QPainter>

MainWindow::MainWindow( QWidget *parent )
    : QMainWindow( parent )
{
    ui.setupUi( this );

    connect( ui.TimeScale, SIGNAL( valueChanged( int ) ), ui.TimeLine, SLOT( onScaleChanged( int ) ) );
    connect( ui.TimeRange, SIGNAL( valueChanged( int ) ), ui.TimeLine, SLOT( onRangeChanged( int ) ) );

}

void MainWindow::onTimeScaleChanged( int val )
{
    float scale = (val + 1) / 100.0f;
    ui.TimeRange->setMaximum( scale *99 );
}
