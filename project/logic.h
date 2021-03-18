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
    int _endX;
    int _endY;
    int _length;

public:
    explicit Logic(QObject *parent=nullptr);
    void setStartCoordinates(int x, int y){
        _startX = x;
        _startY = y;
    }
    void setEndCoordinates(int x, int y){
        _endX = x;
        _endY = y;
    }

    void setLength(int length){
        _length = length;
    }

    int getStartX(){
        return _startX;
    }
    int getStartY(){
        return _startY;
    }
    int getEndX(){
        return _endX;
    }
    int getEndY(){
        return _endY;
    }
    int getLength(){
        return _length;
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
      //  emit getEndCoordinates();
    }

    void getEndPosition(int i, int j){
        std::cout << "End x: " << i << std::endl;
        std::cout << "End y: " << j << std::endl;
        setEndCoordinates(i, j);
        int posX, posY, length;
        posX = getStartX();
        std::cout << posX << std::endl;
        posY = getStartY();
        std::cout << posY << std::endl;
        length = getLength();
        std::cout << length << std::endl;
        emit draw(posX, posY, i, j, length);
    }

signals:
    void draw(int posX, int posY, int i, int j, int length);
//    void getEndCoordinates();

};

#endif // LOGIC_H
