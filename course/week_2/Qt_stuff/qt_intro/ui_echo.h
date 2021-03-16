/********************************************************************************
** Form generated from reading UI file 'echo.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ECHO_H
#define UI_ECHO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EchoApp
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *inputName;
    QLineEdit *inputMessage;
    QPushButton *sendButton;
    QTextBrowser *dialogWindow;

    void setupUi(QWidget *EchoApp)
    {
        if (EchoApp->objectName().isEmpty())
            EchoApp->setObjectName(QString::fromUtf8("EchoApp"));
        EchoApp->resize(304, 253);
        verticalLayoutWidget = new QWidget(EchoApp);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 301, 251));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        inputName = new QLineEdit(verticalLayoutWidget);
        inputName->setObjectName(QString::fromUtf8("inputName"));

        verticalLayout->addWidget(inputName);

        inputMessage = new QLineEdit(verticalLayoutWidget);
        inputMessage->setObjectName(QString::fromUtf8("inputMessage"));

        verticalLayout->addWidget(inputMessage);

        sendButton = new QPushButton(verticalLayoutWidget);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));

        verticalLayout->addWidget(sendButton);

        dialogWindow = new QTextBrowser(verticalLayoutWidget);
        dialogWindow->setObjectName(QString::fromUtf8("dialogWindow"));

        verticalLayout->addWidget(dialogWindow);


        retranslateUi(EchoApp);

        QMetaObject::connectSlotsByName(EchoApp);
    } // setupUi

    void retranslateUi(QWidget *EchoApp)
    {
        EchoApp->setWindowTitle(QCoreApplication::translate("EchoApp", "echo", nullptr));
        inputName->setText(QCoreApplication::translate("EchoApp", "jason", nullptr));
        sendButton->setText(QCoreApplication::translate("EchoApp", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EchoApp: public Ui_EchoApp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ECHO_H
