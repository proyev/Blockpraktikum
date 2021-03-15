#ifndef ARTICLE_HPP
#define ARTICLE_HPP
#include <iostream>
#include "vl3_4_label.hpp"

template <class T=Label>//Article<> and Article<Label> are the same thing
class Article{
        public:
                Article();
                Article(const std::string &name,
                        const T     &id,
                        const double &price=0.0,
                        const uint64_t &amount=0);

                std::string getName()   {return _name;};
                T getId()               {return _id;};
                double getPrice()       {return _price;};
                uint64_t getAmount()    {return _amount;};
                void setAmount(const uint64_t &amount){_amount=amount;};
                void print();

        private:
                const std::string       _name;
                T                       _id;
                double                  _price;
                uint64_t                _amount;

                void setId (const T &id)                {_id=id;};
                void setPrice (const double &price)     {_price=price;};
};

template <class T>// pretty much as <Label> in the case
Article<T>::Article()//<> or <Label>
: _name("Undefined"),
  _id(T::TagName::Undefined),
  _price(0.0),
  _amount(0){
  std::cout << "Default constructor art" << std::endl;
  }

template <class T>
Article<T>::Article(const std::string &name,
                 const T &id,
                 const double &price,
                 const uint64_t &amount)
                : _name(name),
                  _id(id),
                  _price(price),
                  _amount(amount){
std::cout << "Constructor art" << std::endl;
                 }
template <class T>
void Article<T>::print(){
	std::cout << "Name: " <<_name<<std::endl;
	std::cout << "Label: ";
	_id.print();
	std::cout << std::endl;
	std::cout << "Price: " << _price << std::endl;
	std::cout << "Amount: " << _amount << std::endl;
}


#endif
