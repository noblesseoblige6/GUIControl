#pragma once

class Clip;
class TrackScene : public QGraphicsScene
{
    Q_OBJECT

public:
    TrackScene(QObject *parent = nullptr);
    ~TrackScene();

    void addItem( Clip *item );

    void setDuration( int duration ){ m_duration = duration; }
    int getDuration() const { return m_duration; }

    void setTimeSliderWidget( TimeSlider* timeSlider );

    int getTimeSliderValueFromPosition( QPointF );
    float getTimeSliderPositionFromValue( int );

    bool isInTimeSliderRange( int );

signals:
    void timeScaleChanged();
    void timeRangeChanged();

    public slots:
    void onDurationChanged( int );

private:
    int   m_duration;

    QGraphicsProxyWidget* m_proxyTimeSlider;
};
