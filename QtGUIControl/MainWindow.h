#pragma once
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);

    public slots:
    void onDurationChanged(int);

private:
    Ui::MainWindowClass ui;
};
