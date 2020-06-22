#include "canvas.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CCanvas Canvas;
    Canvas.resize(500, 500);
    Canvas.show();

    return a.exec();
}
