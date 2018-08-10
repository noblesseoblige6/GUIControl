#pragma once

#include <QWidget>
#include <QFrame>
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>

class TimeSliderBar : public QFrame
{
    Q_OBJECT
        Q_DISABLE_COPY( TimeSliderBar )

public:
    TimeSliderBar( QWidget *parent = nullptr);

    ~TimeSliderBar();

public: // accessors
    int getRange() const { return m_range; }
    void setRange( int range ) { m_range = range; }

    int getBarWidth() const { return m_barWidth; }
    void setBarWidth( int barWidth ) { m_barWidth = barWidth; }

    const QColor& getColor() const { return m_color; }
    void setColor( const QColor& color ) { m_color = color; }

protected: // events
    void mousePressEvent( QMouseEvent *event );
    void mouseMoveEvent( QMouseEvent *event );

    void paintEvent( QPaintEvent* event );

signals:
    void barMoved( int );

public slots :
    void onTimelineChanged( QPoint );

private:
    int    m_range;
    int    m_barWidth;
    QColor m_color;

    QPoint m_mousePos;
};
