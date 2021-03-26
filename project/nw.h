#ifndef NW_H
#define NW_H

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

/**
 *  @brief The Nw Class A Network Class
 */
class Nw : public QObject //, public Support
{
    Q_OBJECT
public:  
    /**
     *  @brief Nw Constructor
     *
     *  Sets the byte order of _InOutStream to BigEndian
     *
     *  @param[in] parent QObject acting as parent. Defaults to nullptr.
     **/
    explicit Nw(QObject *parent = nullptr);
    ~Nw();



    /**
     *  @brief Protokollstatus in dem wir uns befinden.
     **/
    enum class protocol: char{OFFLINE,          //Nicht mit Proxy verbunden.
                              PROXYCONNECTED,   // Mit Proxy, aber nicht mit Spieler verbunden.
                              PREGAME,          // Mit Spieler verbunden und am Schiffe platzieren.
                              INGAME};         // Im Spiel

    /**
     *  @brief To describe whos turn it is.
     **/
    enum class turn: char{NONE,
                          WESHOOT,
                          WERESPOND,
                          THEYSHOOT,
                          THEYRESPOND};
    /**
     *  @brief To describe who send the message.
     **/

    enum class messageSender: char{status,
                                   enemy,
                                   player};

    /**
     *  @brief The types of responses we send to an request.
     **/
    enum class response: quint8{ACK=0x00,
                                NACK=0x01,
                                NOTSUPPORTED=0x02,
                                MSGINCOMPLETE=0x03,
                                TIMEOUT=0x04,
                                OTHERERROR=0x20};


private:

    //Netzwerk:
    /**
     *  @brief Server Port number
     **/
    quint16 _port;
    /**
     *  @brief Server IP adress
     **/
    QString _adr;

    QTcpSocket* _socket;
    /**
     *  @brief The Stream that is used for communication via the TCP-Socket socket.
     **/
    QDataStream _InOutStream;
    /**
     *  @brief Threshold that is used to notice a spam attack.
     **/
    const quint32 _CONNECTION_THRESHOLD; //Threshold that is used to notice a spam attack.
    /**
     *  @brief Timer to periodically send the Connection Request from Client to server
     **/
    QTimer *_timerConnReq = new QTimer(this);
    //QTimer *timerLastMsgRecv = new QTimer(this);

    //std::vector<quint8> lastMsg;

    //Spiel:
    /**
     *  @brief Whether we are Client or Server
     **/
    bool _isClient;
    /**
     *  @brief Whether the Player is ready
     **/
    bool _playerReady;
    /**
     *  @brief The status of the connection
     **/
    protocol _status;
    /**
     *  @brief Whether it is our turn
     **/
    turn _turn;
    /**
     *  @brief The Time _timerConnReq is set to.
     **/
    int _timeoutTimeConnReq;



signals:
    //public signals

    //Handshake


    //currently not used because the default param are used:
    /**
     *  @brief Received Connection Request from the other player.
     **/
    void recvConnRequest();
    /**
     *  @brief Received Gameparameter from the other player.
     *
     *  @param[in] Gameparameter as quint8 array
     **/
    void recvGameParam(std::array<quint8,6> a);
    /**
     *  @brief The other players response on the Gameparameter we send.
     *
     *  @param[in] Whether he accepted the parameter
     **/
    void paramAccepted(bool b);
    /**
     *  @brief Received a Game Start Request from the other player.
     **/
    void recvStartRequest();

    //currently not used:
    /**
     *  @brief The result of the handshake.
     *
     *  @param[in] Whether we are connected to the other player
     **/
    void connectedToPlayer(bool b);
    /**
     *  @brief The game starts now.
     *
     *  @param[in] Whether we beginn
     **/
    void gameStartsNow(bool ourTurn); //who starts the game.

    //InGame
    /**
     *  @brief The other player shot on us.
     *
     *  @param[in] The coordinates of the shot.
     **/
    void shotIncoming(struct Support::coordinates c);
    /**
     *  @brief We received the result of our shot
     *
     *  @param[in] Whether we are connected to the other player
     *  @param[in] Coordinates of the sunken ship (if there is one). Defaults to an empty vector.
     **/
    void recvShotResponse(Support::FIELD_STATUS h, std::vector<struct Support::coordinates> sunkenShip = {});

    //always
    /**
     *  @brief Display a message in the GUI TextBox.
     *
     *  @param[in] message
     *  @param[in] sender
     **/
    void displayMessage(const QString message,messageSender s= messageSender::status);
    /**
     *  @brief The connection Status to the Proxy Server changed.
     *
     *  @param[in] Whether we are connected to the Proxy Server.
     **/
    void connectionEstablished(bool connected);//void setConnDiscButton(bool connectButtonState);
    /**
     *  @brief We received the other players name.
     *
     *  @param[in] Other players name
     **/
    void recvEnemyName(const QString enemyName);









public slots:
    //Netzwerk:
    /**
     *  @brief Connects to a server.
     *
     *  Verifies whether the port is in the given range [1024, 65535] and attempts
     *   connection to Host. Also enables slots for TCP-Socket events.
     *
     * @param[in] Server IP Adress
     * @param[in] Server Port
     *
     **/
    void connectToServer( QString adr,QString port);
    /**
     *  @brief Disconnects from server
     *
     *  Eventually results in "closeConnection" being called.
     **/
    void disconnectFromServer();
    /**
     *  @brief Whether the user is Client or Server.
     *
     *  Sets the _isClient to the current value.
     *
     *  @param[in] _isClient value
     **/
    void toggleIsClient(bool b);

    //Spiel:
    /**
     *  @brief Sends a Shoot Command over the network.
     *
     *  Verifies whether it is our turn to shoot and if that is the case sends out
     *  a shoot Command with the Coordinates of the target.
     *
     *  @param[in] Target Coordinate x-value
     *  @param[in] Target Coordinate y-value
     **/
    void shoot(int x, int y);
    /**
     *  @brief Sends the response to the enemies shot over the network.
     *
     *  Verifies whether it's our turn to respond to a shot and if that's the case
     * sends the corresponding response over the network
     *
     *  @param[in] Shot result
     *  @param[in] Coordinates the ship occupied in case a ship sunk. Defaults to empty vector.
     **/
    void shotResponse(Support::FIELD_STATUS status,std::vector<struct Support::coordinates> c={});

    //Handshake
    /**
     *  @brief Sends the Game Parameter over the network.
     *
     *  Verifies whether it's our role to send the Parameter (whether we are Server).
     *
     **/
    void sendParam();
    /**
     *  @brief Sends a Connection Request to the other player.
     *
     *  Checks whether we are the Client. If thats not the case doesn't send out the request.
     *
     **/
    void connectToPlayer();

    //PreGame & Handshake
    /**
     *  @brief Sends out a response to an enemies request.
     *
     *  Verifies whether we are already ingame. If thats the case it doesnt send out a response.
     *
     *  @param[in] Type of response that is send out.
     **/
    void respondToRequest(response r);

    //always
    /**
     *  @brief Toggles the playerReady value
     *
     *  In case the player is ready, a Game Start Request is send out. In case we receive a gameStart Request
     *  we can only accept it if the player is ready.
     **/
    void togglePlayerReady();
    /**
     *  @brief Sends a Chat Message over the network.
     *
     *  Receives the message from the GUI and sends the message via QDataStream.
     *
     * @param[in] Textmessage
     **/
    void sendTextMessage(QString message);
    /**
     *  @brief Sends the Playername over the network.
     *
     *  Receives the name from the GUI and sends it via QDataStream.
     *
     * @param[in] Playername
     **/
    void sendPlayerName(QString playerName);

private slots:
    //Netzwerkaufbau
    /**
     *  @brief Enables connection to a server, e.g. allows sending messages.
     **/
    void _enableConnection();
    /**
     *  @brief Disconnects the socket from the server.
     *
     *  Eventually results in "closeConnection" being called.
     **/
    void _disconnected();
    /**
     *  @brief Handles errors occurring with the TCP-Socket connection.
     *
     *  Eventually results in "closeConnection" being called.
     **/
    void _socketError();
    /**
     *  @brief Closes the connection to a server.
     *   Closes the connection and sends out a signal to the GUI to disable network
     *   funcionalities.
     **/
    void _closeConnection();

    //Receive Data
    /**
     *  @brief Receives and processes incoming data
     *
     *  Uses a QDataStream (_InOutStream) to receive and parse data and sends
     *  received information to the GUI/Logik part.
     */
    void _processInput();
    /**
     * @brief Checks, whether enough bytes can be read from the TCP-Socket.
     *
     *  It is assumed that incoming data is always received in form of the protocol
     *  and therefore that the first two bytes of the message include the type of
     *  command and the length of the message. If this method encounters a problem,
     *  it returns false and closes the connection.
     *
     * @return true if the QString can be read, false if not.
     **/
    bool _assertCmdLength();
    /**
     * @brief Waits until numOfBytes bytes can be read from the TCP connection.
     *  Blocks until it returns.
     *
     * @param[in] numOfBytes
     * @param[in] timeout timeout to be waited for numOfBytes
     * @return true if enough bytes are readable, false if not.
     **/
    bool _waitForReadyRead(
                    const quint16& numOfBytes,
                    const std::chrono::seconds &timeout=std::chrono::seconds(4));
    //Send Data
    /**
     *  @brief Sends a Request to start the game
     *
     *  If the player is not ready yet or we are not connected to the the player yet,
     *  the signal does not get send.
     */
    void _startGameRequest();

    //void  _repeatLastMsg();
    /**
     *  @brief Repeatetly sends out the Connection Request to the other Player
     *
     *  If the Players are not connected yet, and if we are the Client, this function
     *  sends out a Connection Request to the other Player repeatetly until the Players are
     * connected.
     *
     */
    void _timeoutConnReq();
    /**
     *  @brief Ignores the given number on bytes on the Socket
     *
     *  In case we get send data that should be ignored.
     *
     *  @param[in] Number of Bytes to ignore.
     */
    void _ignoreBytesOnSocket(int numOfBytes);
    /**
     *  @brief Checks if we support the incoming Parameter.
     *
     *  Checks if the Param are the default Parameter. In that case it sends out an
     *  Acknowledgement, otherwise it sends out an rejection.
     *
     *  @param[in] Array of the six game parameter
     */
    void _checkParam(std::array<quint8,6> param);
    /**
     *  @brief resets the parameters inside the network class to before the game.
     *
     *  The function is called once the game is over.
     *
     *  @param[in] bool value whether we won
     */
    void _gameOver(bool weWon);

};

#endif // NW_H
