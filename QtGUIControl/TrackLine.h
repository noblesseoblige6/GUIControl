#pragma once

#include <QWidget>
#include "ui_TrackLine.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QPushButton>
#include <QLayout>

class TrackLine : public QWidget
{
    Q_OBJECT

public:
    TrackLine(QWidget *parent = Q_NULLPTR);
    ~TrackLine();

private:
    Ui::TrackLine ui;

    QGraphicsView* m_graphicsView;
    QGraphicsScene* m_scene;
    QList<QGraphicsScene*> m_sceneItems;
};
