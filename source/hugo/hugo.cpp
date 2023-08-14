#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("imagenes/Diapositiva9.PNG"));

    MainWindow w;
    w.show();
    return a.exec();
}
