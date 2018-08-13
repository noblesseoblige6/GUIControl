#pragma once

class TimeSlider;
class TrackScene;

class TrackLine : public QGraphicsView
{
    Q_OBJECT

public:
    TrackLine(QWidget *parent = Q_NULLPTR);
    ~TrackLine();

protected:
    void mousePressEvent( QMouseEvent *event );
    void resizeEvent( QResizeEvent *event );

    public slots:
    void onTimeScaleChanged(int val);
    void onTimeRangeChanged( int val );

private:
    TimeSlider* m_timeSlider;
    TrackScene* m_scene;
};
