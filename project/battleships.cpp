#include "battleships.h"
#include "ui_battleships.h"
#include <QPalette>
#include <QRadioButton>
#include <QSignalBlocker>
#include <algorithm>
#include <iostream>
#include <string>

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
            _fieldRival[i][j]->move(490 + i*25, 35 + j*25);
            _fieldPlayer[i][j]->setStyleSheet("* { background-color: rgb(255, 255, 255)}");
            _fieldRival[i][j]->setStyleSheet("* { background-color: rgb(255, 255, 255)}");
            _fieldPlayer[i][j]->show();
            _fieldRival[i][j]->show();
            _fieldPlayer[i][j]->setDisabled(true);
            _fieldRival[i][j]->setDisabled(true);
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
    this->_fieldRival[3][3]->setStyleSheet("* { background-color: rgb(0, 0, 255)}");
    this->_fieldRival[7][8]->setStyleSheet("* { background-color: rgb(125, 0, 0)}");
    ui->startButton->setDisabled(true);
    connect(ui->startButton, &QPushButton::clicked,
            this, &battleships::blockPlayerField); //blocks the field after the game started
    connect(ui->startButton, &QPushButton::clicked,
            this, &battleships::unblockRivalField); //unblocks the field to make a move
    connect(ui->startButton, &QPushButton::clicked,
            ui->verticalOptionButton, &QRadioButton::hide);
    connect(ui->startButton, &QPushButton::clicked,
            ui->horizontalOptionButton, &QRadioButton::hide);
    connect(ui->startButton, &QPushButton::clicked,
            ui->statusLabel, &QLabel::hide);
    connect(ui->startButton, &QPushButton::clicked,
            ui->startButton, &QPushButton::hide);

    ui->createBattleshipButton->setDisabled(true);
    ui->createCruiserButton->setDisabled(true);
    ui->createDestroyerButton->setDisabled(true);
    ui->createSubmarineButton->setDisabled(true);

    ui->disconnectButton->hide();
    ui->clientButton->hide();

    connect(ui->connectButton, &QPushButton::clicked,
            this, &battleships::connectSlot);
    connect(ui->serverButton, &QPushButton::clicked,
            this, &battleships::serverSlot);
    connect(ui->disconnectButton, &QPushButton::clicked,
            this, &battleships::disconnectSlot);
    connect(ui->clientButton, &QPushButton::clicked,
            this, &battleships::clientSlot);

    connect(ui->horizontalOptionButton, &QRadioButton::clicked,
            this, &battleships::horizontalOrientation);
    connect(ui->verticalOptionButton, &QRadioButton::clicked,
            this, &battleships::verticalOrientation);

    connect(this, &battleships::positionPlayer,
            this, &battleships::setPositionPlayer);

    connect(ui->createBattleshipButton, &QPushButton::clicked,
            this, &battleships::createBattleship);
    connect(ui->createCruiserButton, &QPushButton::clicked,
            this, &battleships::createCruiser);
    connect(ui->createDestroyerButton, &QPushButton::clicked,
            this, &battleships::createDestroyer);
    connect(ui->createSubmarineButton, &QPushButton::clicked,
            this, &battleships::createSubmarine);


    connect(ui->saveNameButton, &QPushButton::clicked,
            this, &battleships::saveName);//change to slot from logic

    connect(this, &battleships::blockField,
            this, &battleships::blockPlayerField);
    connect(this, &battleships::unblockField,
            this, &battleships::unblockPlayerField);
}

void battleships::createBattleship(){
    int length = 5;
    ui->statusLabel->setText("Choose the location");
    emit createShip(length);
    emit unblockPlayerField();
    //here should be connection to logic via emits of the new logical signals

}
void battleships::createCruiser(){
    int length = 4;
    ui->statusLabel->setText("Choose the location");
    emit createShip(length);
    emit unblockPlayerField();
    //connection to logic via emit
}
void battleships::createDestroyer(){
    int length = 3;
    ui->statusLabel->setText("Choose the location");
    emit createShip(length);
    emit unblockPlayerField();
    //connection to logic
}
void battleships::createSubmarine(){
    int length = 2;
    ui->statusLabel->setText("Choose the location");
    emit createShip(length);
    emit unblockPlayerField();
    //connection to logic
}

//this slot will draw the ship itself, by making changing the color of buttons
//and making them 'pressed'
//rename to game setting
void battleships::gameSetup(int startX, int startY,
                           char orientation,
                           int length){
    switch (orientation) {
        case('v'):  //vertical orientation
            for (int i=0; i<length; i++){
                    battleships::_fieldPlayer[startX][startY + i]->setStyleSheet("* { background-color: rgb(0, 125, 0)}");
                    battleships::_fieldPlayer[startX][startY + i]->setDisabled(true);
                    ui->verticalOptionButton->setAutoExclusive(false);
                    ui->horizontalOptionButton->setAutoExclusive(false);
                    ui->verticalOptionButton->setChecked(false);
                    ui->horizontalOptionButton->setChecked(false);
                    ui->verticalOptionButton->setAutoExclusive(true);
                    ui->horizontalOptionButton->setAutoExclusive(true);
                    ui->createBattleshipButton->setDisabled(true);
                    ui->createCruiserButton->setDisabled(true);
                    ui->createDestroyerButton->setDisabled(true);
                    ui->createSubmarineButton->setDisabled(true);
                    ui->statusLabel->setText("Choose the orientation of the ship");
                    emit blockField();
            }
            break;
         case ('h'): //horizontal orientation
            for (int i=0; i<length; i++){
                    battleships::_fieldPlayer[startX + i][startY]->setStyleSheet("* { background-color: rgb(0, 125, 0)}");
                    battleships::_fieldPlayer[startX + i][startY]->setDisabled(true);
                    ui->verticalOptionButton->setAutoExclusive(false);
                    ui->horizontalOptionButton->setAutoExclusive(false);
                    ui->verticalOptionButton->setChecked(false);
                    ui->horizontalOptionButton->setChecked(false);
                    ui->verticalOptionButton->setAutoExclusive(true);
                    ui->horizontalOptionButton->setAutoExclusive(true);
                    ui->createBattleshipButton->setDisabled(true);
                    ui->createCruiserButton->setDisabled(true);
                    ui->createDestroyerButton->setDisabled(true);
                    ui->createSubmarineButton->setDisabled(true);
                    ui->statusLabel->setText("Choose the orientation of the ship");
                    emit blockField();
            }
            break;
    }
    switch (length) {
        case(5):
            ui->createBattleshipButton->hide();
            break;
        case(4):
            {static int counter = 0;
            counter += 1;
            if (counter == 2){
                ui->createCruiserButton->hide();
                ui->cruiserCounter->hide();
            }else{
                ui->cruiserCounter->setText("x" + QString::number(2-counter));
            }
            break;
        }
        case(3):
            {static int counter = 0;
            counter += 1;
            if (counter == 3){
                ui->createDestroyerButton->hide();
                ui->destroyerCounter->hide();
            }else{
                ui->destroyerCounter->setText("x" + QString::number(3-counter));
            }
            break;
        }
        case(2):
            {static int counter = 0;
            counter += 1;
            if (counter == 4){
                ui->createSubmarineButton->hide();
                ui->submarineCounter->hide();
            }else{
                ui->submarineCounter->setText("x" + QString::number(4-counter));
            }
            break;
        }
    }
    if (ui->createBattleshipButton->isHidden() &&
        ui->createCruiserButton->isHidden() &&
        ui->createDestroyerButton->isHidden() &&
        ui->createSubmarineButton->isHidden()){
        ui->startButton->setDisabled(false);
        ui->verticalOptionButton->hide();
        ui->horizontalOptionButton->hide();
        ui->statusLabel->setText("Press 'Start' to begin");
        emit blockField();
    }
}

//blocks the field players field, to avoid click-problem
void battleships::blockPlayerField(){
    for (int i=0; i<10; i++){
        for (int j=0; j<10; j++){
            this->_fieldPlayer[i][j]->setDisabled(true);
        }
    }
}
void battleships::unblockPlayerField(){
    for (int i=0; i<10; i++){
        for (int j=0; j<10; j++){
            this->_fieldPlayer[i][j]->setDisabled(false);
            if (this->_fieldPlayer[i][j]->styleSheet().contains("* { background-color: rgb(0, 125, 0)}")){
                this->_fieldPlayer[i][j]->setDisabled(true);
            }
        }
    }
}
//block the rival's turn - block his field to avoid click-issue
void battleships::blockRivalField(){
    for (int i=0; i<10; i++){
        for (int j=0; j<10; j++){
            this->_fieldRival[i][j]->setDisabled(true);
        }
    }
}
//unblocks the field, when it's turn to shoot - adjust to have the previosly choosen buttons blocked
void battleships::unblockRivalField(){
    for (int i=0; i<10; i++){
        for (int j=0; j<10; j++){
            this->_fieldRival[i][j]->setDisabled(false);
            if (this->_fieldRival[i][j]->styleSheet().contains("* { background-color: rgb(125, 0, 0)}") ||
                this->_fieldRival[i][j]->styleSheet().contains("* { background-color: rgb(0, 0, 255)}")){
                this->_fieldRival[i][j]->setDisabled(true);
            }
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

void battleships::horizontalOrientation(){
    char orientation = 'h';
    ui->statusLabel->setText("Choose the size of the ship");
    ui->createBattleshipButton->setDisabled(false);
    ui->createCruiserButton->setDisabled(false);
    ui->createDestroyerButton->setDisabled(false);
    ui->createSubmarineButton->setDisabled(false);
    emit shipOrientation(orientation);
}
void battleships::verticalOrientation(){
    char orientation = 'v';
    ui->statusLabel->setText("Choose the size of the ship");
    ui->createBattleshipButton->setDisabled(false);
    ui->createCruiserButton->setDisabled(false);
    ui->createDestroyerButton->setDisabled(false);
    ui->createSubmarineButton->setDisabled(false);
    emit shipOrientation(orientation);
}

void battleships::setPositionPlayer(int i, int j){ //for testing purposes only - should be removed afterwards
    ui->posX->setText("Position x: " + QString::number(i));
    ui->poxY->setText("Position y: " + QString::number(j));
}

//for network connectivity
void battleships::connectSlot(){
    ui->connectButton->hide();
    ui->disconnectButton->show();
    QString ip = ui->ipInput->text();
    QString port = ui->portInput->text();
    std::cout << "Port saved " << std::endl;
    std::cout << "IP saved " << std::endl;
    //emit connection signal;
}
void battleships::disconnectSlot(){
    ui->disconnectButton->hide();
    ui->connectButton->show();
}
void battleships::serverSlot(){
    ui->serverButton->hide();
    ui->clientButton->show();
}
void battleships::clientSlot(){
    ui->clientButton->hide();
    ui->serverButton->show();
}
void battleships::saveName(){
    ui->saveNameButton->hide();
    QString name = ui->nicknameInput->text();
    ui->statusLabel->setText(name);
}
//for gameplay
void battleships::status(char status){
    ui->statusLabel->show();
    switch(status){
        case('p'):
            ui->statusLabel->setText("Invalid location");
            break;
        case('a'):
            ui->statusLabel->setText("Awaiting another player");
            break;
        case('c'):
            ui->statusLabel->setText("Connection established");
            break;
        case('t'):
            ui->statusLabel->setText("Your turn");
            break;
        case('o'):
            ui->statusLabel->setText("Opponent's turn");
            break;
        case('w'):
            ui->statusLabel->setText("!!!YOU WON!!!");
            ui->startButton->setText("Go again");
            ui->startButton->show();
            break;
        case('l'):
            ui->statusLabel->setText("You lost");
            ui->startButton->setText("Go again");
            ui->startButton->show();
            break;
    }
}
//signal from logic about the length of the destroyed ship
void battleships::destroyedShips(int length){
    static int counter = 0;
    switch (length) {
        case(5):
            ui->createBattleshipButton->setDisabled(true);
            ui->createBattleshipButton->setStyleSheet("* { background-color: rgb(125, 0, 0)}");
            ui->createBattleshipButton->show();
            break;

        case(4):
    {
            counter++;
            ui->createCruiserButton->setDisabled(true);
            ui->createCruiserButton->setStyleSheet("* { background-color: rgb(125, 0, 0)}");
            ui->cruiserCounter->show();
            ui->cruiserCounter->setText("x" + QString::number(counter));
            break;
    }

        case(3):
    {
            counter++;
            ui->createDestroyerButton->setDisabled(true);
            ui->createDestroyerButton->setStyleSheet("* { background-color: rgb(125, 0, 0)}");
            ui->destroyerCounter->show();
            ui->destroyerCounter->setText("x" + QString::number(counter));
            break;
    }

        case(2):
    {
            counter++;
            ui->createSubmarineButton->setDisabled(true);
            ui->createSubmarineButton->setStyleSheet("* { background-color: rgb(125, 0, 0)}");
            ui->submarineCounter->show();
            ui->submarineCounter->setText("x" + QString::number(counter));
            break;
    }
    }
}

battleships::~battleships()
{
    delete ui;
}

