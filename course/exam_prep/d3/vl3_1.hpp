#ifndef TEMPLATE_HPP
#define TEMPLATE_HPP
#include <iostream>

template <typename T>
T add(T num1, T num2){

	return num1 + num2;
}

T add(T num1, T num2, T num3){
	
	return num1 + num2 + num3;
}

template <typename U, typename Y>
auto add(U num1, Y num2) -> decltype(num1 + num2){
	return num1 + num2;
}

#endif
