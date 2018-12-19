#include "formopengl.h"
#include "ui_formopengl.h"
#include <QDebug>
#include "CImg.h"
using namespace cimg_library;

CImg<unsigned char> binarizarImg(string nameFile,int x_inf,int x_sup,int y_inf,int y_sup){
    CImg<unsigned char> img(nameFile.c_str());
    CImg<unsigned char> imgTemp(x_sup-x_inf+1,y_sup-y_inf+1);

    //!BINARIO
    for(int i=x_inf;i<=x_sup;i++){
        for(int j=y_inf;j<=y_sup;j++){

            int valor = (img(i,j,0)+img(i,j,1)+img(i,j,2) )/3;
            if(valor > 170) //Umbral para binarizar, mayores a ello se pinta de negro, caso contrario blanco
               imgTemp(i-x_inf,j-y_inf) = 0;
            else
               imgTemp(i-x_inf,j-y_inf) = 255;


            /*
            int valor = img(i,j,0);
            if(valor < 142) //Umbral para binarizar, mayores a ello se pinta de negro, caso contrario blanco
               imgTemp(i-x_inf,j-y_inf) = 0;
            else
               imgTemp(i-x_inf,j-y_inf) = 255;

            */
        }
    }
    return imgTemp;
}

FormOpenGL::FormOpenGL(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormOpenGL)
{
    angEntreImagenes = 1;
    getNubePuntos();
    ui->setupUi(this);
}

FormOpenGL::~FormOpenGL()
{
    delete ui;
}


void FormOpenGL::getNubePuntos()
{
    int s[4], n;
    ifstream lee("imagenes/data.txt");
    lee >> n >> s[0] >> s[1] >> s[2] >> s[3];
    lee.close();

    string nombre;
    vector< CImg<unsigned char> > imgBins;
    //Binariza los frames capturados y que se encuentran en la carpeta imagenes
    for(int i = 0; i < n; ++i )
    {
        nombre = "imagenes/imagen"+to_string(i)+".jpg";
        imgBins.push_back(binarizarImg(nombre, s[0], s[1], s[2], s[3]));
    }


    float angCamLaser = 70; //Angulo entre la camara y el puntero laser
    float PI = 2 * asin(1); //180 grados en radianes
    int alto = imgBins[0].height();
    int ancho = imgBins[0].width();

    ofstream es("Puntos/puntos.txt");

    //Imagenes por cada angulo con un intervalo asignado por angEntreImagenes
    for(int ang = 0; ang < 360;  ang += angEntreImagenes)
    {
       //posImag es la imagen que se tomara para el presente angulo "ang"
       int posImg = ang * n / 360, cont = 0, prom = 0;
       for(int y = 0; y < alto;  ++y)
        {
           prom = 0;cont = 0;
            for(int x = 0; x < ancho;  ++x)
            {
                if(imgBins[posImg](x,y) == 0){
                    prom += x;
                    ++cont;
                }
            }
            if(cont > 0){
                prom /= cont;//promedio de las x para obtener una sola
                //Distancia entre el centro y el borde detectado por la luz del laser
                float radio = prom / sin(angCamLaser * PI / 180);

                //Almacena la nube de puntos en el achivo puntos.txt dentro de la carpeta Puntos
                es << ang << " ";
                es << (int)(radio * cos(ang * PI / 180)) << " ";
                es << y << " ";
                es << (int)(radio * sin(ang * PI / 180)) << "\n";
            }
        }

       //Se almacenan las imagenes binarias para luego visualizarlo por el explorador
       string namefile = "imagenesBinarias/imagen" + to_string(ang) + ".jpg";
       imgBins[ang].save(namefile.c_str());
    }

    es.close();

}
