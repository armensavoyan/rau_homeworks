#pragma once 
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
//создаем тип комплексных чисел
class Complex_Numbers {
public:
	Complex_Numbers(); //default constructor
	Complex_Numbers(int, int); 
	Complex_Numbers(const Complex_Numbers&); //copy constructor
	int get_a() const;
	int get_b() const;
	void set_a(int);
	void set_b(int);
	double absolute_value() const; //возвращает модуль
private:
	int a; //первая переменная
	int b; //вторая переменная с i
};
//математические операции для комплексных чисел
Complex_Numbers operator + (Complex_Numbers& obj1, const Complex_Numbers& obj2);
Complex_Numbers operator - (Complex_Numbers& obj1, const Complex_Numbers& obj2);
Complex_Numbers operator * (Complex_Numbers& obj1, const Complex_Numbers& obj2);
Complex_Numbers operator * (Complex_Numbers& obj, int value); //умножение integer-ом

void sort_complex_numbers(std::vector<Complex_Numbers>& V);
void add(Complex_Numbers& obj1, const Complex_Numbers& obj2);
void sub(Complex_Numbers& obj1, const Complex_Numbers& obj2);
void mul(Complex_Numbers& obj1, const Complex_Numbers& obj2);
void mull(Complex_Numbers& obj, int value);
