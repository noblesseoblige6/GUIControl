#pragma once
#include "ui_TrackLine.h"

class TimeSlider;
class TrackLine : public QGraphicsView
{
    Q_OBJECT

public:
    TrackLine(QWidget *parent = Q_NULLPTR);
    ~TrackLine();

protected:
    void mousePressEvent( QMouseEvent *event );
    void resizeEvent( QResizeEvent *event );

public:
    TimeSlider* m_timeSlider;

private:
    Ui::TrackLine ui;

    QGraphicsScene* m_scene;

    QGraphicsProxyWidget* proxyWidget;
};
