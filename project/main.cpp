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

    QWidget::connect(&w, &battleships::shipOrientation,
                     logic, &Logic::slotOrientation);
    QWidget::connect(&w, &battleships::createShip,
                     logic, &Logic::createShip);
    QWidget::connect(&w, &battleships::positionPlayer,
                     logic, &Logic::getStartPosition);//here the check-position should be called within logic
    //if ok - emit drawShip to pass to gameSetup all the needed info - the ship will be drawn and the game will be updated
    //if not ok - emit status with some marker:
    // p - for problem with placement or similiar
    // a - awaiting another player
    // c - connection establilshed
    // t - your turn
    // o - your opponents turn
    // w - you win
    // l - game over - you lost

//    QWidget::connect(&w, &battleships::positionRival,
//                     logic, &Logic::getEndPosition);

//    QWidget::connect(&logic,

    QWidget::connect(logic, &Logic::draw,
                     &w, &battleships::gameSetup);


    return a.exec();
}
