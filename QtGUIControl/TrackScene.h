#pragma once

class Clip;
class TrackScene : public QGraphicsScene
{
    Q_OBJECT

public:
    TrackScene(QObject *parent = nullptr);
    ~TrackScene();

    void addItem( Clip *item );

    void setDuration( int duration )
    {
        m_duration = duration;
    }

    int getDuration() const { return m_duration; }

    void setTimeScale( float scale )
    {
        m_timeScale = scale; 
        emit timeScaleChanged();
    }

    float getTimeScale() const { return m_timeScale; }

    void setTimeSliderWidget( TimeSlider* timeSlider );

    int getTimeSliderValueFromPosition( QPointF );
    float getTimeSliderPositionFromValue( int );

signals:
    void timeScaleChanged();

    public slots:
    void onDurationChanged( int );

private:
    int   m_duration;
    float m_timeScale;
    QGraphicsProxyWidget* m_proxyTimeSlider;
};
