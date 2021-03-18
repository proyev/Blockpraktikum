#include "battleships.h"
#include "ui_battleships.h"
#include <QPalette>
#include <algorithm>

battleships::battleships(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::battleships)
{
    ui->setupUi(this);

    //create two fields of buttons
    for (int i=0; i<10; i++){
        for (int j=0; j<10; j++){
            _fieldPlayer[i][j] = new QPushButton(this);
            _fieldRival[i][j] = new QPushButton(this);
            _fieldPlayer[i][j]->setMinimumSize(25, 25);
            _fieldPlayer[i][j]->setMaximumSize(25, 25);
            _fieldRival[i][j]->setMinimumSize(25, 25);
            _fieldRival[i][j]->setMaximumSize(25, 25);
            _fieldPlayer[i][j]->move(35 + i*25, 35 + j*25);
            _fieldRival[i][j]->move(465 + i*25, 35 + j*25);
            _fieldPlayer[i][j]->show();
            _fieldRival[i][j]->show();
            connect(_fieldPlayer[i][j], &QPushButton::clicked,
                    this, [=](){
                            emit positionPlayer(i, j);
                           // ui->posX->setText(QString::number(i));
                           // ui->poxY->setText(QString::number(j));
                        });//when clicked - will send the coordinates to the logical part - required only for ship placement
            /*connect(_fieldRival[i][j], &QPushButton::clicked,
                    this, [=](){
                            emit positionRival(i, j);
                        });*///when clicked - will send the coordinates to the logical part - required only after the game start
            connect(_fieldRival[i][j], &QPushButton::clicked,
                    this, [=](){
                            emit positionRival(i, j);
            });//when clicked on the rival field, will get the position of the button clicked
        }
    }

//    connect(this, &battleships::positionPlayer,
//            [=](int i, int j){
//        ui->posX->setText(QString::number(i));
//        ui->poxY->setText(QString::number(j));
//    });
    connect(this, &battleships::positionPlayer,
            this, &battleships::setPositionPlayer);

    connect(ui->createDestroyerButton, SIGNAL(clicked()),
            this, SLOT(testDrawer()));

    connect(ui->createBattleshipButton, &QPushButton::clicked,
            this, &battleships::createBattleship);
    connect(ui->createCruiserButton, &QPushButton::clicked,
            this, &battleships::createCruiser);
    connect(ui->createDestroyerButton, &QPushButton::clicked,
            this, &battleships::createDestroyer);
    connect(ui->createSubmarineButton, &QPushButton::clicked,
            this, &battleships::createSubmarine);
}

void battleships::testDrawer(){
    int length = 3;
    int i = 3, j = 4;
    for (int draw = 0; draw<length; draw++){
        battleships::_fieldPlayer[i][j + draw]->setStyleSheet("* { background-color: rgb(0, 125, 0)}");
        battleships::_fieldPlayer[i][j + draw]->isChecked();
        battleships::_fieldPlayer[i][j + draw]->disconnect();
    }
}


void battleships::createBattleship(){
    int length = 5;
    ui->createBattleshipButton->hide();
    ui->createCruiserButton->hide();
    ui->createDestroyerButton->hide();
    ui->createSubmarineButton->hide();
    ui->cruiserCounter->hide();
    ui->destroyerCounter->hide();
    ui->submarineCounter->hide();
    emit createShip(length);
    //here should be connection to logic via emits of the new logical signals

}
void battleships::createCruiser(){
    int length = 4;
    ui->createBattleshipButton->hide();
    ui->createCruiserButton->hide();
    ui->createDestroyerButton->hide();
    ui->createSubmarineButton->hide();
    ui->cruiserCounter->hide();
    ui->destroyerCounter->hide();
    ui->submarineCounter->hide();
    emit createShip(length);
    //connection to logic via emit
}
void battleships::createDestroyer(){
    int length = 3;
    ui->createBattleshipButton->hide();
    ui->createCruiserButton->hide();
    ui->createDestroyerButton->hide();
    ui->createSubmarineButton->hide();
    ui->cruiserCounter->hide();
    ui->destroyerCounter->hide();
    ui->submarineCounter->hide();
    emit createShip(length);
    //connection to logic
}
void battleships::createSubmarine(){
    int length = 2;
    ui->createBattleshipButton->hide();
    ui->createCruiserButton->hide();
    ui->createDestroyerButton->hide();
    ui->createSubmarineButton->hide();
    ui->cruiserCounter->hide();
    ui->destroyerCounter->hide();
    ui->submarineCounter->hide();
    emit createShip(length);
    //connection to logic
}

void battleships::settingGameInterpreter(int battleshipCounter,
                                         int cruiserCounter,
                                         int destroyerCounter,
                                         int submarineCounter){
    if (battleshipCounter == 0 && cruiserCounter == 0 \
        && destroyerCounter == 0 && submarineCounter == 0){
        ui->startButton->show();
    }else if (battleshipCounter == 0){
        ui->createBattleshipButton->hide();
    }else if(cruiserCounter == 0){
        ui->createCruiserButton->hide();
        ui->cruiserCounter->hide();
    }else if(destroyerCounter == 0){
        ui->createDestroyerButton->hide();
        ui->destroyerCounter->hide();
    }else if(submarineCounter == 0){
        ui->createSubmarineButton->hide();
        ui->submarineCounter->hide();
    }else{
        ui->cruiserCounter->setText("x" + QString::number(cruiserCounter));
        ui->destroyerCounter->setText("x" + QString::number(destroyerCounter));
        ui->submarineCounter->setText("x" + QString::number(submarineCounter));
    }
}

//this slot will draw the ship itself, by making changing the color of buttons
//and making them 'pressed'
void battleships::drawShip(int startX, int startY,
                           int endX, int endY,
                           int length){

    if (startX == endX){
        //vertical orientation
        for (int i=0; i<length;i++){
            battleships::_fieldPlayer[startX][std::min(startY, endY) + i]->setStyleSheet("* { background-color: rgb(0, 125, 0)}");
            battleships::_fieldPlayer[startX][std::min(startY, endY) + i]->isChecked();
            battleships::_fieldPlayer[startX][std::min(startY, endY) + i]->disconnect();
        }
    }else{
        //horizontal orientation
        for (int i=0; i<length; i++){
            battleships::_fieldPlayer[std::min(startX, endX) + i][startY]->setStyleSheet("* { background-color: rgb(0, 125, 0)}");
            battleships::_fieldPlayer[std::min(startX, endX) + i][startY]->isChecked();
            battleships::_fieldPlayer[std::min(startX, endX) + i][startY]->disconnect();
        }
        }
    }


//these two slots take the interpretation of the made move form the logic and will paint the field accordingly
void battleships::moveRivalInterpreter(int posX, int posY, char status){
    switch (status) {
        case('H'):
            battleships::_fieldPlayer[posX][posY]->setStyleSheet("* { background-color: rgb(125, 0, 0)}");
            break;
        case('M'):
            battleships::_fieldPlayer[posX][posY]->setStyleSheet("* { background-color: rgb(0, 0, 255)}");
    }
}
void battleships::movePlayerInterpreter(int posX, int posY, char status){
    switch (status) {
        case('H'):
            battleships::_fieldRival[posX][posY]->setStyleSheet("* { background-color: rgb(125, 0, 0)}");
            break;
        case('M'):
            battleships::_fieldRival[posX][posY]->setStyleSheet("* { background-color: rgb(0, 0, 255)}");
    }
}

void battleships::setPositionPlayer(int i, int j){

    ui->posX->setText("Position x: " + QString::number(i));
    ui->poxY->setText("Position y: " + QString::number(j));
//    emit testSignal(5);
}

battleships::~battleships()
{
    delete ui;
}

