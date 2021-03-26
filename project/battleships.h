#ifndef BATTLESHIPS_H
#define BATTLESHIPS_H

#include <QWidget>
#include <QObject>
#include <QPushButton>
#include <string>
#include "nw.h"

namespace Ui { class battleships; }
//QT_END_NAMESPACE

/**
 *  @brief The battleships class A GUI Class
 */
class battleships : public QWidget
{
    Q_OBJECT


public:
    /**
     *  @brief battleship Constructor
     *
     *  @param[in] parent QObject acting as parent. Defaults to nullptr.
     */
    battleships(QWidget *parent = nullptr);
    ~battleships();

private:
    /**
    *  @brief Pointer to the GUI.
    **/
    Ui::battleships *ui;
    /**
    *  @brief Pointer to 2D array of buttons representing player's field.
    **/
    QPushButton *_fieldPlayer[10][10];
    /**
    *  @brief Pointer to 2D array of buttons representing opponent's field.
    **/
    QPushButton *_fieldRival[10][10];

private slots:
            /**
             * @brief horizontalOrientation - sets the orientation of to be created ship to
             * horizontal.
             *
             * @param orientation
             * Sends this information to the Player Class of Logic via emitted signal.
             *
             * Unblocks the buttons to choose the type of ship to be placed.
             *
             **/
            void horizontalOrientation();
            /**
             * @brief verticalOrientation - sets the @param orientation of to be created ship to
             * vertical.
             *
             * Sends this information to the Player Class of Logic via emitted signal.
             *
             * Unblocks the buttons to choose the type of ship to be placed.
             *
             **/
            void verticalOrientation();
            /**
             * @brief createBattleship - sets @param length of to be created ship to 5
             *
             * Sends this information to the Player Class of Logic via emitted signal.
             *
             * Unblocks the player's field to place the ship on the field.
             **/
            void createBattleship();
            /**
             * @brief createCruiser - sets @param length of to be created ship to 4
             *
             * Sends this information to the Player Class of Logic via emitted signal.
             *
             * Unblocks the player's field to place the ship on the field.
             **/
            void createCruiser();
            /**
             * @brief createDestroyer - sets @param length of to be created ship to 3
             *
             * Sends this information to the Player Class of Logic via emitted signal.
             *
             * Unblocks the player's field to place the ship on the field.
             **/
            void createDestroyer();
            /**
             * @brief createSubmarine- sets @param length of to be created ship to 2
             *
             * Sends this information to the Logic via emitted signal.
             *
             * Unblocks the player's field to place the ship on the field.
             **/
            void createSubmarine();

            /**
             * @brief blockPlayerField - blocks the player's field:
             *
             *      1) after a single ship was created - to avoid random signals and additional checks
             *
             *      2) after the player starts the game - to avoid confusion and prevent unwanted checks as well
             **/
            void blockPlayerField();
            /**
             * @brief blockRivalField - blocks the opponent's field:
             *
             *      1) before the game was launched simply to leave this space inactive as it is not needed at this stage of the game
             *
             *      2) after player makes a move during the game, thereby controlling the correct change of turns and helps to prevent
             *      errors and missclicks
             **/
            void blockRivalField();

            /**
             * @brief updatePlayerHP - creates and updates the player's health bar:
             *
             *      1) with every received hit from the opponent it will be decreased
             *
             *      2) once less then 15% health left - will change color to red, indicating 'critical'
             *
             *      3) once reaches zero - will end the game and provide the information about game results
             **/
            void updatePlayerHP();
            /**
             * @brief updateRivalHP - creates and updates the player's health bar:
             *
             *      1) with every received hit from the player it will be decreased
             *
             *      2) once less then 15% health left - will change color to red, indicating 'critical'
             *
             *      3) once reaches zero - will end the game and provide the information about game results
             **/
            void updateRivalHP();

        signals:
            /**
             * @brief positionPlayer - signal to send the coordinates to place the ship
             * @param i
             * @param j
             */
            void positionPlayer(int i, int j);
            /**
             * @brief positionRival - signal to send the coordinates to make a move
             * @param i
             * @param j
             */
            void positionRival(int i, int j);

            /**
             * @brief createShip - signal to the Player Logic Class about the length
             * of the ship to be created
             * @param length
             */
            void createShip(int length); // sends the info about the type of ship to be created
            /**
             * @brief shipOrientation - the signal to the Player Logic Class about the orientation of the
             * ship to be created
             * @param orientation
             */
            void shipOrientation(char orientation);
            /**
             * @brief checkCoordinates - signal to the Player Logic Class to check the location the player
             * wants to place the ship at
             * @param startX
             * @param startY
             */
            void checkCoordinates(int startX, int startY);

            /**
             * @brief blockField - signal to block the field
             */
            void blockField();
            /**
             * @brief unblockField - signal to unblock the field
             */
            void unblockField();
            /**
             * @brief playerHP - signal to update the player's HP
             */
            void playerHP();
            /**
             * @brief rivalHP - signal to update the opponent's HP
             */
            void rivalHP();
            /**
             * @brief playerTurn - signal to inform the player about the first move
             */
            void playerTurn();
            /**
             * @brief statusSignal - sends the status information to provide the suitable response
             * @param satus
             */
            void statusSignal(char satus);

            /**
             * @brief connectSignal - signal to Nw Network Class with the information of the ip and port to
             * connect to
             * @param ip
             * @param port
             */
            void connectSignal(QString ip, QString port);
            /**
             * @brief startGame - signal to Nw Network Class about player being ready to start the game
             */
            void startGame();
            /**
             * @brief disconnectSignal - signal to Nw Network Class to disconnect
             */
            void disconnectSignal();
            /**
             * @brief isClient - signal to Nw Network Class informing whether the player wants to act as a
             * Server or as a Client
             * @param info
             */
            void isClient(bool info);

            /**
             * @brief sendTextMessage - signal to Nw Network Class with the text message from player in order to be
             * printed into chat
             * @param message
             */
            void sendTextMessage(QString message);
            /**
             * @brief sendPlayerName - signal which sends the nickname of the player
             * @param name
             */
            void sendPlayerName(QString name);

public slots:
            /**
             * @brief gameSetup - revies information from the Player Logic Class about where and what type of ship to put onto the field.
             * Creates graphical respresentation on the field based on the parameters.
             * Updates the counter of the total number of the ships, that can be created.
             *
             * @param startX
             * @param startY
             * @param orientation
             * @param length
             */
            void gameSetup(int startX, int startY,
                          char orientation,
                          int length);
            /**
             * @brief destroyedShips - receives the information from Player Class within logic about the ship which was destroyed
             * @param[in] length indicates the type of the destroyed ship
             *
             *     The corresponding visualisation will be provided and the counter of the destroyed ships will
             *       be updated
             **/
            void destroyedShips(int length);
            /**
             * @brief placementValidation - receives the information from Player Class within logic about the placement of the ship at a
             * chosen location.
             *
             * @param[in] valid
             *
             * @if not valid - will provide a corresponding message
             **/
            void placementValidation(bool valid);

            /**
             * @brief turn - receives the message from the Nw Class of Network part indicating who of two players will make the first move
             *
             * @param[in] turn
             * @if turn - the opponent's field will be unblocked to make a move
             * the corresponding information will be provided
             *
             * Otherwise, the corresponding information will be provided and the field stays blocked
             */
            void turn(bool turn);
            /**
             * @brief status - receives signals from different parts of the project
             *
             * @param[in] status - will indicate the actions to be performed next and reacts to the performed actions to
             * indicate state of the game, connection status and more.
             * In some cases might only print corresponding messages.
             * In some cases though, will immedeately perform actions in response
             */
            void status(char status);
            /**
             * @brief connectionStatus - receives information from Nw Network Class about the state of the connection
             * @param[in] connection
             *
             */
            void connectionStatus(bool connection);

            /**
             * @brief unblockPlayerField - receives the coordinates from the Player Logic Class about the areas
             * that have to be blocked around the placed ship on the field. Saves those coordinates and,
             * based upon this information unblocks the field for further placement of the ships, but keeping
             * the certain areas blocked to avoid misplacement.
             *
             * @param startX
             * @param startY
             * @param endX
             * @param endY
             */
            void unblockPlayerField(int startX, int startY,
                                    int endX, int endY);
            /**
             * @brief unblockRivalField - unblocks the opponent's field for the player to make a move.
             */
            void unblockRivalField();
            /**
             * @brief movePlayerInterpreter - receives the coordinates from the Player Logic Class about move
             * made by the player and provides the corresponding graphical output.
             * @param posX
             * @param posY
             * @param status - provides information, whether the move was a "Hit" or a "Miss".
             */
            void movePlayerInterpreter(int posX, int posY, char status);
            /**
             * @brief moveRivalInterpreter - receives the coordinates from the Player Logic Class about the move
             * made by the opponent and provides the corresponding graphical output.
             * @param posX
             * @param posY
             * @param status- provides information, whether the move was a "Hit" or a "Miss".
             */
            void moveRivalInterpreter(int posX, int posY, char status);

            /**
             * @brief messageRival - receives the messages from the Nw Class for the build-in
             * chat between players
             * @param message - displays the opponent name and message
             * @param s - to monitor the status
             */
            void messageRival(QString message, Nw::messageSender s= Nw::messageSender::status);


};
#endif // BATTLESHIPS_H
