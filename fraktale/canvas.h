#ifndef CANVAS_H
#define CANVAS_H

#include <QMainWindow>
#include <QPainter>

class CCanvas : public QMainWindow {
public:
    CCanvas(QWidget *pParent = nullptr);
    int getColorValue(double ptX, double ptY);

protected:
    void paintEvent(QPaintEvent *pEvent) override;
    void paintMandelbrot(QPainter *painter);
    void paintSierpinski(QPainter *painter);

private:
    int m_nBrightness = 25;
    int m_nSensitivity = 75;
};

#endif // CANVAS_H
