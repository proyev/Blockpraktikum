#include "nw.h"

Nw::Nw(QObject *parent) : QObject(parent),
    _CONNECTION_THRESHOLD(20000),
    _isClient(false),
    _playerReady(false),
    _status(protocol::OFFLINE),
    _turn(turn::NONE),
    _timeoutTimeConnReq(10000)
{
    _InOutStream.setByteOrder(QDataStream::BigEndian);
    //Alle connects() innerhalb der klasse kommen hierherein
    connect(_timerConnReq,&QTimer::timeout,this,&Nw::_timeoutConnReq);
}

void Nw::connectToServer(QString adr, QString port){

    emit displayMessage("Verbindungsversuch...");

    bool okPort=false;
    _port = port.toUShort(&okPort);
    _adr = adr;
    _socket = new QTcpSocket(this);


    if(okPort){

        QString textMessage = "connecting to server: ";
        emit displayMessage(textMessage + _adr +":" + port);

        std::cout<<"connecting to server:"<<_adr.toStdString()<<":"<<port.toStdString()<<std::endl;
        _socket->connectToHost(_adr, _port);

        //emit setConnDiscButton(false);
    }
    else{
        emit displayMessage("Fehler. Ungültige Portnummer.");
        return;
    }


    connect(_socket, SIGNAL(connected()),
             this, SLOT(_enableConnection()) );
    connect(_socket, SIGNAL(disconnected()),
             this, SLOT(_disconnected()) );
    connect(_socket, SIGNAL(error(QAbstractSocket::SocketError)),
             this, SLOT(_socketError()) );
    connect(_socket, SIGNAL(destroyed()),
             this, SLOT(_closeConnection()) );


}

void Nw::disconnectFromServer(){
    emit displayMessage("Disconnecting from server.");
    _socket->disconnectFromHost();
    _status = protocol::OFFLINE;
    _turn = turn::NONE;
}

void Nw::toggleIsClient(bool isClient){
    if (_status != protocol::PROXYCONNECTED && _status != protocol::OFFLINE){
        std::cout<<"You cant change that now."<<std::endl;
        return;
    }
    _isClient=isClient;
    if (_isClient){ // Falls man Client ist muss der Timer für die periodischen Spielstart befehle gestartet werden.
        _timerConnReq->start(0);
    }
    std::cout<<"isClient is beeing called. We are now: "<<_isClient<<std::endl;
    displayMessage("You are now: "+ (QString)((_isClient) ? "Client" : "Server"));
}

void Nw::_enableConnection(){
    assert(_socket != nullptr);
    emit displayMessage("Connected.");
    std::cout<<"connected to server"<<std::endl;

    _InOutStream.setDevice(_socket);

    connect(_socket, SIGNAL(readyRead()), this, SLOT(_processInput()));

    _status = protocol::PROXYCONNECTED;

    //timer starten wenn man sich zum ersten mal mit dem server verbindet.
    //_timerConnReq->start(_timeoutTimeConnReq);
    _timeoutConnReq();

    emit connectionEstablished(true);

}

void Nw::_disconnected(){
    emit displayMessage("Disconnecting/Deleting Socket");
    _socket->deleteLater();
    _status = protocol::OFFLINE;
    _turn = turn::NONE;
}

void Nw::_socketError(){
    emit displayMessage("Connection closed or could not connect.");
    _socket->deleteLater();
    _status = protocol::OFFLINE;
    _turn = turn::NONE;
}

void Nw::_closeConnection(){
     emit displayMessage("You are now offline.");
     _InOutStream.setDevice(nullptr);
     emit connectionEstablished(false);
     _status = protocol::OFFLINE;
     _turn = turn::NONE;
}

void Nw::_processInput(){
    while(_InOutStream.atEnd() == false) {
        {
        if(_socket->bytesAvailable() > _CONNECTION_THRESHOLD){
            displayMessage("Verdacht auf DOS Angriff. Verbindung wird abgebrochen.");
            _socket->abort();
            return;
        }

        else if(_assertCmdLength() == false) {
            displayMessage("Nachricht unvollständig. Verbindung wird abgebrochen.");
            _socket->abort();
            return;
        }
        }


    quint8 cmd,
           cmdLength;

    _InOutStream >> cmd >> cmdLength;

    switch(cmd){
        case 0x01: //Verbindungsanfrage empfangen, Nachrichtenlänge ist 2.
        std::cout << "Connection request received"<<std::endl;
            if(cmdLength > 0x00){
                displayMessage("0x01:Nachricht ungültig. Verbindung wird abgebrochen.");
                _socket->abort();
                return;
            }
            else if(_status != protocol::PROXYCONNECTED){
                //Wie soll das interpretiert werden? Wir sind doch schon verbunden? -> wird ignoriert.
                return;
            }
            else if (_isClient == true){
                //dürfen wir theoretisch nicht annehmen? oder doch?
                respondToRequest(response::NACK); //erstmal ablehnen, vll später ändern.
                return;
            }

            displayMessage("ConnReq received.");

            //falls mit variablen param gearbeitet werden soll dann muss hier ein signal an die logik gesendet werden.
            //emit recvConnRequest();  //wants the logic to call our send param function. -> automatisch???

            //mit statischen param:
            sendParam();
            break;

        case 0x02: //Aushandeln der Spielfeldparameter
            if (cmdLength > 0x06){
                displayMessage("0x02:Nachricht ungültig. Verbindung wird abgebrochen.");
                _socket->abort();
                return;
            }
            else if (cmdLength < 0x06){
                _ignoreBytesOnSocket(cmdLength);
                respondToRequest(response::MSGINCOMPLETE);
                return;
            }

            std::array<quint8,6> param;
            for(auto &x: param){
                _InOutStream >> x;
            }


            if(_status != protocol::PROXYCONNECTED){
                displayMessage("Protokollfehler cmd 0x02: Verbindungsabbruch.");
                _socket->abort();
                return;
            }
            else if (_isClient == false){
                displayMessage("Protokollfehler cmd 0x02: Verbindungsabbruch.");
                _socket->abort();
                return;
            }

            displayMessage("Spielparameter empfangen.");



            //Falls wir mit variablen Param. arbeiten müssen die Param. mit einem signal an die logik gesendet werden:
            //emit recvGameParam(param);

            //da wir aber mit statischen param arbeiten werde ich den check innerhalb der klasse machen:
            _checkParam(param);

            break;

        case 0x03: //Spielbeginn Anfrage
            if(cmdLength > 0x00){
                displayMessage("0x03:Nachricht ungültig. Verbindung wird abgebrochen.");
                _socket->abort();
                return;
            }

            if(_status != protocol::PREGAME){
                displayMessage("Protokollfehler cmd 0x03: Verbindungsabbruch.");
                _socket->abort();
                return;
            }

            if (_playerReady){ //send ready
                respondToRequest(response::ACK);
            }
            else{ //send not ready
                respondToRequest(response::NACK);
            }

            break;

        case 0x04: //Der Gegner schiesst auf uns.
            {
            if (cmdLength != 0x02){
                displayMessage("Protokollerror cmd 0x04: Schuss empfangen aber Format ungültig.");
                _socket->abort();
                return;
            }

            quint8 x,y;
            _InOutStream >> x >> y;
            Support::coordinates c;
            c = {(int) x, (int) y};


            if (_status != protocol::INGAME){
                displayMessage("Enemy tried to shoot. We are not ingame.");
                shotResponse( Support::NONVALID);
                return;
            }
            else if(_turn != turn::THEYSHOOT){
                displayMessage("Enemy tried to shoot. Its not their turn.");
                shotResponse( Support::NOTYOURTURN);
                return;
            }

            _turn = turn::WERESPOND;
            emit displayMessage("Schuss auf uns.");
            emit shotIncoming(c);
            }
            break;

        case 0x10: //Antwort auf Anfragen
            if (cmdLength != 0x01){
                displayMessage("Protokollerror cmd 0x10:Format ungültig.");
                _socket->abort();
                return;
            }

            quint8 statuscode;
            _InOutStream>>statuscode;

           if(_status == protocol::PREGAME){ //falls es sich um die antwort auf eine spielbeginn anfrage handelt.

               switch(statuscode){
               case 0x00:
                    _turn = turn::WESHOOT;
                    _status = protocol::INGAME;
                    emit displayMessage("Spielstart. Wir beginnen.");
                    emit gameStartsNow(true);
                    break;
               //------------------------------------------------------------
               case 0x01:
                   emit displayMessage("Other party has rejected the GameStart or is not ready yet.");
                   break;
               case 0x02:
                   emit displayMessage("Protokollerror 0x10:Pregame cmd not supported.");
                   _socket->abort();
                   break;
               case 0x03:
                   emit displayMessage("repeating the last message");
                   //_repeatLastMsg();
                   break;
               case 0x04:
                   emit displayMessage("Protokolleror 0x10:We took too long responding. Timeout.");
                   _socket->abort();
                   break;
               case 0x20: //sonstiger Fehler.
                   emit displayMessage("Protokolleror 0x10:'Sonstiger Fehler'");
                   _socket->abort();
                   break;
               default:
                   emit displayMessage("Protokollerror Type responsecode unknown.");
                   _socket->abort();
                   return;
               //---------------------------------
                }

            }
           else if (_status == protocol::PROXYCONNECTED){ //Falls wir uns noch im handshake befinden

                switch(statuscode){
                case 0x00:
                    emit displayMessage("Other party has accepted the game param.");
                    _status = protocol::PREGAME;
                    connectedToPlayer(true); // -> signal das wir uns jetzt in der vorbereitungsphase befinden.
                    //emit paramAccepted(true);
                    break;
                case 0x01:
                    emit displayMessage("Other party has rejected the game param.");
                    //emit paramAccepted(false);
                    break;
                case 0x02:
                    //emit paramAccepted(false);
                    emit displayMessage("Other party does not support these game param.");
                    break;
                case 0x03:
                    emit displayMessage("repeating the last message");
                    //_repeatLastMsg();
                    break;
                case 0x04:
                    emit displayMessage("We took too long responding. Timeout.");
                    _socket->abort();
                    break;
                case 0x20: //sonstiger Fehler.
                    emit displayMessage("Protokollerror 'Sonstiger Fehler'");
                    _socket->abort();
                    break;
                default:
                    emit displayMessage("Protokollerror Type responsecode unknown.");
                    _socket->abort();
                    return;
                }
            }

           else if (_status == protocol::INGAME){
                 switch(statuscode){
                 case 0x04:
                       emit displayMessage("Timeout. We took to long.");
                     break;
                 default:
                       emit displayMessage("Protokollerror Type responsecode unknown.");
                       _socket->abort();
                 }
           }

           else { //Falls wir uns in einem anderen Protokollstatus befinden.
                std::cout<<"error. shouldnt be possible"<<std::endl;
                emit displayMessage("error should not be possible. ");
                return;
            }

            break;



        case 0x11: // Der Gegner schickt uns die Antwort auf unseren Schuss.
        {
            bool islegitim = true;
            if (cmdLength > 0x0D){ //Nachricht sollte nicht länger als 13 sein.
                displayMessage("Protokollerror cmd 0x11:Format ungültig.");
                _socket->abort();
                return;
            }
            if (_status != protocol::INGAME){
                displayMessage("Not ingame! the enemy shouldnt respond to a shot. Verbindungsabbruch.");
                _socket->abort();
                islegitim = false;
            }

            else if (_turn != turn::THEYRESPOND){
                //shotResponse(hitStatus::Support::NOTYOURTURN);
                displayMessage("not the enemies turn to respond to a shot! Verbindungsabbruch.");
                _socket->abort();
                islegitim = false;
            }


            emit displayMessage("Receiving shot in network class");

            quint8 shotResult;
            _InOutStream >> shotResult;

            if(shotResult<(quint8)0x04){
                _turn = turn::THEYSHOOT;
            }

            if(shotResult==0x02 || shotResult==0x03){ //Nur falls die Schiffe vesenkt werden werden die Koordinaten mitgesendet
                std::vector<struct Support::coordinates> sunkenShip ((cmdLength-1)/2);
                for(int i=0; i<((cmdLength-1)/2);i++){
                    quint8 x,y;
                    _InOutStream >> x >> y;
                    sunkenShip[i] = {(int)x,(int)y};
                }
                if(islegitim){
                    if ((Support::FIELD_STATUS)shotResult == Support::HIT_AND_SUNK_PLAYER){
                        _gameOver(true);
                    }
                    emit recvShotResponse(( Support::FIELD_STATUS)shotResult,sunkenShip);

                }
                break;
            }

            if(islegitim){
                emit recvShotResponse(( Support::FIELD_STATUS)shotResult);
            }
            break;
        }

        case 0x81:
            { // Ohne die geschweiften klammern kommt es zu einem error.
            QString txtMessage;
            _InOutStream >> txtMessage;
            emit displayMessage(txtMessage, messageSender::enemy);
            }
            break;

        case 0x82:
            { // Ohne die geschweiften klammern kommt es zu einem error.
            QString enemyName;
            _InOutStream >> enemyName;
            emit displayMessage("Recv. Enemy Name: " + enemyName);
            emit recvEnemyName(enemyName);
            }
            break;

        default:
            respondToRequest(response::NOTSUPPORTED);
            _ignoreBytesOnSocket(cmdLength);
            displayMessage("Not supported command received.");
        }
    }
}

void Nw::shoot(int x, int y){
    if(_status!=protocol::INGAME){
        std::cout<<"You are not allowed to shoot."<<std::endl;
        return;
    }
    else if(_turn != turn::WESHOOT){
        std::cout<<"Not our turn to shoot!"<<std::endl;
        return;
    }
    _turn = turn::THEYRESPOND;
    std::cout<<"shoot is beeing called..."<<std::endl;
    quint8 shootCmd=0x04,
            length=0x02;

    std::cout<<"Sending Shot to position: "<<QString::number(x).toStdString()<<
                              ","<<QString::number(y).toStdString()<<std::endl;
    std::cout<<QString::number(x).toStdString()<<","
                                      <<QString::number(y).toStdString()<<std::endl;

    QString textMessage = "Sending shot to position: ";
    emit displayMessage(textMessage + QString::number(x) +"," + QString::number(y));

    //_InOutStream<<shootCmd<<length<<c[0]<<c.y;
    _InOutStream<<shootCmd<<length<<(quint8)x<<(quint8)y;
}

void Nw::shotResponse( Support::FIELD_STATUS shotResult,std::vector<struct Support::coordinates> sunkShip){
    std::cout << "shotResponse was called" << std::endl;
    bool legitimateShot=true;
    if(_status!=protocol::INGAME){
        displayMessage("You are not allowed to respond to a shot! Not ingame");
        legitimateShot = false;
        return;
    }
    else if(_turn != turn::WERESPOND){
        displayMessage("Not our turn to respond to a shot!");
        legitimateShot = false;
        return;
    }
    else if(shotResult == Support::NONVALID || shotResult==  Support::OUTOFBOUNDS){
        _turn = turn::THEYSHOOT;
        legitimateShot= false;
    }
    else if (legitimateShot){
        _turn = turn::WESHOOT;
    }

    std::cout<<"shotResponse is beeing called..."<<std::endl;
    QString textMessage = "responding to shot.";
    emit displayMessage(textMessage);

    _InOutStream<<(quint8)0x11<<(quint8)(sunkShip.size()*2+1)<<(quint8)shotResult;
    for (auto &value: sunkShip){
        _InOutStream<<(quint8)value.X<<(quint8)value.Y;
    }

    if (legitimateShot && (shotResult == Support::HIT_AND_SUNK_PLAYER)){
        _gameOver(false);
    }


    //Falls das Spiel nicht beendet ist:


    //ansonsten turn zurück auf none setzen und verbindung trennen?

}

void Nw::_startGameRequest(){
    if (_status != protocol::PREGAME){
        std::cout<<"Not allowed to call this method"<<std::endl;
        return;
    }
    else if (_playerReady == false){
        std::cout<<"Player not ready yet."<<std::endl;
        return;
    }

    quint8 requestCmd=0x03,
            length=0x00;

    displayMessage("Sending GameRequest");

    _InOutStream<<requestCmd<<length;
}

void Nw::sendParam(){
    if (_status != protocol::PROXYCONNECTED){
        std::cout<<"you are not supposed to call this function now."<<std::endl;
        return;
    }
    else if (_isClient){
        std::cout<<"Not our turn to send Param. We are Client. Server sends param."<<std::endl;
        return;
    }
    std::cout<<"sendParam is beeing called..."<<std::endl;
    quint8 paramList[8]={0x02,0x06,0x0A,0x0A,0x01,0x02,0x03,0x04};
    for(auto &x: paramList){
        _InOutStream << x;
    }
    //falsch!!! nur für übungszwecke!!!
    //_status = protocol::INGAME;
    //_InOutStream<<0x02<<0x06<<0x0A<<0x0A<<0x01<<0x02<<0x03<<0x04;
}

void Nw::connectToPlayer(){
    if (_status != protocol::PROXYCONNECTED){
        std::cout<<"You are not supposed to call this function now."<<std::endl;
        return;
    }
    else if (_isClient!=true){
        std::cout<<"We are not the server. We cant init. the connection"<<std::endl;
        return;
    }
    quint8 connectCmd = 0x01,
            length = 0x00;
    _InOutStream<<connectCmd<<length;
}

void Nw::respondToRequest(response r){
    if (_status != protocol::PROXYCONNECTED && _status != protocol::PREGAME){
        std::cout<<"You are not supposed to call this function now."<<std::endl;
        return;
    }
    if (_status == protocol::PROXYCONNECTED
            && r == response::ACK){
        _status = protocol::PREGAME;
        connectedToPlayer(true);
        std::cout << "respond to request sets _status to Pregame"<<std::endl;
    }
    else if (_status == protocol::PREGAME
             && r == response::ACK){
        _status = protocol::INGAME;
        _turn = turn::THEYSHOOT;
        std::cout<<"Spielstart. Der Gegner beginnt."<<std::endl;
        displayMessage("Spielstart. Der Gegner beginnt.");
        emit gameStartsNow(false);
    }


    std::cout<<"respondToRequst is beeing called..."<<std::endl;
    quint8 responseCmd = 0x10,
            length=0x01;
    //check if we are valid to send an Ack
     //if valid:
    if(r==response::ACK){
        std::cout<<"sending ACK.."<<std::endl;
    }

    _InOutStream<<responseCmd<<length<<(quint8)r;

}

void Nw::togglePlayerReady(){
    if (_status != protocol::PREGAME){
        std::cout<<"cant change that now"<<std::endl;
        return;
    }
    _playerReady=!_playerReady;
    if(_playerReady){
        _startGameRequest(); //Sendet eine Spielbeginn Anfrage an den anderen Spieler.
    }
}

bool Nw::_assertCmdLength() { //Now checks whether the cmd is fully here. -> may have to be altered for chat functionality

    /* According to the Qt-Doku, Streams have no ability to check for available
     *  bytes. However, it must be ensured that enough bytes are available!
     *  Additionally, peeking data from the socket requires adjusting the byte
     *  order, reinterpret_cast from quint32* to char* is not sufficient!
     */

    // For reading the QString length
    if(_waitForReadyRead(2) == false)
        return false;

    char peeked[2];
    _socket->peek(peeked, 2);
    quint8 cmd = peeked[0];
    quint16 cmdLength = peeked[1] + 2;

    if(cmd == 0x81 || cmd == 0x82){                             //Falls es sich um eine ChatNachricht oder den Spielernamen handelt!
        if(_waitForReadyRead(6) == false)
            return false;

        char peeked[6];
        _InOutStream.device()->peek(peeked, 6);
        quint32 peekedLength = 0;
        for(int i =2;i<6;i++) {
            peekedLength <<= 4;
            peekedLength  |= peeked[i];
        }
        // For the whole string
        return _waitForReadyRead(peekedLength + 6);

    }


    //std::cout<<"-assertCmdLength: "<<peeked[1]<<","<<(quint16)peeked[1]<<std::endl;
    //std::cout<<"_assertCmdLength peeked cmdLength of: "<<cmdLength<<std::endl;

    return _waitForReadyRead(cmdLength);
}

bool Nw::_waitForReadyRead( const quint16 &numOfBytes,
                                 const std::chrono::seconds &timeout ) {

    auto bytesAvailable = std::async( std::launch::async,
                  [&]() {
                    while(_socket->bytesAvailable() <  numOfBytes)
                        ;
                    return true;
                  });

    return bytesAvailable.wait_for(timeout) == std::future_status::ready;
}

void Nw::sendTextMessage(QString message){
    _InOutStream << (quint8)0x81 << (quint8)0x00 << message;
}

void Nw::sendPlayerName(QString playerName){
    _InOutStream << (quint8)0x82 << (quint8)0x00 << playerName;
}

//void  Nw::_repeatLastMsg(){
//    static int count = 0;
//    count += 1;
//}

void Nw::_timeoutConnReq(){

    if (_status == protocol::PROXYCONNECTED && _isClient){
        emit displayMessage("ConnReq is send periodically.");
        connectToPlayer();
        _timerConnReq->start(_timeoutTimeConnReq);
        return;
    }
    _timerConnReq->stop();
}


void Nw::_ignoreBytesOnSocket(int numOfBytes){
    quint8 byte;
    for(int i=0;i<numOfBytes;i++){
        _InOutStream >> byte;
    }
}

void Nw::_checkParam(std::array<quint8,6> param){
    std::array<quint8,6> standartParam = {0x0A,0x0A,0x01,0x02,0x03,0x04};
    if (param == standartParam){
        //parameter werden von uns akzeptiert.
        respondToRequest(response::ACK);
        displayMessage("Accepted Param.");
    }
    else{
        //parameter werden von uns nicht unterstützt.
        respondToRequest(response::NOTSUPPORTED);
        displayMessage("Rejected Param.");
    }
}

void Nw::_gameOver(bool weWon){
    _status = protocol::PROXYCONNECTED;
    _playerReady = false;
    _turn = turn::NONE;

    std::cout<<"Nw:gameover called"<<std::endl;
    displayMessage( weWon ? "Network: We won" : "Network: We lost.");
}

Nw::~Nw(){
    delete _socket;
    delete _timerConnReq;
    //delete timerLastMsgRecv;
};
