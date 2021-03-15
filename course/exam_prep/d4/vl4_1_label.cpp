#include "vl4_1_label.hpp"


Label::Label (const Label::TagName &tag):
	_tag(tag) {
		std::cout << "Label constructor" << std::endl;
}

Label::TagName Label::getTag(){
	return _tag;
}

void Label::setTag(const Label::TagName &tag){
	_tag = tag;
}

void Label::print(){
	switch (_tag){
		case TagName::Stationery:
			std::cout << "Stationery" << std::endl;
			break;
		case TagName::Food:
			std::cout << "Food" << std::endl;
			break;
		case TagName::Clothes:
			std::cout << "Clothes" << std::endl;
			break;
		case TagName::Others:
			std::cout << "Others:" << std::endl;
			break;
		case TagName::Undefined:
			std::cout << "Undefined:" << std::endl;
			break;
	}
}
