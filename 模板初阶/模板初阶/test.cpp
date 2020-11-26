#include<iostream>

using namespace std;

//函数模板
template<typename T>
void Swap(T& a, T& b) {
	T tmp = b;
	b = a;
	a = tmp;
}
/*
	函数模板只是一个模板, 本身不是函数, 不是可执行代码
	实际可执行的代码在编译时产生
*/


template<class T>
T Add(const T& a, const T& b) {
	return a + b;
}

//普通函数和函数模板共存
int Add(int& a, int& b) {
	return a + b;
}


template<class T, class T2>
T Add(const T& a, const T2& b) {
	return a + b;
}



void test() {
	int a = 1, b = 2;
	double c = 1.0, d = 2.0;
	char e = 'e', f = 'f';

	//隐式实例化, 编译器自动推导
	Swap(a, b);
	Swap(c, d);
	Swap(e, f);

	//强转
	//Swap(a, (int)d); //这里不行是因为强转之后生成一个临时变量(具有常性), 上面要用const接收

	Add(a, b);
	Add(c, d);
	Add(e, f);

	//强制类型转换 --> 不推荐
	Add(a, (int)d);
	//显式实例化: 函数<实例化类型>(参数列表) --> 推荐
	Add<int>(a, d);
}


void test2() {
	int a = 1, b = 2;
	
	//如果参数类型和普通函数完全匹配, 则优先调用普通函数, 不会进行函数模板的实例化(编译器也比较懒~)
	Add(a, b);

	double c = 1.0;
	//如果函数模板可以生成参数类型更加匹配的函数, 则会执行实例化 (更精确)
	Add(a, c);

	//如果指明要显式实例化, 则要执行实例化, 不会调用普通函数
	Add<int>(a, b);
}



template<class T>
struct seqList {
	T* _array;
	size_t _size = 0;
	size_t _capacity = 10;

	seqList(size_t num = 10)
		:_array(new T[num])
	{}

	void push_back(T x) {
		_array[_size++] = x;
	}
};

void test3() {

	//实例化必须为显示实例化
	//类型: 类名<参数类型>       类名 != 类型
	seqList<int> sq;
	seqList<char> sq2;
	seqList<double> sq3;

	sq.push_back(1);
	sq.push_back(2);
	sq.push_back(3);

	sq2.push_back('a');
	sq2.push_back('b');
	sq2.push_back('c');

	sq3.push_back(1.0);
	sq3.push_back(2.0);
	sq3.push_back(3.0);
	  
}


int main() {
	test();
	//test2();
	//test3();

	return 0;
}