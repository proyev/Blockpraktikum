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

    QWidget::connect(&w, &battleships::createShip,
                     logic, &Logic::createShip);
    QWidget::connect(&w, &battleships::positionPlayer,
                     logic, &Logic::getStartPosition);

    QWidget::connect(&w, &battleships::positionRival,
                     logic, &Logic::getEndPosition);

//    QWidget::connect(&logic,

    QWidget::connect(logic, &Logic::draw,
                     &w, &battleships::drawShip);


    return a.exec();
}
