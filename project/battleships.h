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
            void setPositionPlayer(int i, int j);
//            void setPositionRival(int i, int j);


            void createBattleship();
            void createCruiser();
            void createDestroyer();
            void createSubmarine();
            void settingGameInterpreter(int battleshipCounter,
                                        int cruiserCounter,
                                        int destroyerCounter,
                                        int submarineCounter);

            void movePlayerInterpreter(int posX, int posY, char status);
            void moveRivalInterpreter(int posX, int posY, char status);

            void testDrawer();//for tests only

        signals:
            void positionPlayer(int i, int j);
            void positionRival(int i, int j);

            void shipDrawer(int i, int j, int lenght);

            void createShip(int length); // sends the info about the type of ship to be created

            void shipOrientation(char orientation);


            void testSignal(int a);
//            void positionRival(int i, int j);
public slots:
            void drawShip(int startX, int startY,
                          char orientation,
                          int length);//slot to draw a ship later on - try and combine it with logic
            void destroyedShips(int length);

            void horizontalOrientation();
            void verticalOrientation();

            void connectSlot();
            void disconnectSlot();
            void serverSlot();
            void clientSlot();
            void saveName();

};
#endif // BATTLESHIPS_H
