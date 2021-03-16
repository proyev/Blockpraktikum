#include "qtui.hpp"
#include <QApplication>

int main(int argc, char **argv){
	QApplication app(argc, argv);

	//to display the pre-saved design
	myui myui;
	myui.show();
	
	//alternative
	//myui *ui = new myui();
	//ui->show();
	
	return app.exec();
}
