#pragma once

class Clip;
class TrackScene : public QGraphicsScene
{
    Q_OBJECT

public:
    TrackScene(QObject *parent = nullptr);
    ~TrackScene();

    void addItem( Clip *item );

    void setLength( int length )
    {
        m_length = length;
    }

    int getLength() const { return m_length; }

    void setTimeScale( float scale )
    {
        m_timeScale = scale; 
        emit timeScaleChanged();
    }

    float getTimeScale() const { return m_timeScale; }

    float getPitch() const
    {
        return sceneRect().width() / (m_length * m_timeScale);
    }

    QGraphicsProxyWidget* setTimeSliderWidget( TimeSlider* timeSlider );

    int getTimeSliderValueFromPosition( QPointF );
    float getTimeSliderPositionFromValue( int );

signals:
    void timeScaleChanged();

    public slots:
    void onLengthChanged( int );

private:
    int m_length;
    float m_timeScale;
    QGraphicsProxyWidget* m_proxyTimeSlider;
};
