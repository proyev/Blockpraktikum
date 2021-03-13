#include "vl2_4_article.hpp"


int main(){
	Article art1=Article();
	Article art2=Article("Pen", Label::TagName::Stationery);
	Article art3=Article("Fish", Label::TagName::Food, 10.0, 100);
	
	std::cout << "-----Getter Test-----" << std::endl;
	std::cout << "Name: " << art1.getName() << std::endl;
	std::cout << "Id: ";
	art1.getId().print();
	std::cout << std::endl;

	std::cout << "Price: " << art1.getPrice() << std::endl;
	std::cout << "Amount: " << art1.getAmount() << std::endl;
	std::cout << "-----Print Test1-----" << std::endl;
	art1.print();
	std::cout << "-----Print Test2-----" << std::endl;
	art2.print();
	std::cout << "-----Price Test3-----" << std::endl;
	art3.print();
	std::cout << "-----Setter Test art3----" << std::endl;
	art3.setAmount(42);
	art3.print();	

	return 0;
}
