#include "vl2_4_article.hpp"

Article::Article()
: _name("Undefined"),
  _id(Label::TagName::Undefined),
  _price(0.0),
  _amount(0){ 
  std::cout << "Default constructor art" << std::endl;
  }
Article::Article(const std::string &name,
                 const Label &id,
                 const double &price,
                 const uint64_t &amount)
		: _name(name),
		  _id(id),
		  _price(price),
		  _amount(amount){ 
std::cout << "Constructor art" << std::endl;
		 }

void Article::print(){
	std::cout << "Name: " << _name << std::endl;
	std::cout << "Label: ";  
	_id.print();
        std::cout << std::endl;
	std::cout << "Price: " << _price << std::endl;
	std::cout << "Amount: " << _amount << std::endl;
}


