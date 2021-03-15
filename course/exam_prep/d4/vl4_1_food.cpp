#include "vl4_1_food.hpp"


Food::Food(const std::string &name,
	   const uint32_t &best,
	   const double &price,
	   const uint64_t &amount)
	: Article(name, Label(Label::TagName::Food),
		  price, amount), _best(best)

{

	std::cout << "Constructor Food" << std::endl;

}	 
