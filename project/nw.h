#ifndef NW_H
#define NW_H

//#include "battleships.h"
#include "battleShipLogic.hpp"

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QDataStream>
#include <vector>
#include <string>
#include <map>
#include <iterator>
#include <QTimer>
#include <thread>
#include <chrono>
#include <future>
#include <iostream>
#include <cassert>

class Nw : public QObject //, public Support
{
    Q_OBJECT
public:
    explicit Nw(QObject *parent = nullptr);
    ~Nw();

    //enum class hitStatus: char{MISSED, HIT, DESTROYED, FINISHED,NOTYOURTURN, OUTOFBOUNDS, INVALID};

    //enum class protocol: char{CLIENT,CLIENT_PROXYCONNECTED,CLIENT_CONNREQSEND,CLIENT_PARAMRECV,CLIENT_ACKSEND,
    //                                      SERVER,SERVER_PROXYCONNECTED,SERVER_CONNREQRECV,SERVER_PARAMSEND,SERVER_ACKRECV,
    //                                      PLAYER_READY,OURTURN,THEIRTURN};

    //enum class serverprotocolStatus: char{BEGINNING,PROXYCONNECTED,}


    //--------------ProtokollStatus----------------------------------
    enum class protocol: char{OFFLINE,          //Nicht mit Proxy verbunden.
                              PROXYCONNECTED,   // Mit Proxy, aber nicht mit Spieler verbunden.
                              PREGAME,          // Mit Spieler verbunden und am Schiffe platzieren.
                              INGAME};         // Im Spiel

    enum class turn: char{NONE,
                          WESHOOT,
                          WERESPOND,
                          THEYSHOOT,
                          THEYRESPOND};
    enum class messageSender: char{status,
    enemy,
    player};
    enum class response: quint8{ACK=0x00,
    NACK=0x01,
    NOTSUPPORTED=0x02,
    MSGINCOMPLETE=0x03,
    TIMEOUT=0x04,
    OTHERERROR=0x20};
    //struct cmd{
    //    quint8 bitcode;
    //    quint16 maxLength;
    //    std::vector<quint8> values;
    //};

    //cmd ConnReq{0x01,0x00};

    //enum class commands: quint8{
    //                      CONNREQ,
    //                      GAMEPARAM,
    //                      STARTGAMEREQ,
    //                      SHOOT,
    //                      REQRESPONSE,
    //                      SHOTRESPONSE};

    //std::map<enum commands, cmd> map_1;
    //map_1[commands::CONNREQ]={0x01,0x00};

private:

    //Netzwerk:
    quint16 _port;
    QString _adr;
    QTcpSocket* _socket;
    QDataStream _InOutStream; //The Stream that is used for communication via the TCP-Socket socket.
    const quint32 _CONNECTION_THRESHOLD; //Threshold that is used to notice a spam attack.

    QTimer *timerConnReq = new QTimer(this);
    QTimer *timerLastMsgRecv = new QTimer(this);

    std::vector<quint8> lastMsg;

    //Spiel:
    bool _isClient;
    bool _playerReady;
    protocol _status;
    turn _turn;

    int _timeoutConnReq;



signals:
    //public signals

    //Handshake
    void recvConnRequest();
    void recvGameParam(std::array<quint8,6> a);
    void paramAccepted(bool b);

    //PreGame
    void recvStartRequest();
    void connectedToPlayer(bool b); //void gameStartSignal();
    void gameStartsNow(bool ourTurn); //who starts the game.

    //InGame
    void shotIncoming(struct Support::coordinates c);
    void recvShotResponse(Support::FIELD_STATUS h, std::vector<struct Support::coordinates> sunkenShip = {});

    //always
    void displayMessage(const QString message,messageSender s= messageSender::status);
    void connectionEstablished(bool connected);//void setConnDiscButton(bool connectButtonState);
    void recvEnemyName(const QString enemyName);









public slots:
    //Netzwerk:
    void connectToServer( QString adr,QString port);
    void disconnectFromServer();
    void toggleIsClient(bool b);

    //Spiel:
    void shoot(int x, int y);
    void shotResponse(Support::FIELD_STATUS status,std::vector<struct Support::coordinates> c={});

    //Handshake
    void sendParam();
    void connectToPlayer();

    //PreGame & Handshake
    void respondToRequest(response r);

    //always
    void togglePlayerReady();
    void sendTextMessage(QString message);
    void sendPlayerName(QString playerName);

private slots:
    void enableConnection();
    void disconnected();
    void socketError();
    void closeConnection();
    void processInput();
    void startGameRequest();
    bool _assertCmdLength();
    bool _waitForReadyRead(
                    const quint16& numOfBytes,
                    const std::chrono::seconds &timeout=std::chrono::seconds(4));
    void  _repeatLastMsg();
    void timeoutConnReq();
    void _cmdInvalid();
    void _ignoreBytesOnSocket(int numOfBytes);
    void checkParam(std::array<quint8,6> param);
};

#endif // NW_H
