#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include <GL/glut.h>
#include <QDebug>
#include <fstream>

using namespace std;

class GLWidget : public QGLWidget
{
public:
    explicit GLWidget(QWidget *parent = 0);
    void initializeGL();
    void paintGL();
    //void mouseMove(int x,int y);
    void resizeGL(int w, int h);

private:
    QTimer timer;
    void leerPuntos();
    float puntos[180000][3];
    int n;
    void dibujaPuntos();
};

#endif // GLWIDGET_H
