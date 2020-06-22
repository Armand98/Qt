#include "canvas.h"
#include <complex>
#include <QLabel>
#include <QSlider>
#include <QToolBar>
#include <cmath>
#include <cstdlib>

CCanvas::CCanvas(QWidget *pParent) : QMainWindow(pParent) {

}

int CCanvas::getColorValue(double ptX, double ptY) {

    std::complex<double> complexPoint(ptX/width() - 1.5, ptY/height() - 0.5);
    std::complex<double> complexZ(0, 0);

    int nBrightness = m_nBrightness;

    while((abs(complexZ) < 2) && (nBrightness <= m_nSensitivity)) {
        complexZ = pow(complexZ, 2) + complexPoint;
        nBrightness++;
    }

    if(nBrightness < m_nSensitivity)
        return static_cast<int>((255 * nBrightness) / m_nSensitivity);
    else
        return 0;
}

void CCanvas::paintEvent(QPaintEvent *) {

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    /*
     * Wywołanie funkcji do rysowania wybranego fraktala
     * */
    //paintSierpinski(&painter);
    paintMandelbrot(&painter);
}

void CCanvas::paintMandelbrot(QPainter *painter) {
    QPen pen;
    int nColorValue = 0;

    for(int ptX = 0; ptX < width(); ++ptX) {
        for(int ptY = 0; ptY < height(); ++ptY) {
            nColorValue = getColorValue(static_cast<double>(ptY), static_cast<double>(ptX));
            pen.setColor(QColor(nColorValue, 0, 0));
            painter->setPen(pen);
            painter->drawPoint(ptX, ptY);
        }
    }
}

void CCanvas::paintSierpinski(QPainter *painter) {

     float A[2];
     float B[2];
     float C[2];
     float P[2];
     A[0]=200;
     A[1]=50;
     B[0]=50;
     B[1]=250;
     C[0]=350;
     C[1]=250;
     P[0]=0;
     P[1]=0;

     QColor colors[3];
     colors[0] = Qt::blue;
     colors[1] = Qt::red;
     colors[2] = Qt::green;

     for (int i=0; i<10000000; i++) {
          int losuj=floor(rand()%3);
          painter->setPen(colors[losuj]);
          switch(losuj) {
              case 0:
                  P[0]=(P[0]+A[0])/2;
                  P[1]=(P[1]+A[1])/2;
              break;
              case 1:
                  P[0]=(P[0]+B[0])/2;
                  P[1]=(P[1]+B[1])/2;
              break;
              case 2:
                  P[0]=(P[0]+C[0])/2;
                  P[1]=(P[1]+C[1])/2;
              break;
          }
          painter->drawPoint(P[0],P[1]);
      }
}



