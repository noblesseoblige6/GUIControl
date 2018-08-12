#pragma once
#include "ui_TrackLine.h"

class TrackLine : public QGraphicsView
{
    Q_OBJECT

public:
    TrackLine(QWidget *parent = Q_NULLPTR);
    ~TrackLine();

private:
    Ui::TrackLine ui;

    QGraphicsScene* m_scene;
    QList<QGraphicsScene*> m_sceneItems;
};
