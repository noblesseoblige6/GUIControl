#pragma once

class TimeScrollBar : public QScrollBar
{
    Q_OBJECT

public:
    enum STATUS
    {
        MOVE = 0,
        SCALE_LEFT,
        SCALE_RIGHT,
        NONE
    };

public:
    TimeScrollBar( QWidget *parent);
    ~TimeScrollBar();

    void setLength( int length );
protected:
    void mousePressEvent( QMouseEvent* event );
    void mouseMoveEvent( QMouseEvent* event );
    void mouseReleaseEvent( QMouseEvent* event );

signals:
    void moved(int, int, int);
    void scaled(int,int);

    public slots:

protected:
    void paintEvent( QPaintEvent* event );

private:
    STATUS m_status;

    int m_length;
    int m_leftScope;
    int m_rightScope;
    int m_minScope;
    int m_prevScope;
    QPoint m_mousePos;
};
