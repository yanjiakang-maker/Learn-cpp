#include<iostream>

using namespace std;

int a; //声明了一个变量
int b = 1; //初始化


class Date {
public:
	Date(int y = 2000, int m = 1, int d = 1)
		//初始化列表   语法 -->   : 变量1(值) , 变量2(值) .......
	{
		//赋值
		_year = y;
		_month = m;
		_day = d;

		num++;
	}

	//Date() {

	//}


	static void printnum() {
		cout << num << endl;
		
	}

	void fun() {

	}


	//声明Print函数是我Date类的友元函数
	friend void Print(const Date& d);

	friend ostream& operator<<(ostream& cout, const Date& d);

private:
	//只是成员变量声明的地方
	int _year;
	int _month;
	int _day;
	
public:
	//静态成员变量 :  用来计数, 我现在有多少个Date对象
	static int num; 
};
int Date::num = 0;

ostream& operator<<(ostream& cout, const Date& d) {
	cout << d._year << " " << d._month << " " << d._day << endl;
	return cout;
}


void Print(const Date& d) {
	cout << d._year << " " << d._month << " " << d._day << endl;
}



void test() {
	Date d(2020, 12, 16);
	d.printnum(); 

	Date d2;
	d2.printnum();

	Date d3;
	d3.printnum();

	//静态成员变量的访问方式
	//1. 通过对象访问  (公有成员)
	cout << d.num << endl; 
	//2. 通过类名访问  (公有)
	cout << Date::num << endl;

	cout << &d.num << endl;
	cout << &d2.num << endl;
	cout << &d3.num << endl;

}

void test2() {
	Date d(2020, 12, 16);
	Date* pd = new Date;

	Date d2(2020, 12, 17);

	cout << d << d2;

	//等价于上面
	operator<<(cout, d2);

	delete pd;
}


//void print(int a, int b, int c = 1) {
//	cout << a << " " << b << " " << c << endl;
//}



void test3() {
	int a = 1; // 栈

	int* arr = new int[10000000]; // 堆

	int* pa = new int;  // 堆

	static int b = 0;  // 数据段

	const char* p = "12345";  // 代码段

	delete[] arr;

	Date d;
	d.printnum();
	Date* pd = &d;
	pd->printnum();   //  ->  等价于   * .   (*pd).printnum



}


template<class T>
T Add(T a, T b) {
	return a + b;
}

int Add(int a, int b) {
	return a + b;
}


void test4() {
	char arr[10];
	cin >> arr;
	cout << arr << endl;
}

int main() {
	//test();
	//int i = 5;
	//print(++i, i++);  //  7 5 1

	//test2();

	//test3();
	test4();

	return 0;
}