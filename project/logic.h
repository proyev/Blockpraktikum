#ifndef LOGIC_H
#define LOGIC_H
#include <iostream>
#include <QObject>

class Logic : public QObject
{
    Q_OBJECT
public:
    explicit Logic(QObject *parent = nullptr);

signals:


public slots:
    void testSlot(int a){
        std::cout<<a<<std::endl;
    }
};

#endif // LOGIC_H
