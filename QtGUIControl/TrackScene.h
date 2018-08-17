#pragma once

class Clip;
class TrackScene : public QGraphicsScene
{
    Q_OBJECT

public:
    TrackScene(QObject *parent = nullptr);
    ~TrackScene();

    void addItem( Clip *item );

    void setTimeSliderWidget( TimeSlider* timeSlider );
    void resizeTimeSlider(const QSizeF& size);
    int getTimeSliderValueFromPosition( QPointF );
    float getTimeSliderPositionFromValue( int );

    bool isInTimeSliderRange( int );

signals:
    void timeScaleChanged();
    void timeRangeChanged();

private:
    QGraphicsProxyWidget* m_proxyTimeSlider;
    QGraphicsProxyWidget* m_proxyTimeSliderBar;
};
