#ifndef FORMOPENGL_H
#define FORMOPENGL_H

#include <QWidget>
#include <string>
#include <QThread>
#include <string>
#include <fstream>

using namespace std;

namespace Ui {
class FormOpenGL;
}

class FormOpenGL : public QWidget
{
    Q_OBJECT

public:
    explicit FormOpenGL(QWidget *parent = 0);
    ~FormOpenGL();

private:
    Ui::FormOpenGL *ui;
    void getNubePuntos();
    int angEntreImagenes;
};

#endif // FORMOPENGL_H
