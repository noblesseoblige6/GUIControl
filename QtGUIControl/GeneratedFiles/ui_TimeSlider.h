/********************************************************************************
** Form generated from reading UI file 'TimeSlider.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMESLIDER_H
#define UI_TIMESLIDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TimeSlider
{
public:
    QSlider *horizontalSlider;

    void setupUi(QWidget *TimeSlider)
    {
        if (TimeSlider->objectName().isEmpty())
            TimeSlider->setObjectName(QStringLiteral("TimeSlider"));
        TimeSlider->resize(651, 459);
        horizontalSlider = new QSlider(TimeSlider);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(110, 180, 160, 22));
        horizontalSlider->setOrientation(Qt::Horizontal);

        retranslateUi(TimeSlider);

        QMetaObject::connectSlotsByName(TimeSlider);
    } // setupUi

    void retranslateUi(QWidget *TimeSlider)
    {
        TimeSlider->setWindowTitle(QApplication::translate("TimeSlider", "TimeSlider", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TimeSlider: public Ui_TimeSlider {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMESLIDER_H
