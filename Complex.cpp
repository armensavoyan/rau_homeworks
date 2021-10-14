#include "Complex.h"

	Complex_Numbers::Complex_Numbers()
		:a(0)
		,b(0)
	{}
	
	Complex_Numbers::Complex_Numbers(int a_, int b_)
		:a(a_)
		,b(b_)
	{}
	
	Complex_Numbers::Complex_Numbers(const Complex_Numbers& obj)
		:a(obj.a)
		,b(obj.b)
	{}
	
	int Complex_Numbers::get_a() const{ return a; }
	int Complex_Numbers::get_b() const{ return b; }
	void Complex_Numbers::set_a(int x){ a = x; }
	void Complex_Numbers::set_b(int x){ b = x; }
	double Complex_Numbers::absolute_value() const{	return sqrt(a * a + b * b); }

Complex_Numbers operator + (Complex_Numbers& obj1, const Complex_Numbers& obj2){
	obj1.set_a(obj1.get_a() + obj2.get_a());
	obj1.set_b(obj1.get_b() + obj2.get_b());
	return obj1;
}

Complex_Numbers operator - (Complex_Numbers& obj1, const Complex_Numbers& obj2){
	obj1.set_a(obj1.get_a() - obj2.get_a());
	obj1.set_b(obj1.get_b() - obj2.get_b());
	return obj1;
}

Complex_Numbers operator * (Complex_Numbers& obj1, const Complex_Numbers& obj2){
	obj1.set_a(obj1.get_a() * obj2.get_a() - obj1.get_b() * obj2.get_b());
	obj1.set_b(obj1.get_a() * obj2.get_b() + obj2.get_a() * obj1.get_b());
	return obj1;
}

Complex_Numbers operator * (Complex_Numbers& obj, int value){
	obj.set_a(obj.get_a() * value);
	obj.set_b(obj.get_b() * value);
	return obj;
}

bool operator < (const Complex_Numbers& obj1, const Complex_Numbers& obj2){
	return obj1.absolute_value() < obj2.absolute_value();
}

void sort_complex_numbers(std::vector<Complex_Numbers>& V){
	for (int i = 0; i < V.size() - 1; ++i){
		for (int j = 0; j < V.size() - i - 1; ++j){
			if (V[j+1] < V[j]){
				std::swap(V[j], V[j + 1]);
			}	
		}
	}
}

void add(Complex_Numbers& obj1, const Complex_Numbers& obj2){ //прибавить
	obj1.set_a(obj1.get_a() + obj2.get_a());
	obj1.set_b(obj1.get_b() + obj2.get_b());
}

void sub(Complex_Numbers& obj1, const Complex_Numbers& obj2){ // отнять 
	obj1.set_a(obj1.get_a() - obj2.get_a());
	obj1.set_b(obj1.get_b() - obj2.get_b());
}

void mul(Complex_Numbers& obj1, const Complex_Numbers& obj2){ //умножение
	obj1.set_a(obj1.get_a() * obj2.get_a() - obj1.get_b() * obj2.get_b());
	obj1.set_b(obj1.get_a() * obj2.get_b() + obj2.get_a() * obj1.get_b());
}

void mull(Complex_Numbers& obj, int value){ //умножение integer-ом
	obj.set_a(obj.get_a() * value);
	obj.set_b(obj.get_b() * value);
}
