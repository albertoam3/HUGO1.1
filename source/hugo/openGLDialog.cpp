//
// Created by alberto on 11/09/23.
//

#include "openGLDialog.h"

void openGLDialog::paintGL() {
    QPainter painter(this);
    painter.setPen(Qt::white); // Color del texto (blanco)
    QFont font;
    font.setPixelSize(24); // Tamaño de fuente
    painter.setFont(font);
    painter.drawLine(30, 450, 30,30 );
    painter.drawLine(20, 430, 430, 430);

    painter.drawText(50, 450, "1");
    painter.drawText(85, 450, "2");
    painter.drawText(120, 450, "3");
    painter.drawText(155, 450, "4");
    painter.drawText(190, 450, "5");
    painter.drawText(225, 450, "6");
    painter.drawText(260, 450, "7");
    painter.drawText(295, 450, "8");
    painter.drawText(330, 450, "9");
    painter.drawText(365, 450, "10");
    painter.drawText(400, 450, "11");
}


void openGLDialog::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
}

void openGLDialog::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_MODELVIEW);



    // Habilitar antialiasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_MULTISAMPLE);

    QSurfaceFormat format = this->format();
}
