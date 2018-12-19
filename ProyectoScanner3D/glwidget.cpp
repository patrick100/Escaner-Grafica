#include "glwidget.h"
#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent):QGLWidget(parent)
{
    n = 0;
    leerPuntos();
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(16);
}

void GLWidget::initializeGL()
{
    glClearColor(0, 0, 0, 1);

}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glRotatef(0.5, 0, 1, 0);

    //AXIS X -RED
    glColor3f(1., 0., 0.);
    glBegin(GL_LINES);
    glVertex3f(-0.7, 0, 0.);
    glVertex3f(0.7, 0, 0.);
    glEnd();
    //AXIS Y -GREEN
    glColor3f(0., 1., 0.);
    glBegin(GL_LINES);
    glVertex3f(0, -0.7, 0.);
    glVertex3f(0, 0.7, 0.);
    glEnd();
    //AXIS Z -BLUE
    glColor3f(0., 0., 1.);
    glBegin(GL_LINES);
    glVertex3f(0, 0, -0.7);
    glVertex3f(0, 0, 0.7);
    glEnd();

    dibujaPuntos();
}

/*
void GLWidget::mouseMove(int x, int y)
{
    if (mouseHold.buttonLeft)
    {
        glRotatef(1.0, 1, 1, 0);
    }
    if (mouseHold.buttonRight)
    {
        glRotatef(1.0, 2, 1, 0);
    }
    if (mouseHold.buttonMiddle)
    {
        glRotatef(1.0, 1, 0, 0);
    }
    mouseHold.x = x;
    mouseHold.y = y;
}*/


void GLWidget::resizeGL(int w, int h)
{

        //Set the viewport
        glViewport( 0.f, 0.f, w, h );
        qDebug()<< w << " " << h;
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();

        glEnable(GL_DEPTH_TEST);

        //Initialize Modelview Matrix
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();

        GLfloat luz_ambiental[] = { 0.2, 0.2, 0.2, 1.0 };
        glLightModelfv (GL_LIGHT_MODEL_AMBIENT, luz_ambiental);

}

void GLWidget::leerPuntos()
{
    ifstream leer("Puntos/puntos.txt");

    float angulo, x, y, z;
    n = 0;
    //Se divide entre 200 para escalarlo y entre en la ventana que tiene como rango -1 a 1
    while(!leer.eof()){
        leer >> angulo;
        leer >> x >> y >> z;
        puntos[n][0] = x / 200;
        puntos[n][1] = (y/200)-0.8;
        puntos[n][2] = z / 200;
        ++n;
    }

    leer.close();

    qDebug() << "lee puntos";
}
void GLWidget::dibujaPuntos()
{
    glColor3f(1., 0., 1.);
    glBegin(GL_POINTS);
    for(int i = 0; i < n; ++i)
        glVertex3f(puntos[i][0], puntos[i][1], puntos[i][2]);
    glEnd();
}
