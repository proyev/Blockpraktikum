#include "battleships.h"
//#include "logic.hpp"
//#include "nw.h"
#include <QApplication>
#include <QWidget>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    battleships w;
    w.show();
    //*Player *player = new player;
   // network Nw *nw = new Nw;

    //======================================================
    /*Logic *logic = new Logic;

    QWidget::connect(&w, &battleships::shipOrientation,
                     logic, &Logic::slotOrientation);
    QWidget::connect(&w, &battleships::createShip,
                     logic, &Logic::createShip);
    QWidget::connect(&w, &battleships::positionPlayer,
                     logic, &Logic::getStartPosition);*///here the check-position should be called within logic
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

//    QWidget::connect(logic, &Logic::draw,
//                     &w, &battleships::gameSetup);

//    //connection to network
//    QWidget::connect(
    QWidget::connect(&w, & ,
                     player, &Player::SetOrientationSlot);
    QWidget::connect(player, &Player::UnblockPlayerFieldSig,
                     &battleships::unblockField);
    QWidget::connect(&w, &battleships::createShip,
                     player, &SetSelectedShipSlot);
    QWidget::connect(&w, &battleships::positionPlayer,
                     player, &Player::SetPlacingBeginCoordinates);
    QWidget::connect(player, &Player::ShipPlaceValidationSig,
                     //the reciever)
    QWidget::connect(player, &Player::DrawShipSig,
                     &w, &battleships::gameSetup);
    QWidget::connect(player, &Player::BlockingSurfaceSig,
                     &w, // some slot to save information about the further unblocking);
    QWidget::connect(&w, //rivalmove,
                     player, &Player::SetTargetSlot);
    QWidget::connect(player, &Player::PlayerAttackResultSig,
                     &w, &battleships::moveRival);
    QWidget::connect(player, &Player::SunkShip,
                     &w, &battleships::destroyedShips);
    QWidget::connect(player, &Player::EnemyAttackResultGUISig,
                     &w, &battleships::moveRivalInterpreter);
    //move RivalInterpreter will emit signal to change turns


    return a.exec();
}
