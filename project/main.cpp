#include "battleships.h"
#include <QApplication>
#include "battleShipLogic.hpp"
#include "nw.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    battleships* w = new battleships;
    w->show();


    Player* player = new Player;
    Nw* nw = new Nw;

    // -----------Alle "connect()" die slots und signals von versch. Klassen verbinden. ---------------------------------


    //-----------------------------GUI -> NW -------------------------------------------------
    QObject::connect(w,&battleships::connectSignal,nw,&Nw::connectToServer);         //ok
    QObject::connect(w,&battleships::disconnectSignal,nw,&Nw::disconnectFromServer); //ok
    QObject::connect(w,&battleships::positionRival,nw,&Nw::shoot); //ok
    QObject::connect(w,&battleships::startGame,nw,&Nw::togglePlayerReady); //ok
    //QObject::connect(w,&battleships::respondToRequestSignal,nw,&Nw::respondToRequest);
    QObject::connect(w,&battleships::isClient,nw,&Nw::toggleIsClient);//ok
    //QObject::connect(w,&battleships::sendParamSignal,nw,&Nw::sendParam);
    //QObject::connect(w,&battleships::connectToPlayer,nw,&Nw::connectToPlayer);
    QObject::connect(w,&battleships::sendTextMessage,nw,&Nw::sendTextMessage);
//    QObject::connect(w,&battleships::sendPlayerName,nw,&Nw::sendPlayerName);


    //-----------------------------NW -> GUI -----------------------------------------
    QObject::connect(nw,&Nw::displayMessage,w,&battleships::messageRival); // later
    QObject::connect(nw,&Nw::connectionEstablished,w,&battleships::connectionStatus);// ok
/*    QObject::connect(nw,&Nw::recvEnemyName,w,&battleships::nameRival);*/ // later
    QObject::connect(nw,&Nw::gameStartsNow,w,&battleships::turn); //ok
    //QObject::connect(nw,&Nw::connectedToPlayer,w,&battleships::); //ok

    //-----------------------------NW -> player --------------------------------------
    QObject::connect(nw,&Nw::recvShotResponse,player,&Player::PlayerAttackResultSlot); //ok
    QObject::connect(nw,&Nw::shotIncoming,player,&Player::EnemyAttackSlot);
    //----------------------------player -> NW ----------------------------------------
   QObject::connect(player,&Player::EnemyAttackResultSig,nw,&Nw::shotResponse); //ok

    //-----GUI <-> player
   QObject::connect(w, &battleships::shipOrientation,
                    player, &Player::SetOrientationSlot);
   QObject::connect(w, &battleships::createShip,
                        player, &Player::SetSelectedShipSlot);
   QObject::connect(player, &Player::BlockingSurfaceSig,
                    w, &battleships::unblockPlayerField);
   QObject::connect(w, &battleships::positionPlayer,
                    player, &Player::SetPlacingBeginCoordinatesSlot);
   QObject::connect(player, &Player::ShipPlaceValidationSig,
                    w, &battleships::placementValidation);
   QObject::connect(player, &Player::DrawShipSig,
                    w, &battleships::gameSetup);

   // game phase
   QObject::connect(w, &battleships::positionRival,
                    player, &Player::SetTargetSlot);
   QObject::connect(player, &Player::PlayerAttackResultSig,
                    w, &battleships::movePlayerInterpreter);
   QObject::connect(player, &Player::SunkShip,
                    w, &battleships::destroyedShips);
   QObject::connect(player, &Player::EnemyAttackResultGUISig,
                    w, &battleships::moveRivalInterpreter);

    return a.exec();
}
