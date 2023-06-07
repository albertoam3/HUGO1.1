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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
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
    QPushButton *reset;
    QComboBox *elemC;
    QPushButton *pushButton;
    QTextEdit *texto_neurona;
    QPushButton *boton3D;
    QPushButton *boton2D;
    QGroupBox *groupBox;
    QRadioButton *igual_ang;
    QRadioButton *terminales_ang;
    QGroupBox *groupBox_2;
    QRadioButton *igual_ramas;
    QRadioButton *dif_rama;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QCheckBox *setArbol;
    QGroupBox *groupBox_3;
    QRadioButton *igual_grosor;
    QRadioButton *dif_grosor;
    QComboBox *grosorComboBox;
    QMenuBar *menubar;
    QMenu *menuopen;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1110, 706);
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
        reset = new QPushButton(centralwidget);
        reset->setObjectName(QString::fromUtf8("reset"));
        reset->setGeometry(QRect(380, 560, 89, 25));
        elemC = new QComboBox(centralwidget);
        elemC->setObjectName(QString::fromUtf8("elemC"));
        elemC->setGeometry(QRect(690, 40, 86, 25));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(800, 40, 89, 25));
        texto_neurona = new QTextEdit(centralwidget);
        texto_neurona->setObjectName(QString::fromUtf8("texto_neurona"));
        texto_neurona->setGeometry(QRect(730, 350, 251, 311));
        boton3D = new QPushButton(centralwidget);
        boton3D->setObjectName(QString::fromUtf8("boton3D"));
        boton3D->setGeometry(QRect(40, 150, 89, 25));
        boton2D = new QPushButton(centralwidget);
        boton2D->setObjectName(QString::fromUtf8("boton2D"));
        boton2D->setGeometry(QRect(40, 190, 89, 25));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(680, 80, 191, 91));
        igual_ang = new QRadioButton(groupBox);
        igual_ang->setObjectName(QString::fromUtf8("igual_ang"));
        igual_ang->setGeometry(QRect(10, 30, 112, 23));
        terminales_ang = new QRadioButton(groupBox);
        terminales_ang->setObjectName(QString::fromUtf8("terminales_ang"));
        terminales_ang->setGeometry(QRect(10, 50, 112, 23));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(680, 180, 251, 91));
        igual_ramas = new QRadioButton(groupBox_2);
        igual_ramas->setObjectName(QString::fromUtf8("igual_ramas"));
        igual_ramas->setGeometry(QRect(10, 30, 112, 23));
        dif_rama = new QRadioButton(groupBox_2);
        dif_rama->setObjectName(QString::fromUtf8("dif_rama"));
        dif_rama->setGeometry(QRect(10, 50, 112, 23));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(260, 30, 181, 17));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(260, 70, 221, 20));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(690, 20, 221, 17));
        setArbol = new QCheckBox(centralwidget);
        setArbol->setObjectName(QString::fromUtf8("setArbol"));
        setArbol->setGeometry(QRect(680, 290, 92, 23));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(890, 90, 201, 80));
        igual_grosor = new QRadioButton(groupBox_3);
        igual_grosor->setObjectName(QString::fromUtf8("igual_grosor"));
        igual_grosor->setGeometry(QRect(10, 30, 112, 23));
        dif_grosor = new QRadioButton(groupBox_3);
        dif_grosor->setObjectName(QString::fromUtf8("dif_grosor"));
        dif_grosor->setGeometry(QRect(10, 50, 112, 23));
        grosorComboBox = new QComboBox(groupBox_3);
        grosorComboBox->setObjectName(QString::fromUtf8("grosorComboBox"));
        grosorComboBox->setGeometry(QRect(100, 30, 86, 25));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1110, 22));
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
        reset->setText(QApplication::translate("MainWindow", "Reset", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "PushButton", nullptr));
        boton3D->setText(QApplication::translate("MainWindow", "3D", nullptr));
        boton2D->setText(QApplication::translate("MainWindow", "2D", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "Separaci\303\263n de las dendritas", nullptr));
        igual_ang->setText(QApplication::translate("MainWindow", "Igual", nullptr));
        terminales_ang->setText(QApplication::translate("MainWindow", "Terminales", nullptr));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Tama\303\261o de las ramas", nullptr));
        igual_ramas->setText(QApplication::translate("MainWindow", "Igual", nullptr));
        dif_rama->setText(QApplication::translate("MainWindow", "Diferente", nullptr));
        label->setText(QApplication::translate("MainWindow", "CARGAR OBJETO", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "PINTAR OBJETOS CARGADOS", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "ELEMENTOS CARGADOS", nullptr));
        setArbol->setText(QApplication::translate("MainWindow", "\303\241rbol", nullptr));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Grosor de las ramas", nullptr));
        igual_grosor->setText(QApplication::translate("MainWindow", "Igual", nullptr));
        dif_grosor->setText(QApplication::translate("MainWindow", "Diferente", nullptr));
        menuopen->setTitle(QApplication::translate("MainWindow", "open", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
