#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    hilo = std::thread(&MainWindow::camara,this);
    //Captura las señales emitidas por el Mouse al hacer click
    connect(ui->LabelCamara, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_Current_Pressed()));

    contador = 0;
    limites[0] = limites[1] = limites[2] = limites[3] = 0;

    ui->coor->setText("Limite Izquierdo");

    ancho = ui->LabelCamara->geometry().width();
    alto = ui->LabelCamara->geometry().height();

    capturar = false;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::camara()
{
    VideoCapture cap;
    cap.open(0);
    int col = 640; //Numero de pixeles de los frames capturados de la camara(ANCHO)
    int row = 480; //Numero de pixeles de los frames capturados de la camara(ALTO)

    clock_t ini;
    int tiempo;

        for(;;)
            {
                ini = clock();
                Mat image;
                cap >> image;

                dibujarLimites(image, row, col);
                if(capturar) fotos.push_back(image);//Comienza a capturar frames de la camara

                //qDebug()<<"CAPTURANDO FOTOS "<<fotos.size();

                Mat dest;
                cvtColor(image, dest,CV_BGR2RGB);
                QImage image1= QImage((uchar*) dest.data, dest.cols, dest.rows, dest.step, QImage::Format_RGB888);
                //Muestra la imagen capturada de la camara en labelCamara
                ui->LabelCamara->setPixmap(QPixmap::fromImage(image1));

                tiempo = 200 - ((clock()- ini)/1000);//Halla el tiempo restante para llegar a 200ms
                if(tiempo > 0) QThread::msleep(tiempo);//Duerme el tiempo que falta
            }
}

void MainWindow::on_BotonPlay_clicked()
{
    ui->BotonPlay->setEnabled(false);//Inhabilita boton Play
    capturar = true;
    ui->BotonStop->setEnabled(true);//Habilita boton Stop
}

void MainWindow::on_BotonStop_clicked()
{
    ui->BotonStop->setEnabled(false);//Inhabilita boton Stop
    capturar = false;
    guardarImagenes();//Guarda lo frames del vector fotos
    ofstream es("imagenes/data.txt");
    /*
     Guarda el numero frames capturadas de la camara
     y sus limites respectivos  en la carpeta imagenes con el nombre data.txt
     limites[0] -> Limite izquierdo
     limites[1] -> Limite derecho
     limites[2] -> Limite superior
     limites[3] -> Limite inferior
    */
    es << fotos.size() << " " << limites[0] << " " << limites[1] << " "<< limites[2] << " "<<limites[3];
    es.close();
    fotos.clear();
    ui->BotonPlay->setEnabled(true);//Habilita boton de tomar fotos
}

void MainWindow::on_BotonEjecutar_clicked()
{
    FormOpenGL *fogl = new FormOpenGL;
    fogl->show();//Abre la ventana en el cua se visualizara el objeto en 3D
}

void MainWindow::Mouse_Current_Pressed()
{
    if(contador % 4 == 0){//Se elige el limite izquierdo
        limites[0] = ui->LabelCamara->x * 640 / ancho;
        ui->coor->setText("Limite Derecho");
        qDebug() << limites[0];
    }
    else if(contador % 4 == 1){//Se elige el limite derecho
        limites[1] = ui->LabelCamara->x * 640 / ancho;
        ui->coor->setText("Limite Superior");
        qDebug() << limites[1];
    }
    else if(contador % 4 == 2){//Se elige el limite superior
        limites[2] = ui->LabelCamara->y * 480 / alto;
        ui->coor->setText("Limite Inferior");
        qDebug() << limites[2];
    }
    else{//Se elige el limite inferior
        limites[3] = ui->LabelCamara->y * 480 / alto;
        ui->coor->setText("Limite Izquierdo");
        qDebug() << limites[3];
    }
    contador++;
    contador %= 4;// si contador es: 0->0, 1->1, 2->2, 3->3, 4->0
}

void MainWindow::dibujarLimites(Mat &img,int row, int col)
{
    for(int i = 0; i < row; ++i ) //Lineas Verticales
    {
        //BGR(0, 255, 0)
        img.at<Vec3b>(i, limites[0]).val[0] = 255;
        img.at<Vec3b>(i, limites[0]).val[1] = 0;
        img.at<Vec3b>(i, limites[0]).val[2] = 0;

        img.at<Vec3b>(i, limites[1]).val[0] = 255;
        img.at<Vec3b>(i, limites[1]).val[1] = 0;
        img.at<Vec3b>(i, limites[1]).val[2] = 0;
    }

    for(int i = 0; i < col; ++i )//Lineas Horizontales
    {

        //BGR(0, 255, 0)
        img.at<Vec3b>(limites[2], i).val[0] = 255;
        img.at<Vec3b>(limites[2], i).val[1] = 0;
        img.at<Vec3b>(limites[2], i).val[2] = 0;

        img.at<Vec3b>(limites[3], i).val[0] = 255;
        img.at<Vec3b>(limites[3], i).val[1] = 0;
        img.at<Vec3b>(limites[3], i).val[2] = 0;
    }

}

//Guarda los frames almacenados en el vector fotos
void MainWindow::guardarImagenes()
{
    int n = fotos.size();
    for(size_t i = 0;i < n; ++i)
    {
       Mat dest;
       cvtColor(fotos[i], dest,CV_BGR2RGB);
       //Convierte del formato BGR a RGB
       QImage image1= QImage((uchar*) dest.data, dest.cols, dest.rows, dest.step, QImage::Format_RGB888);
       QString str = "imagenes/imagen"+QString::number(i)+".jpg";

       qDebug()<<"GUARDANDO IMAGEN";

       image1.save(str,"JPEG");//Los frames de guardan en la carpeta imagenes
    }

    QMessageBox m;
    m.setText("Se guardaron lo Frames!");
    m.exec();
}
