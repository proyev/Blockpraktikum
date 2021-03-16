#include "echo.h"
#include "ui_echo.h"

EchoApp::EchoApp(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EchoApp)
{
    ui->setupUi(this);
    connect(ui->sendButton, SIGNAL(clicked()),
            this, SLOT(send()));
    connect(ui->inputMessage, SIGNAL(returnPressed()),
            this, SLOT(send()));
}

EchoApp::~EchoApp()
{
    delete ui;
}

void EchoApp::send(){
    QString name = ui->inputName->text(),
            message = ui->inputMessage->text();

    ui->inputMessage->clear();

    QString text = name + ": " + message;

    ui->dialogWindow->append(text);


}

