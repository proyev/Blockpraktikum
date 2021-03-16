#ifndef ECHO_H
#define ECHO_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class EchoApp; }
QT_END_NAMESPACE

class EchoApp : public QWidget
{
    Q_OBJECT

public:
    EchoApp(QWidget *parent = nullptr);
    ~EchoApp();

private:
    Ui::EchoApp *ui;

private slots:
        void send();
};
#endif // ECHO_H
