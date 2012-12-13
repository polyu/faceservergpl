/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Dec 5 15:56:17 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPlainTextEdit *statusText;
    QLabel *label;
    QPushButton *reloadButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(400, 300);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        statusText = new QPlainTextEdit(centralWidget);
        statusText->setObjectName(QString::fromUtf8("statusText"));
        statusText->setEnabled(true);
        statusText->setGeometry(QRect(10, 40, 381, 251));
        statusText->setReadOnly(true);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 65, 21));
        reloadButton = new QPushButton(centralWidget);
        reloadButton->setObjectName(QString::fromUtf8("reloadButton"));
        reloadButton->setGeometry(QRect(290, 10, 95, 21));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Face Server", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Status:", 0, QApplication::UnicodeUTF8));
        reloadButton->setText(QApplication::translate("MainWindow", "reload", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
