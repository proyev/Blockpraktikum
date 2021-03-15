#ifndef LABEL_HPP
#define LABEL_HPP
#include <iostream>
#include <string>

class Label{
	
	public:
	enum class TagName : uint8_t {
			Stationery,
			Food,
			Clothes,
			Others,
			Undefined
		};
		Label(const TagName &tag);
		void setTag(const TagName &tag);
		TagName getTag();
		void print();
	private:
		TagName _tag;


};
#endif
