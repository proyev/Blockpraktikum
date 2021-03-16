#include "battleship_gui.h"
#include "ui_battleship_gui.h"

battleship_gui::battleship_gui(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::battleship_gui)
{
    ui->setupUi(this);
}

battleship_gui::~battleship_gui()
{
    delete ui;
}

