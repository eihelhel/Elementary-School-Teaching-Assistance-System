/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLabel *iplabel;
    QLineEdit *iplineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *portlabel;
    QLineEdit *portlineEdit;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(270, 132);
        widget = new QWidget(Widget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(10, 10, 247, 99));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        iplabel = new QLabel(widget);
        iplabel->setObjectName("iplabel");

        horizontalLayout->addWidget(iplabel);

        iplineEdit = new QLineEdit(widget);
        iplineEdit->setObjectName("iplineEdit");

        horizontalLayout->addWidget(iplineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        portlabel = new QLabel(widget);
        portlabel->setObjectName("portlabel");

        horizontalLayout_2->addWidget(portlabel);

        portlineEdit = new QLineEdit(widget);
        portlineEdit->setObjectName("portlineEdit");

        horizontalLayout_2->addWidget(portlineEdit);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        label->setText(QCoreApplication::translate("Widget", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; font-weight:700;\">\346\234\215\345\212\241\345\231\250</span></p></body></html>", nullptr));
        iplabel->setText(QCoreApplication::translate("Widget", "\345\234\260\345\235\200", nullptr));
        portlabel->setText(QCoreApplication::translate("Widget", "\347\253\257\345\217\243", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
