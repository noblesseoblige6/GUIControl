#pragma once
#include "ui_TrackLine.h"

class TimeSlider;
class TrackScene;
class TrackLine : public QGraphicsView
{
    Q_OBJECT

public:
    TrackLine(QWidget *parent = Q_NULLPTR);
    ~TrackLine();

public:
    int getTimeSliderValueFromPosition(int pos);
    int getTimeSliderPositionFromValue();

protected:
    void mousePressEvent( QMouseEvent *event );
    void resizeEvent( QResizeEvent *event );

    public slots:
    void onTimeScaleChanged(int val);
    void onTimeRangeChanged( int val );
private:
    Ui::TrackLine ui;

    TimeSlider* m_timeSlider;
    TrackScene* m_scene;

    QGraphicsProxyWidget* proxyWidget;
};
