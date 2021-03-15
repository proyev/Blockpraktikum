#ifndef FOOD_HPP
#define FOOD_HPP
#include <iostream>
#include <string>
#include "vl4_1_article.hpp"

class Food : public Article<>{
	public:
		Food(const std::string &name,
		     const uint32_t &best,
		     const double &price=0.0,
		     const uint64_t &amount=0);
		
		uint32_t getBest() {return _best;};
		void setBest(const uint8_t &best){_best=best;};

	private:
		uint32_t _best;


}; //Article<Label>


#endif
