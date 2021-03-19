#ifndef LOGIC_H
#define LOGIC_H
#include <iostream>

#include <QObject>
#include "battleships.h"

class Logic : public QObject
{
    Q_OBJECT
private:
    int _startX;
    int _startY;
    char _orienatation;
    int _length;

public:
    explicit Logic(QObject *parent=nullptr);
    void setStartCoordinates(int x, int y){
        _startX = x;
        _startY = y;
    }

    void setLength(int length){
        _length = length;
    }

    void setOrientation(char orientation){
        _orienatation = orientation;
    }

    int getStartX(){
        return _startX;
    }
    int getStartY(){
        return _startY;
    }
    int getLength(){
        return _length;
    }

    char getOrientation(){
        return _orienatation;
    }

public slots:
    void testSlot(int i, int j){
        std::cout << "Coordinate x: " << i << std::endl;
        std::cout << "Coordinate y: " << j << std::endl;
        std::cout << "===========" << std::endl;
    }

    void createShip(int length){
        std::cout << "The ship with the length of: " << length << " will be created" << std::endl;
        setLength(length);
    }
    void getStartPosition(int i, int j){
        std::cout << "Start x: " << i << std::endl;
        std::cout << "Start y: " << j << std::endl;
        setStartCoordinates(i, j);
        emit draw(i, j, getOrientation(), getLength());
    }
    void slotOrientation(char orientation){
        setOrientation(orientation);
    }



signals:
    void draw(int posX, int posY, char orientation, int length);
//    void getEndCoordinates();

};

#endif // LOGIC_H
