#ifndef BATTLESHIP_GUI_H
#define BATTLESHIP_GUI_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>



QT_BEGIN_NAMESPACE
namespace Ui { class battleship_gui; }
QT_END_NAMESPACE

class battleship_gui : public QWidget
{
    Q_OBJECT

public:
    battleship_gui(QWidget *parent = nullptr);
    ~battleship_gui();

private:
    Ui::battleship_gui *ui;
};
#endif // BATTLESHIP_GUI_H
