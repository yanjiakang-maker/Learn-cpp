#include<iostream>

using namespace std;



void test() {
	int num = 4;

	//malloc: 只申请空间
	int* p1 = (int*)malloc(sizeof(int) * num);

	//calloc: 申请空间 并且初始化为0
	//calloc(数据个数, 数据大小)
	int* p2 = (int*)calloc(num, sizeof(int));

	//realloc: 调整空间, 不会初始化, 但会拷贝原有数据
	//realloc(空间首地址, 大小)
	//调整空间时会把p1释放, 开辟新的空间, 并且会把p1内容拷贝过来
	int* p3 = (int*)realloc(p1, sizeof(int) * 100);


	//realloc(nullptr, 大小)  等价于malloc
	char* p4 = (char*)realloc(nullptr, sizeof(char));


	free(p2);
	free(p3);
}


void test2() {
	//realloc的3种情况

	//1. 
	int* p = (int*)malloc(sizeof(int));
	*p = 10;

	int* p2 = (int*)realloc(p, sizeof(int) * 100);

	//2. 
	char* pa = (char*)malloc(sizeof(char));
	*pa = 'a';
	char* pc = (char*)realloc(pa, sizeof(char) * 2);

	//3.
	char* pd = (char*)realloc(pc, sizeof(char));

	free(p);
	free(p2);
	free(pa);
	free(pc);
	free(pd);


}


class Date {
public:
	Date(int y = 1, int m = 1, int d = 1)
		:_year(y)
		,_month(m)
		,_day(d)
	{
		cout << "Date(int, int, int)" << endl;
	}


	void* operator new(size_t size) {
		cout << "operator new" << endl;
		void* ptr = malloc(size);
		return ptr;
	}


	~Date() {
		cout << "~Date()" << endl;
	}

private:
	int _year = 2020;
	int _month = 5;
	int _day = 20;
};


void test3() {
	//申请一个变量
	int* pa = (int*)malloc(sizeof(int));
	int* pa2 = new int;

	//申请连续空间
	int* pb = (int*)malloc(sizeof(int) * 10);
	int* pb2 = new int[10];

	//申请变量, 并且初始化为20
	int* d = new int(20);

	//释放一个元素
	free(pa);
	delete pa2;
	delete d;
	
	//释放连续空间
	free(pb);
	delete[] pb2;
}

void test4() {

	Date* pd = (Date*)malloc(sizeof(Date));
	
	//自动调用默认构造完成初始化
	Date* pd1 = new Date;

	Date* pd2 = new Date(2020, 10, 24);

	//在堆上创建自定义类型数组, new只能调用默认构造 (没法自己给初始值, 也就是[]和()不能同时出现)
	Date* pd3 = new Date[10];


	//delete会调用析构函数, delete[]会调用多次析构
	free(pd);
	delete pd1;
	delete pd2;
	delete[] pd3;


	//new:  开空间 --> 构造
	//delete: 析构 --> 释放空间 
}


void test5() {
	//new --> operator new --> malloc --> 构造函数
	//operator new 不是运算符重载函数, 只是一个全局函数
	//实际上是 malloc + 异常 的封装
	Date* pd = new Date;
}




class A {
public:
	A() {
		cout << "A()" << endl;
	}

	A(int a) {
		cout << "A(int)" << endl;
	}

	~A() {
		cout << "~A()" << endl;
	}
};


void test6() {
	//new的定位表达式

	A* pa = (A*)malloc(sizeof(A));
	//显示调用构造函数
	new (pa)A();

	A* pa2 = (A*)malloc(sizeof(A));
	new (pa2)A(10);

	
	//显示调用析构, 清理对象中的资源
	pa->~A();
	pa2->~A();


	//释放对象空间
	free(pa);
	free(pa2);
}


void test7() {
	char* p = new char[100];
	delete p;
}


int main() {
	//test();
	test2();
	//test4();
	//test5();
	//test6();
	//test7();

	return 0;
}


int globalVar = 1;
static int staticGlobalVar = 1;

void Test() {
	static int staticVar = 1;
	int localVar = 1;
	int num1[10] = { 1, 2, 3, 4 };

	char char2[] = "abcd";
	const char* pChar3 = "abcd";

	int* ptr1 = (int*)malloc(sizeof(int) * 4);
	int* ptr2 = (int*)calloc(4, sizeof(int));
	int* ptr3 = (int*)realloc(ptr2, sizeof(int) * 4);

	free(ptr1);
	free(ptr3);
}