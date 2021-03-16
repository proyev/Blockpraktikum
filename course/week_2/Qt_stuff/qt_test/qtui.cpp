#include "qtui.hpp"

myui::myui(QWidget *parent)
: QWidget(parent)
{
	//creating the elements
	_pbSet		=new QPushButton("Set", this);
	_pbClose	=new QPushButton("Close", this);
	_outputButton	=new QLabel("Button", this);
	_outputEnter	=new QLabel("Enter", this);
	_outputAny	=new QLabel("Any", this);
	_input		=new QLineEdit(this);
	_layout		=new QVBoxLayout(this);

	//to organize elements within a layout
	_layout->addWidget(_input);
	_layout->addWidget(_outputButton);
	_layout->addWidget(_outputEnter);
	_layout->addWidget(_outputAny);
	_layout->addWidget(_pbSet);
	_layout->addWidget(_pbClose);

	setLayout(_layout);
	//classics	
	connect(_pbSet, SIGNAL(clicked()),
		this, SLOT(setButton()));
	connect(_pbClose, SIGNAL(clicked()),
		this, SLOT(setButton()));
	//methods
	connect(_input, &QLineEdit::returnPressed,
		this, &myui::setEnter);
	//lambda
	connect(this, &myui::mySignal, [&](){
			_outputAny->setText("Any: "+ _input->text());
			});

}



void myui::setEnter(){
	
	_outputEnter->setText("Enter: " + _input->text());
	emit mySignal();
}


void myui::setButton(){
	
	_outputButton->setText("Button: " + _input->text());
	emit mySignal();
}




