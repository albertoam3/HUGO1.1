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
    openGLDialog(QWidget* parent = nullptr) : QOpenGLWidget(parent) {}
    void paintGL() override;
    void resizeGL(int w,int h) override;
    void initializeGL() override;
};

#endif //SOURCE_OPENGLDIALOG_H
