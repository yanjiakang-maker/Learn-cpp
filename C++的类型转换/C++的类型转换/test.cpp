#include <iostream>

using namespace std;


void test() {
	//隐式类型转换：意义相似的类型
	int a = 10;
	char b = 'a';
	float c = 2.3;

	//隐式类型转换
	a = b;
	c = b;

	//强制类型转换
	int ptrInt = (int)&a;
	cout << ptrInt << endl;

	int* ptr = (int*)a; // 0xa
	//风险很大：非法访问
	cout << *ptr << endl;
}


void test2() {
	int a = 10;
	char b = 'b';
	double f = 3.5;

	//static_cast<类型>: 支持C语言的隐式类型转换
	//可读性强
	b = static_cast<char> (a);
	a = static_cast<int> (f);

	//reinterpret_cast<类型>:支持C语言的强制类型转换
	//可读性强
	int* ptr = reinterpret_cast<int*> (a);

	//const_cast<类型>:去除数据的const属性
	const int* ptr2 = &a;
	int* ptr3 = const_cast<int*>(ptr2);

	const int c = 20;
	int d = c;

}


class Base {
public:
	virtual void fun() {
		cout << "Base fun()" << endl;
	}
};

class Derived : public Base {
public:
	virtual void fun() {
		cout << "Derived fun()" << endl;
	}

	int _b = 100;
};

void test3() {
	//向上转型: 切片 (子类-->父类)
	Base base;
	Derived derived;
	base = derived;
	//向下转型: 父类-->子类
	Base base2;
	Derived derived2;
	//derived2 = static_cast<Derived>(base2);
	Derived* ptr = static_cast<Derived*>(&base2);
	//非法访问
	cout << ptr->_b << endl;

	//这种情况就是安全的
	Base* bPtr = &derived2;
	Derived* ptr2 = static_cast<Derived*>(bPtr);
	cout << ptr2->_b << endl;


	//dynamic_cast<子类>:多态场景的向下转型 (必须是多态)
	//安全检查: 安全就正常转换, 不安全返回nullptr
	ptr = dynamic_cast<Derived*> (&base2);
	ptr2 = dynamic_cast<Derived*>(bPtr);
}


int main() {
	//test();
	test3();

	return 0;
}