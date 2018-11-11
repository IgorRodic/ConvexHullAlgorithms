/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDial>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include <graphview.h>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *brojTacaka;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_4;
    QPushButton *ucitavanjeFajla;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QDial *brzinaAnimacije;
    QLabel *label;
    QPushButton *naivniAlgoritam;
    QPushButton *gremovAlgoritam;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *uputstvo;
    GraphView *graphicsView;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(1174, 710);
        Widget->setStyleSheet(QStringLiteral(""));
        gridLayout = new QGridLayout(Widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        brojTacaka = new QLineEdit(Widget);
        brojTacaka->setObjectName(QStringLiteral("brojTacaka"));
        brojTacaka->setStyleSheet(QStringLiteral("background-color: rgb(167, 167, 167)"));

        horizontalLayout->addWidget(brojTacaka);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label_4 = new QLabel(Widget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout->addWidget(label_4);

        ucitavanjeFajla = new QPushButton(Widget);
        ucitavanjeFajla->setObjectName(QStringLiteral("ucitavanjeFajla"));
        ucitavanjeFajla->setStyleSheet(QStringLiteral("background-color: rgb(167, 167, 167)"));

        horizontalLayout->addWidget(ucitavanjeFajla);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_3 = new QLabel(Widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        brzinaAnimacije = new QDial(Widget);
        brzinaAnimacije->setObjectName(QStringLiteral("brzinaAnimacije"));
        brzinaAnimacije->setStyleSheet(QStringLiteral("background-color: rgb(107, 107, 107)"));
        brzinaAnimacije->setMinimum(1);
        brzinaAnimacije->setMaximum(2000);
        brzinaAnimacije->setSingleStep(50);
        brzinaAnimacije->setPageStep(50);
        brzinaAnimacije->setWrapping(false);
        brzinaAnimacije->setNotchesVisible(true);

        horizontalLayout->addWidget(brzinaAnimacije);

        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        naivniAlgoritam = new QPushButton(Widget);
        naivniAlgoritam->setObjectName(QStringLiteral("naivniAlgoritam"));
        naivniAlgoritam->setStyleSheet(QStringLiteral("background-color: rgb(167, 167, 167)"));

        horizontalLayout->addWidget(naivniAlgoritam);

        gremovAlgoritam = new QPushButton(Widget);
        gremovAlgoritam->setObjectName(QStringLiteral("gremovAlgoritam"));
        gremovAlgoritam->setStyleSheet(QStringLiteral("background-color: rgb(167, 167, 167)"));

        horizontalLayout->addWidget(gremovAlgoritam);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        uputstvo = new QPushButton(Widget);
        uputstvo->setObjectName(QStringLiteral("uputstvo"));
        uputstvo->setStyleSheet(QStringLiteral("background-color: rgb(167, 167, 167)"));

        horizontalLayout->addWidget(uputstvo);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);

        graphicsView = new GraphView(Widget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::NoBrush);
        graphicsView->setBackgroundBrush(brush);
        QBrush brush1(QColor(255, 255, 255, 0));
        brush1.setStyle(Qt::SolidPattern);
        graphicsView->setForegroundBrush(brush1);

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Elasticni graf", Q_NULLPTR));
        label_2->setText(QApplication::translate("Widget", "Broj ta\304\215aka", Q_NULLPTR));
        label_4->setText(QApplication::translate("Widget", "U\304\215itavanje iz fajla ", Q_NULLPTR));
        ucitavanjeFajla->setText(QApplication::translate("Widget", "Open...", Q_NULLPTR));
        label_3->setText(QApplication::translate("Widget", "Brzina animacije:", Q_NULLPTR));
        label->setText(QApplication::translate("Widget", "Generi\305\241i konveksni omota\304\215", Q_NULLPTR));
        naivniAlgoritam->setText(QApplication::translate("Widget", "Naivni algoritam", Q_NULLPTR));
        gremovAlgoritam->setText(QApplication::translate("Widget", "Gremov algoritam", Q_NULLPTR));
        uputstvo->setText(QApplication::translate("Widget", "Uputstvo", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
