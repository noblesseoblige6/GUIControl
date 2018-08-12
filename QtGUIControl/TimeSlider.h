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

    bool isFrameInRange() { return m_currentFrame <= maximum() && m_currentFrame >= minimum(); }

public:
    const QColor& getHandleColor() const { return m_handleColor; }
    void setHandleColor( const QColor& color ) { m_handleColor = color; }

    const QColor& getGrooveColor() const { return m_grooveColor; }
    void setGrooveColor( const QColor& color ) { m_grooveColor = color; }

    int getCurrentFrame() const { return m_currentFrame; }
    void setCurrentFrame( int frame );

    int getRange() const { return maximum() - minimum(); }
signals:
    void sliderMoved( QPoint );

    public slots :
    void onScaleChanged( int val );
    void onRangeChanged( int val );
    void onSliderValueChanged( int val );
    void onTimeBarChanged( int );

private:
    int m_currentFrame;

    int m_length;
    float m_scale;

    int m_interval;
    int m_longBarCount;

    int m_labelSize;
    int m_labelCount;

    QColor m_handleColor;
    QColor m_grooveColor;

    QVector<QPoint> m_handleShape;

    TimeSliderBar* m_pTimeBar;
};
