#pragma once

class Clip;
class TimeLineScene : public QGraphicsScene
{
    Q_OBJECT

public:
    TimeLineScene(QObject *parent = nullptr);
    ~TimeLineScene();

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
