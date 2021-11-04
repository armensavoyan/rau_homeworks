#include <iostream>
#include "Complex.h"
int main(){
	Complex_Numbers obj1(1, 2);
	Complex_Numbers obj2(obj1);
	Complex_Numbers obj3(3, 4);
	Complex_Numbers obj4(5, 6);
	Complex_Numbers obj5(7, 8);
	Complex_Numbers obj6(9, 10);
	Complex_Numbers obj7(11, 12);
	Complex_Numbers obj8(13, 14);
	std::vector <Complex_Numbers> V;
	V.push_back(obj1);
	V.push_back(obj2);
	V.push_back(obj3);
	V.push_back(obj4);
	V.push_back(obj5);
	V.push_back(obj6);
	V.push_back(obj7);
	V.push_back(obj8);
	for (int i = 0; i < V.size(); ++i){
		std::cout << V[i].absolute_value() << " ";
	}
	std::cout << std::endl;
	sort_complex_numbers(V);
	for (int i = 0; i < V.size(); ++i){
		std::cout << V[i].absolute_value() << " ";
	}
	std::cout << std::endl;
}
