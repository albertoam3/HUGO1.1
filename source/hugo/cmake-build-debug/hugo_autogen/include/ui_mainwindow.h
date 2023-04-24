/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <myopenglwidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionswc_file;
    QWidget *centralwidget;
    myopenglwidget *openGLWidget;
    QPushButton *draw;
    QPushButton *load;
    QComboBox *list;
    QPlainTextEdit *plainTextEdit;
    QTextEdit *textEdit;
    QPushButton *reset;
    QLineEdit *lineEdit;
    QComboBox *elemC;
    QPushButton *pushButton;
    QLineEdit *lineEdit_2;
    QRadioButton *igual;
    QRadioButton *terminales;
    QTextEdit *texto_neurona;
    QMenuBar *menubar;
    QMenu *menuopen;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(986, 650);
        actionswc_file = new QAction(MainWindow);
        actionswc_file->setObjectName(QString::fromUtf8("actionswc_file"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        openGLWidget = new myopenglwidget(centralwidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setGeometry(QRect(210, 110, 441, 441));
        draw = new QPushButton(centralwidget);
        draw->setObjectName(QString::fromUtf8("draw"));
        draw->setGeometry(QRect(530, 70, 89, 25));
        load = new QPushButton(centralwidget);
        load->setObjectName(QString::fromUtf8("load"));
        load->setGeometry(QRect(530, 20, 89, 25));
        list = new QComboBox(centralwidget);
        list->setObjectName(QString::fromUtf8("list"));
        list->setGeometry(QRect(60, 20, 86, 25));
        plainTextEdit = new QPlainTextEdit(centralwidget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(260, 20, 211, 31));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(260, 60, 211, 31));
        reset = new QPushButton(centralwidget);
        reset->setObjectName(QString::fromUtf8("reset"));
        reset->setGeometry(QRect(380, 560, 89, 25));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(700, 50, 221, 25));
        elemC = new QComboBox(centralwidget);
        elemC->setObjectName(QString::fromUtf8("elemC"));
        elemC->setGeometry(QRect(700, 80, 86, 25));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(810, 80, 89, 25));
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(700, 190, 211, 25));
        igual = new QRadioButton(centralwidget);
        igual->setObjectName(QString::fromUtf8("igual"));
        igual->setGeometry(QRect(700, 230, 112, 23));
        terminales = new QRadioButton(centralwidget);
        terminales->setObjectName(QString::fromUtf8("terminales"));
        terminales->setGeometry(QRect(780, 230, 112, 23));
        texto_neurona = new QTextEdit(centralwidget);
        texto_neurona->setObjectName(QString::fromUtf8("texto_neurona"));
        texto_neurona->setGeometry(QRect(690, 260, 251, 311));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 986, 22));
        menuopen = new QMenu(menubar);
        menuopen->setObjectName(QString::fromUtf8("menuopen"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuopen->menuAction());
        menuopen->addAction(actionswc_file);

        retranslateUi(MainWindow);
        QObject::connect(actionswc_file, SIGNAL(triggered()), MainWindow, SLOT(openSWCFileThroughDialog()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionswc_file->setText(QApplication::translate("MainWindow", "swc  file", nullptr));
        draw->setText(QApplication::translate("MainWindow", "Draw", nullptr));
        load->setText(QApplication::translate("MainWindow", "Load", nullptr));
        plainTextEdit->setPlainText(QApplication::translate("MainWindow", "Cargar objeto", nullptr));
        textEdit->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Pintar objetos cargados</p></body></html>", nullptr));
        reset->setText(QApplication::translate("MainWindow", "Reset", nullptr));
        lineEdit->setText(QApplication::translate("MainWindow", "Elementos cargados", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "PushButton", nullptr));
        lineEdit_2->setText(QApplication::translate("MainWindow", "Separaci\303\263n de las dendritas", nullptr));
        igual->setText(QApplication::translate("MainWindow", "Igual", nullptr));
        terminales->setText(QApplication::translate("MainWindow", "Terminales", nullptr));
        menuopen->setTitle(QApplication::translate("MainWindow", "open", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
