#pragma once
#include "TimeSliderBar.h"

class TimeSliderBar;

class TimeSlider : public QSlider
{
    Q_OBJECT

public:
    TimeSlider( QWidget *parent = Q_NULLPTR );
    ~TimeSlider();

protected:
    bool eventFilter( QObject* watched, QEvent* event );
    void paintEvent( QPaintEvent* event );

protected:
    void drawHandle( QPainter& painter, QRect& rect );
    void drawGroove( QPainter& painter, QRect& rect );
    void drawLabel( QPainter& painter, int value, QPoint& point );


public:
    const QColor& getHandleColor() const { return m_handleColor; }
    void setHandleColor( const QColor& color ) { m_handleColor = color; }

    const QColor& getGrooveColor() const { return m_grooveColor; }
    void setGrooveColor( const QColor& color ) { m_grooveColor = color; }

    int getCurrentFrame() const { return m_currentFrame; }
    void setCurrentFrame( int frame );

    int getRange() const { return maximum() - minimum(); }

    int getDuration() const { return m_duration; }
    void setDuration( int length );

    int getSliderPositionFromValue( int val );

    TimeSliderBar* getVertivalBar(){ return m_pTimeBar; }

    bool isFrameInRange() { return m_currentFrame <= maximum() && m_currentFrame >= minimum(); }


signals:
    void sliderMoved( QPoint );
    void durationChanged( int );
    void timeScaleChanged( int, int );
    void currentFrameChanged( int );

    public slots :
    void onTimeScaleChanged( int val );
    void onTimeRangeChanged( int val, int left, int right );
    void onSliderValueChanged( int val );
    void onTimeBarChanged( int );
    void onReachedBound(int);

private:
    int m_currentFrame;

    int m_duration;
    float m_timeScale;

    int m_interval;
    int m_longBarCount;

    int m_labelSize;

    QColor m_handleColor;
    QColor m_grooveColor;

    QVector<QPoint> m_handleShape;

    TimeSliderBar* m_pTimeBar;
};
