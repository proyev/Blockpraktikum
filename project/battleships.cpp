#include "battleships.h"
#include "ui_battleships.h"

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
        }
    }
//    connect(this, &battleships::positionPlayer,
//            [=](int i, int j){
//        ui->posX->setText(QString::number(i));
//        ui->poxY->setText(QString::number(j));
//    });
    connect(this, &battleships::positionPlayer,
            this, &battleships::setPositionPlayer);
}

//void battleships::positionPlayer(int i, int j){

//}

void battleships::setPositionPlayer(int i, int j){
    ui->posX->setText(QString::number(i));
    ui->poxY->setText(QString::number(j));
//    emit testSignal(5);
}

battleships::~battleships()
{
    delete ui;
}

