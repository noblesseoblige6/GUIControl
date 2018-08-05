#pragma once

#include <QWidget>
#include <QScrollBar>
#include <QSlider>
#include <QPainter>
#include <QLine>
#include <QtGui>
#include <QtWidgets/QHBoxLayout>

class TimeSlider : public QWidget
{
    Q_OBJECT

public:
    TimeSlider( QWidget *parent = Q_NULLPTR );
    ~TimeSlider();

    public slots:
    void onScaleChanged( int val );
    void onRangeChanged( int val );

protected:
    void paintEvent( QPaintEvent* event );
    void drawLabel( QPainter&, int, QPoint& );

private:
    QSlider * m_scaleSlider;
    QScrollBar* m_rangeSlider;
    int m_length;
    float m_scale;
    int   m_range;
    int m_minInterval;
    int m_largeBarCount;

    QPoint m_offset;

    int m_labelSize;
    int m_labelCount;

    QColor m_color;
    int m_lineWidth;
};
