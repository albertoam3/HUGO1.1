//
// Created by alberto on 11/09/23.
//

#ifndef SOURCE_OPENGLDIALOG_H
#define SOURCE_OPENGLDIALOG_H


#include <QDialog>
#include <QOpenGLWidget>
#include <QVBoxLayout>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QPainter>


class openGLDialog : public QOpenGLWidget,public QOpenGLFunctions {


Q_OBJECT

public:
    openGLDialog(QWidget* parent = nullptr) : QOpenGLWidget(parent) {
    for (int i=0;i<9;i++){
        nodos_por_punto[i]=0;
    }
}
    void paintGL() override;
    void resizeGL(int w,int h) override;
    void initializeGL() override;
    void anadir_nodos_por_punto(int aux[9]);
private:
    int nodos_por_punto[9];
};
#endif //SOURCE_OPENGLDIALOG_H
