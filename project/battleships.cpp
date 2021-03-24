#include "battleships.h"
#include "ui_battleships.h"
#include <QPalette>
#include <QRadioButton>
#include <QSignalBlocker>
#include <QMessageBox>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

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
                        });//when clicked - will send the coordinates to the logical part - required only for ship placement
            connect(_fieldRival[i][j], &QPushButton::clicked,
                    this, [=](){
                            emit positionRival(i, j);
            });//when clicked on the rival field, will get the position of the button clicked
        }
    }
    battleships::setMinimumSize(900, 300);
    battleships::setMaximumSize(900, 300);

    ui->createBattleshipButton->setDisabled(true);
    ui->createCruiserButton->setDisabled(true);
    ui->createDestroyerButton->setDisabled(true);
    ui->createSubmarineButton->setDisabled(true);
    connect(ui->horizontalOptionButton, &QRadioButton::clicked,
            this, &battleships::horizontalOrientation);
    connect(ui->verticalOptionButton, &QRadioButton::clicked,
            this, &battleships::verticalOrientation);

    connect(ui->createBattleshipButton, &QPushButton::clicked,
            this, &battleships::createBattleship);
    connect(ui->createCruiserButton, &QPushButton::clicked,
            this, &battleships::createCruiser);
    connect(ui->createDestroyerButton, &QPushButton::clicked,
            this, &battleships::createDestroyer);
    connect(ui->createSubmarineButton, &QPushButton::clicked,
            this, &battleships::createSubmarine);

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
    connect(ui->startButton, &QPushButton::clicked,
            this,[&](){
        emit status('a');
        emit startGame();//if doesn't work - try by-value
    });
    connect(ui->startButton, &QPushButton::clicked,
            ui->playerHP, &QPushButton::show);
    connect(ui->startButton, &QPushButton::clicked,
            ui->rivalHP, &QPushButton::show);
    connect(this, &battleships::playerTurn,
            this, &battleships::unblockRivalField);
    ui->connectButton->setDisabled(true);
    ui->disconnectButton->hide();
    connect(ui->connectButton, &QPushButton::clicked,
            this, [&](){
        QString ip = ui->ipInput->text();
        QString port = ui->portInput->text();
        if (ip != "" && port != ""){
            std::cout << "signal emited" << std::endl;
            emit connectSignal(ip, port);
        }else{
            std::cout << "no info" << std::endl;

        }
    });

    connect(ui->disconnectButton, &QPushButton::clicked,
            this, [&](){
        ui->disconnectButton->hide();
        ui->connectButton->show();
        emit disconnectSignal();
    });
    connect(ui->clientRadioButton, &QRadioButton::clicked,
            this, [&](){
        ui->connectButton->setDisabled(false);
        emit isClient(true);
    });
    connect(ui->serverRadioButton, &QRadioButton::clicked,
            this, [&](){
        ui->connectButton->setDisabled(false);
        emit isClient(false);
    });

    ui->playerHP->setMaximumWidth(25);
    ui->playerHP->setMinimumWidth(25);
    ui->playerHP->setDisabled(true);
    ui->playerHP->hide();
    ui->rivalHP->setMaximumWidth(25);
    ui->rivalHP->setMinimumWidth(25);
    ui->rivalHP->setDisabled(true);
    ui->rivalHP->hide();
    connect(this, &battleships::playerHP,
            this, &battleships::updatePlayerHP);
    connect(this, &battleships::rivalHP,
            this, &battleships::updateRivalHP);

    connect(this, &battleships::statusSignal,
            this, &battleships::status);

    ui->hideChatButton->hide();
    connect(ui->saveNameButton, &QPushButton::clicked,
            this, [&](){
        ui->saveNameButton->hide();
        QString name = ui->nicknameInput->text();
        ui->statusLabel->setText(name);
        ui->nicknameInput->setDisabled(true);
    });//change to slot from logic
    connect(ui->chatButton, &QPushButton::clicked,
            this, [&](){
        ui->chatButton->hide();
        ui->hideChatButton->show();
        battleships::setMaximumSize(1100, 300);
        battleships::setMinimumSize(1100, 300);
    });
    connect(ui->chatMessage, &QLineEdit::returnPressed,
            this, [&](){
         QString name = ui->nicknameInput->text(),
                 message = ui->chatMessage->text();
         ui->chatMessage->clear();
         ui->chatBox->append("<" + name + ">" + " " + message);
    });
    connect(ui->hideChatButton, &QPushButton::clicked,
            this, [&](){
        ui->chatButton->show();
        ui->hideChatButton->hide();
        battleships::setMaximumSize(900, 300);
        battleships::setMinimumSize(900, 300);
    });

    connect(this, &battleships::blockField,
            this, &battleships::blockPlayerField);
    //connect(this, &battleships::unblockField,
     //       this, &battleships::unblockPlayerField); - should be first call from logic
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

void battleships::createBattleship(){
    int length = 5;
    ui->statusLabel->setText("Choose the location");
    emit createShip(length);
    //here should be connection to logic via emits of the new logical signals

}
void battleships::createCruiser(){
    int length = 4;
    ui->statusLabel->setText("Choose the location");
    emit createShip(length);
    //emit unblockPlayerField(); - this should be emited from logic
    //connection to logic via emit
}
void battleships::createDestroyer(){
    int length = 3;
    ui->statusLabel->setText("Choose the location");
    emit createShip(length);
    //emit unblockPlayerField(); - shoould be emited from logic
    //connection to logic
}
void battleships::createSubmarine(){
    int length = 2;
    ui->statusLabel->setText("Choose the location");
    emit createShip(length);
    //emit unblockPlayerField(); - should be emited from logic
    //connection to logic
}
//this slot will draw the ship itself, by making changing the color of buttons
//and making them 'pressed'
void battleships::placementValidation(bool valid){
    if (!valid){
        emit status('p');
    }
}
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
//will recieve info form logic, if placement is possible
void battleships::unblockPlayerField(int startX, int startY, int endX, int endY){
    static std::vector <std::vector <int>> coordinates;
    static int counter = 0;
    std::vector<int> currentInfo{startX, startY, endX, endY};
    coordinates.push_back(currentInfo);
    if (counter == 0){
        for (int i=0; i<10; i++){
            for (int j=0; j<10; j++){
                this->_fieldPlayer[i][j]->setDisabled(false);
    }}
        counter++;
    }else{
        for (int i=0; i<10; i++){
            for (int j=0; j<10; j++){
                this->_fieldPlayer[i][j]->setDisabled(false);
//            if (this->_fieldPlayer[i][j]->styleSheet().contains("* { background-color: rgb(0, 125, 0)}")){
//                this->_fieldPlayer[i][j]->setDisabled(true);
//          }
            }
            }
        for (auto &region : coordinates){
            for (int i=region[0]; i<=region[1]; i++){
                for (int j=region[2]; j<region[3]; j++){
                    this->_fieldPlayer[i][j]->setDisabled(true);
                }
            }
        }
    }

    //block specified region

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
            emit(playerHP());
            emit statusSignal('t');
            emit playerTurn();
            break;
        case('M'):
            battleships::_fieldPlayer[posX][posY]->setStyleSheet("* { background-color: rgb(0, 0, 255)}");
            emit statusSignal('t');
            emit playerTurn();
            break;
    }
}
void battleships::movePlayerInterpreter(int posX, int posY, char status){
    switch (status) {
        case('H'):
            battleships::_fieldRival[posX][posY]->setStyleSheet("* { background-color: rgb(125, 0, 0)}");
            emit(rivalHP());
            break;
        case('M'):
            battleships::_fieldRival[posX][posY]->setStyleSheet("* { background-color: rgb(0, 0, 255)}");
    }
}

//for network connectivity
void battleships::connectionSatus(bool connection){
    QMessageBox msgBox;
    if (connection){
        ui->connectButton->hide();
        ui->disconnectButton->show();
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Connection established");
        msgBox.setStandardButtons(QMessageBox::Close);
        emit statusSignal('c');
    }else{
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Connection failed!");
        msgBox.setStandardButtons(QMessageBox::Close);
        emit statusSignal('i');
    }
}

//for gameplay
void battleships::turn(bool turn){ // change of the turns - start of the game only
    if (turn){
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("You begin the game!");
        msgBox.setStandardButtons(QMessageBox::Close);
        emit status('t');
    }
}
void battleships::destroyedShips(int length){ // will print the information about already destroyed ships
    switch (length) {
        case(5):
            ui->createBattleshipButton->setDisabled(true);
            ui->createBattleshipButton->setStyleSheet("* { background-color: rgb(125, 0, 0)}");
            ui->createBattleshipButton->show();
            break;

        case(4):
    {       static int counter = 0;
            counter++;
            ui->createCruiserButton->setDisabled(true);
            ui->createCruiserButton->setStyleSheet("* { background-color: rgb(125, 0, 0)}");
            ui->cruiserCounter->show();
            ui->cruiserCounter->setText("x" + QString::number(counter));
            break;
    }

        case(3):
    {       static int counter = 0;
            counter++;
            ui->createDestroyerButton->setDisabled(true);
            ui->createDestroyerButton->setStyleSheet("* { background-color: rgb(125, 0, 0)}");
            ui->destroyerCounter->show();
            ui->destroyerCounter->setText("x" + QString::number(counter));
            break;
    }

        case(2):
    {       static int counter = 0;
            counter++;
            ui->createSubmarineButton->setDisabled(true);
            ui->createSubmarineButton->setStyleSheet("* { background-color: rgb(125, 0, 0)}");
            ui->submarineCounter->show();
            ui->submarineCounter->setText("x" + QString::number(counter));
            break;
    }
    }
}
void battleships::status(char status){  // prints the information about current satus of the game
    ui->statusLabel->show();
    switch(status){
        case('p'):
            ui->statusLabel->setText("Invalid location");
            break;
        case('a'):
            ui->statusLabel->setText("Awaiting another player");
            break;
        case('c'):
            ui->statusLabel->setText("Connection to proxy established");
            ui->clientRadioButton->setDisabled(true);
            ui->serverRadioButton->setDisabled(true);
            break;
        case('i'):
            ui->statusLabel->setText("Invalid connection to proxy");
            break;
        //case(''): connection between players
            //ui->statusLabel->setText("")
            //emit unblock of the buttons - start placing or smth
            //break;
        case('t'):
            ui->statusLabel->setText("Your turn");
            emit unblockRivalField();
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
        //case('s'):
            //ui->statusLabel->setText('The game begin');

    }
}

//updates hp bar
void battleships::updatePlayerHP(){
    static int damage = 0;
    damage++;
    if (damage > 29){
        ui->playerHP->hide();
        emit statusSignal('l');
    }else if(damage > 25){
        ui->playerHP->setStyleSheet("* {background-color : rgb(125, 0, 0)}");
        ui->playerHP->setText("");
        ui->playerHP->setMinimumHeight(250 - damage * (250/30));
        ui->playerHP->setMaximumHeight(250 - damage * (250/30));
        ui->playerHP->move(290, 35 + damage * (250/30));
    }else{
        ui->playerHP->setMinimumHeight(250 - damage * (250/30));
        ui->playerHP->setMaximumHeight(250 - damage * (250/30));
        ui->playerHP->move(290, 35 + damage * (250/30));
    }
}
void battleships::updateRivalHP(){
    static int damage = 0;
    damage++;
    if (damage > 29){
        ui->rivalHP->hide();
        emit statusSignal('w');
    }else if(damage > 25){
        ui->rivalHP->setStyleSheet("* {background-color : rgb(125, 0, 0)}");
        ui->rivalHP->setText("");
        ui->rivalHP->setMinimumHeight(250 - damage * (250/30));
        ui->rivalHP->setMaximumHeight(250 - damage * (250/30));
        ui->rivalHP->move(460, 35 + damage * (250/30));
    }else{
        ui->rivalHP->setMinimumHeight(250 - damage * (250/30));
        ui->rivalHP->setMaximumHeight(250 - damage * (250/30));
        ui->rivalHP->move(460, 35 + damage * (250/30));
    }
}

battleships::~battleships()
{
    delete ui;
}

