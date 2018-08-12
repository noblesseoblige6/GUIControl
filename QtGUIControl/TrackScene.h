#pragma once

class Clip;
class TrackScene : public QGraphicsScene
{
    Q_OBJECT

public:
    TrackScene(QObject *parent = nullptr);
    ~TrackScene();

    void addItem( Clip *item );

    QGraphicsProxyWidget* addWidget( QWidget *widget, Qt::WindowFlags wFlags = Qt::WindowFlags() );

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

signals:
    void timeScaleChanged();

    public slots:
    void onLengthChanged( int );

private:
    int m_length;
    float m_timeScale;
};
