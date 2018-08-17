#pragma once

class TimeSlider;
class TimeLineScene;

class TimeLine : public QGraphicsView
{
    Q_OBJECT

public:
    TimeLine(QWidget *parent = Q_NULLPTR);
    ~TimeLine();

protected:
    void mousePressEvent( QMouseEvent *event );
    void resizeEvent( QResizeEvent *event );

    public slots:
    void onTimeScaleChanged(int val);
    void onTimeRangeChanged( int val );

private:
    TimeSlider* m_timeSlider;
    TimeLineScene* m_scene;
};
