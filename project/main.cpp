#include "battleships.h"
#include "logic.h"
#include <QApplication>
#include <QWidget>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    battleships w;
    w.show();

    Logic *logic = new Logic;
    QWidget::connect(&w, &battleships::positionPlayer,
                     logic, &Logic::testSlot);


    return a.exec();
}
