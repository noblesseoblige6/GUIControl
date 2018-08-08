#include "TrackLine.h"

TrackLine::TrackLine(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    m_graphicsView = new QGraphicsView();
    m_scene = new QGraphicsScene();

    QGraphicsRectItem *rect_item = new QGraphicsRectItem( 50, 50, 100, 100 );
    QPushButton* label = new QPushButton();
    label->setText( "TesT" );
    m_scene->addItem( rect_item );
    rect_item->setRotation( 45 );

    QGraphicsProxyWidget* proxyWidget = m_scene->addWidget( label );
    proxyWidget->setRotation( 90 );

    m_graphicsView->setScene( m_scene );
    //m_graphicsView->show();
}

TrackLine::~TrackLine()
{
}
