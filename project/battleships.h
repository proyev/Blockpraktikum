#ifndef BATTLESHIPS_H
#define BATTLESHIPS_H

#include <QWidget>
#include <QObject>
#include <QPushButton>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class battleships; }
QT_END_NAMESPACE

class battleships : public QWidget
{
    Q_OBJECT

public:
    battleships(QWidget *parent = nullptr);
    ~battleships();

private:
    Ui::battleships *ui;
    QPushButton *_fieldPlayer[10][10];
    QPushButton *_fieldRival[10][10];

private slots:
            void horizontalOrientation();
            void verticalOrientation();
            void createBattleship();
            void createCruiser();
            void createDestroyer();
            void createSubmarine();

            void blockPlayerField();
            void blockRivalField();

            void updatePlayerHP();
            void updateRivalHP();

        signals:
            void positionPlayer(int i, int j);
            void positionRival(int i, int j);

            void createShip(int length); // sends the info about the type of ship to be created
            void shipOrientation(char orientation);
            void checkCoordinates(int startX, int startY);

            void blockField();
            void unblockField();
            void playerHP();
            void rivalHP();
            void playerTurn();
            void statusSignal(char satus);

            void connectSignal(QString ip, QString port);
            void startGame();
            void disconnectSignal();
            void isClient(bool info);
public slots:
            void gameSetup(int startX, int startY,
                          char orientation,
                          int length);//slot to draw a ship later on - try and combine it with logic
            void destroyedShips(int length);
            void placementValidation(bool valid);

            void turn(bool turn);
            void status(char status);

            void connectionSatus(bool connection);

            void unblockPlayerField(int startX, int startY,
                                    int endX, int endY);
            void unblockRivalField();
            void movePlayerInterpreter(int posX, int posY, char status);
            void moveRivalInterpreter(int posX, int posY, char status);

};
#endif // BATTLESHIPS_H
