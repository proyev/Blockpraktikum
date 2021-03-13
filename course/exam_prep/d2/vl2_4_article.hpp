#ifndef ARTICLE_HPP
#define ARTICLE_HPP
#include "vl2_4_label.hpp"

class Article{
	public:
		Article();
		Article(const std::string &name,
			const Label &id,
			const double &price=0.0,
			const uint64_t &amount=0);

		std::string getName() 	{return _name;};
		Label getId()		{return _id;};
		double getPrice()	{return _price;};
		uint64_t getAmount()	{return _amount;};
		void setAmount(const uint64_t &amount){_amount=amount;};
		void print();

	private:
		const std::string 	_name;
		Label 			_id;
		double 			_price;
		uint64_t 		_amount;

		void setId (const Label &id)		{_id=id;};
		void setPrice (const double &price)	{_price=price;};
};

#endif
