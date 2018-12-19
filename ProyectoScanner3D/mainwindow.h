#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <fstream>
#include <thread>
#include <QThread>
#include <vector>
#include <QDebug>
#include <opencv2/opencv.hpp>
#include "formopengl.h"


using namespace cv;
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::thread hilo;
    void camara();
    vector<Mat> fotos;

    int limites[4];//almacena los limites respectivos
    int contador;//Ubica que limite hay que definir
    int ancho;//Ancho del label que muestra las imagenes  de la camara
    int alto;//Alto del label que muestra las imagenes obtenidas de la camara
    void dibujarLimites(Mat &img, int row, int col);

    bool capturar;//Estado de la captura frames de la camara
    void guardarImagenes();

private slots:
    void on_BotonPlay_clicked();//Comienza la captura de frames de la camara
    void on_BotonStop_clicked();//Finliza la captura de frames de la camara
    void on_BotonEjecutar_clicked();//Reconstruye el objeto en 3D

    void Mouse_Current_Pressed();//Captura las posiciones de mouse en el labelCamara
};

#endif // MAINWINDOW_H
