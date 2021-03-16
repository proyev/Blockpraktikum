#include "echo.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EchoApp w;
    w.show();
    return a.exec();
}
