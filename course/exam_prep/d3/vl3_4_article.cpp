#include "vl3_4_label.hpp"
#include "vl3_4_article.hpp"
#include <iostream>

template <>//or template <Label>
Article<>::Article() //<> or template <Label>
	: _name("Undefined"),
	  _id(Label::TagName::Undefined),
	  _price(0.0),
	  _amount(0){
	 	std::cout << "Default const" << std::endl;
	  }



/*template <class T>
void Article<T>::print(){
	std::cout << "Name: " << _name << std::endl;
	std::cout << "Label: ";  
	_id.print();
        std::cout << std::endl;
	std::cout << "Price: " << _price << std::endl;
	std::cout << "Amount: " << _amount << std::endl;

	}
*/
