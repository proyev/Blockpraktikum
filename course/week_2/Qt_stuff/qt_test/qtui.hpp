#ifndef QTUI_HPP
#define QTUI_HPP

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QObject>

class myui : public QWidget{
	Q_OBJECT //macro
	public:
		myui(QWidget *parent=nullptr);
		
	private:
		QPushButton 		*_pbSet;
		QPushButton 		*_pbClose;
		QLabel			*_outputButton;
		QLabel			*_outputEnter;
		QLabel			*_outputAny;
		QLineEdit		*_input;
		QLayout			*_layout;

		void setEnter();

	private slots:
		void setButton();
		
		signals:
		void mySignal();

};
#endif
