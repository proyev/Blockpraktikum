#ifndef BATTLESHIPS_H
#define BATTLESHIPS_H

#include <QWidget>
#include <QObject>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class battleships; }
QT_END_NAMESPACE

class battleships : public QWidget
{
    Q_OBJECT

public:
    battleships(QWidget *parent = nullptr);
    ~battleships();

private:
    Ui::battleships *ui;
    QPushButton *_fieldPlayer[10][10];
    QPushButton *_fieldRival[10][10];

private slots:
            void setPositionPlayer(int i, int j);
//            void setPositionRival(int i, int j);

        signals:
            void positionPlayer(int i, int j);
//            void positionRival(int i, int j);


};
#endif // BATTLESHIPS_H
