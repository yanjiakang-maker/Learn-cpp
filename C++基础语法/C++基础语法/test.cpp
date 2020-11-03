#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<stdio.h>
#include<time.h>

using namespace std;


//命名空间 namespace
namespace bite {
	void print(int a) {
		printf("%d\n", a);
	}

	int a;
	int b;

	//可以嵌套定义
	namespace bite_69 {
		void fun1(int a) {
			printf("%d\n", a);
		}

		int a;
		int b;
	}
}

//可以分段定义,编译器会合并相同的命名空间
//相同的命名空间不能定义重复的变量和函数
namespace bite {
	int c;
	int d;

	void fun2() {
		printf("fun2()\n");
	}
}


int a;
int b;

/*
	命名空间成员使用方式
	1. 命名空间 :: 成员
	2. 引入成员 using + 命名空间 :: 成员    后面使用成员时不需要再加作用域
	     引入后成员暴露在全局域中, 如果全局域中有同名成员, 则会导致命名冲突
	3. 展开命名空间 using + 命名空间   命名空间中所有的成员暴露在全局域中
*/

using bite::fun2;
//using namespace bite;

void test() {
	bite::a = 1;
	bite::print(bite::a); //bite命名空间下的成员a
	bite::print(a); //全局a

	bite::bite_69::a = 2;
	bite::c = 3;
	bite::fun2();
	fun2();
}


void test2(int a) {
	a = 10; //局部域
	bite::a = 20; //命名空间域
	bite::bite_69::a = 30; //命名空间域
	::a = 40; //全局域
}


//输入输出
void test3() {
	int a = 10;
	int b;
	printf("%d\n", a);
	scanf("%d", &b);
	
	//C++输入输出 :  头文件<iostream> + std命名空间
	//不需要显示指定输入输入变量的格式, 支持连续的输入输出
	std::cout << a << std::endl;
	std::cin >> b >> a;

	const char* p = "1234";
	int* pa = &a;
	std::cout << pa << std::endl; // 非字符串指针输出地址
	std::cout << p << std::endl; // 字符串指针输出内容
}


//缺省参数: 给参数定义一个默认值, 实际使用时, 如果没有传参, 对应的形参使用默认值
//全缺省 : 所有参数都有缺省值
void test4(int a = 1, int b = 2, int c = 3) {
	cout << a << " " << b << " " << c << endl;
}

//半缺省 : 部分参数有缺省值
//      必须从右向左连续依次赋值, 中间不能有间隔
void test5(int a, int b = 1, int c = 2) {
	cout << a << " " << b << " " << c << endl;
}

//缺省值只能出现在声明或者定义的地方, 不能同时出现 (编译器有选择困难症, 不能写二义性的代码)
void test6(int a = 1, int b = 2, int c = 3);
void test6(int a, int b, int c) {
	cout << a << " " << b << " " << c << endl;
}


//函数重载 : 函数名相同, 参数不同, 且在同一个作用域
//参数不同 : 类型, 个数, 顺序不同
//仅有返回值类型不同, 不能构成函数重载
int Add(int a, int b) {
	return a + b;
}

float Add(float a, float b) {
	return a + b;
}

int Add(int a, int b, int c) {
	return a + b + c;
}

int Add(char a, int b) {
	return a + b;
}

int Add(int a, char b) {
	return a + b;
}

//void Add(int a, char b) {
//	return a + b;
//}


void test7() {
	int a = 1;
	int b = 2;
	float c = 1.5;
	float d = 2.5;
	char f = 'a';
	int e = 3;
	Add(a, b);
	Add(c, d);
	Add(a, b, e);
	Add(a, f);
	Add(f, b);
}

////extern "C" 让编译器按照C语言的编译规则进行编译
//extern "C" {
//	int sub(int a, int b);
//	int mul(int a, int b);
//}
//void test8() {
//	sub(1, 2);
//	mul(2, 8);
//}


//引用
void test9() {
	//引用 : 类型 + & + 引用名称
	//引用在定义时必须要初始化
	int a = 10;
	//a的别名
	int& ra = a;
	int& ra2 = a;
	ra2 = 30;
	ra = 100;
	a = 1000;

	cout << &a << endl;
	cout << &ra << endl;
	cout << &ra2 << endl;

	int b = -1;
	//引用定义之后, 不会再去更改实体的指向
	// 这里是赋值操作, 并不是让ra作为b的别名
	ra = b;
	ra = -100;
}

void test10() {
	//const 引用
	const int a = 10;
	const int& ra = a;
	const int& r = 10;

	double d = 2.0;
	double& rd = d;

	int c = d;
	//d隐式类型转换, 生成一个临时的整型变量, rd2指向的位此临时变量
	//临时变量具有常性, 所以要加个const
	const int& rd2 = d;
}


void Swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void Swap(int& ra, int& rb) {
	int tmp = ra;
	ra = rb;
	rb = tmp;
}

void t() {
	int a = 1;
	int b = 2;
	Swap(&a, &b);
	cout << a << " " << b << endl;
	Swap(a, b);
	cout << a << " " << b << endl;
}

int& Add(int& a) {
	return ++a;
}

//引用作返回值: 注意返回变量的生命周期一定要大于函数的生命周期
int& Add2(int a) {
	return ++a;
}

void t2() {
	int a = 0;
	int& b = Add(a); 
	int c = Add(a);
	int& d = Add2(a); //引用类型变量 d指向Add2()函数栈帧中的局部变量a, 当Add2函数结束之后变量a销毁
					  //如果是int d = Add2(a) 则没有问题, 因为是开辟了一个新的空间保存a的值
	cout << d << endl;
	cout << a << endl;
	cout << d << endl;
}


struct A {
	int array[10000];
};

void fun1(A a) {
}
void fun2(A& a) {
}
void t3() {
	A a;
	int n = 100000;
	size_t begin = clock();
	for (int i = 0; i < n; i++)
		fun1(a);
	size_t end = clock();
	cout << "fun1(int): " << end - begin << endl;

	begin = clock();
	for (int i = 0; i < n; i++)
		fun2(a);
	end = clock();
	cout << "fun2(int&): " << end - begin << endl;
}

A g;

A fun3() {
	return g;
}

A& fun4() {
	return g;
}

void t4() {
	A a;
	int n = 100000;
	size_t begin = clock();
	for (int i = 0; i < n; i++)
		fun1(a);
	size_t end = clock();
	cout << "fun3(): " << end - begin << endl;

	begin = clock();
	for (int i = 0; i < n; i++)
		fun2(a);
	end = clock();
	cout << "fun4(): " << end - begin << endl;
}

//在底层 引用通过指针实现   定义一个引用类型变量相当于定义一个指针类型变量
//语法: 引用是别名, 不是指针, 没有发生拷贝 
void t5() {
	int a = 10;
	int* pa = &a;
	*pa = 20;

	int& ra = a;
	ra = 30;
}


//内联函数: 编译器编译时, 会进行函数指令的展开, 没有栈帧的开销, 提高代码效率
//代替宏函数使用
inline int ADD(int a, int b) {
	return a + b;
}
//inline 只是一个建议, 编译器会根据实际情况进行判断, 如果代码简单, 直接展开, 代码复杂则不会展开
inline void fun5() {
	for (int i = 0; i < 10000; i++) {
		int a = i;
		int b = a * i;
		int c = b * i;
	}
}

void t6() {
	int c = ADD(3, 5);
	fun5();
}


void t7() {
	//auto : C++中, 自动类型推导, 不代表具体类型
	//编译时, 根据初始化表达式自动推导 (所以啊, 必须初始化)
	//auto相当于类型的占位符, 具体类型在编译时进行推导
	auto a = 2;
	auto f = 3.5;
	auto c = 'a';
	auto d = 'a' + 'b';
	cout << typeid(a).name() << endl;
	cout << typeid(f).name() << endl;
	cout << typeid(c).name() << endl;
	cout << typeid(d).name() << endl;

	//auto可以定义多个变量, 但是类型要一致(只做一次推导)
	auto a1 = 2, c1 = 6;
	//auto a2 = 2.5, c2 = 5;

	//auto定义指针时, 加不加*,没有区别
	auto pa = &a;
	auto* pa2 = &a;
	cout << typeid(pa).name() << endl;
	cout << typeid(pa2).name() << endl;

	//定义引用时必须加&符号
	auto& ra = a; //int&
	auto ra2 = a; //int
}
////函数参数类型不能使用auto
//void fun6(auto a) {
//}
////定义数组不能用auto
//auto array[] = { 0, 1, 2, 3, 4 };


//范围for ->   要迭代的变量  :  迭代范围
void t8() {
	int array[] = { 1, 2, 3, 4, 5, 6 };
	for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++)
		cout << array[i] << " ";
	cout << endl;

	//范围for : 使用场景: 数据范围确定 
	for (auto e : array)
		cout << e << " ";
	cout << endl;
}


//指针值nullptr
void t9() {
	int* p = NULL; // 等价于 int* p = 0;
}

void fun7(int a) {
	cout << "fun7(int)" << endl;
}

void fun7(int* pa) {
	cout << "fun7(int*)" << endl;
}

struct AS {

};

void t10() {
	fun7(NULL); //编译器默认NULL为整型的0, 而不是指针空值
	fun7((int*)NULL);// NULL有二义性: 指针空值 和 整型0

	//nullptr: 指针空值, 意义明确
	fun7(nullptr);

	//nullptr可以隐式转换成任意的指针类型(内置和自定义)
	int* p = nullptr;
	char* p1 = nullptr;
	float* p2 = nullptr;
	AS* pas = nullptr;

	//nullptr类型为: nullptr_t
	cout << typeid(nullptr).name() << endl;
	cout << sizeof(nullptr) << endl;

	auto p3 = nullptr;
	cout << typeid(p3).name() << endl;
}




int main() {
	//test();
	//test2(0);
	//test3();
	//test4(1, 2, 3);
	//test4();
	//test4(100, 200, 300);
	//test5(10);
	//test6();
	//test7();
	//test8();
	//test9();
	//test10();
	//t();
	//t2();
	//t3();
	t4();
	//t6();
	//t7();
	//t8();
	//t10();

	return 0;
}