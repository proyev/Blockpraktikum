#include "vl4_1_article.hpp"
#include "vl4_1_food.hpp"

int main(){
	Article<> *art1=new Article<>();
	Article<int> *art2=new Article<int>("Pen", -17);
	Article<> *art3;
	
	Food f=Food("Fish", 1);
	std::cout << "Food Print" << std::endl;
	f.print();
	

	std::cout << "---Print Test art1---" << std::endl;
	(*art1).print();
	std::cout << "---Print Test art2---" << std::endl;
	art2->print();

	delete art1;
	delete art2;

	std::cout << "END" << std::endl;

	return 0;
}
