#ifndef LOGIC_H
#define LOGIC_H
#include <iostream>

#include <QObject>

class Logic : public QObject
{
    Q_OBJECT
public:
    explicit Logic(QObject *parent=nullptr);

public slots:
    void testSlot(int i, int j){
        std::cout << "Coordinate x: " << i << std::endl;
        std::cout << "Coordinate y: " << j << std::endl;
        std::cout << "===========" << std::endl;
    }

};

#endif // LOGIC_H
