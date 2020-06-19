#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>


//命名空间
namespace bite {
	//可以定义变量, 函数. 也可以嵌套定义命名空间
	int a;
	int b;

	void fun1(int a) {
		printf("%d\n", a);
	}

	namespace bite_69 {
		int a;
	}
}


void test0() {
	//1. 使用命名空间要  空间名 + :: + 变量名
	//2. 可以 using 引入空间成员
	//3. 可以 using 引入整个空间
	//推荐使用第一种

	bite::a = 10;
	bite::fun1(bite::a);

	bite::bite_69::a = 20;
	bite::fun1(bite::bite_69::a);
}


void test() {
	int a = 0;
	int b = 0;

	//c语言的输入输出
	scanf("%d", &a);
	printf("%d\n", a);
	
	//c++的输入输出
	//包含<iostream>头文件 + std命名空间
	//不需要指定输入输出的变量格式, 支持连续的输入输出
	std::cin >> b;
	std::cout << b << '\n';
}


void test2() {
	//这里必须要加 const
	const char* p = "abcd";
	
}


//缺省参数 : 给参数定义一个默认值, 使用时没有传参的话, 就使用默认值
//全缺省
void func2(int a = 1, int b = 2, int c = 3) {
	std::cout << a << b << c << std::endl;
}

//半缺省 : 必须从右向左依次赋值, 中间不能间隔
void func3(int a, int b = 2, int c = 3) {
	std::cout << a << b << c << std::endl;
}
//下面是错误案例
//void func3(int a = 1, int b, int c = 3);
//void func3(int a, int b = 2, int c);



//函数重载: 函数名相同, 参数不同, 且在同一个作用域	c++支持
//参数不同 : 类型, 个数, 顺序不同
//如果只是返回值类型不同, 不能构成函数重载

int Add(int a, int b) {
	return a + b;
}

int Add(int a, int b, int c) {
	return a + b + c;
}

float Add(float a, float b) {
	return a + b;
}

int Add(int a, char b) {
	return a + b;
}

int Add(char a, int b) {
	return a + b;
}

//extern "C" 可以让编译器按照c语言的编译规则进行编译
//extern "C" { }  表示对 { } 内的代码都进行C规则编译
extern "C" int sub(int a, int b) {

}



//引用
void test5(){
	//类型 + & + 引用名称
	int a = 10;
	//a的别名
	//引用相当于起别名, 下面ra, ra1 和上面的 a 指向同一块内存空间, 即一个变都变
	int& ra = a;
	int& ra1 = a;


	int b = -1;
	ra = b;//这里只是赋值,引用定义之后不会再去改变实体的指向 (不是表示ra是b的别名, ra改变并不会改变b的值)
	        
	//引用在定义时必须初始化
	//int& ra3;
}





int main() {
	//test();
	//test0();

	//传参的时候也不能中间间隔, 要从左向右依次赋值
	func2(10, 20, 30);
	func2(10); 
	func2();

	func3(2);
	func3(2, 3);

	return 0;
}