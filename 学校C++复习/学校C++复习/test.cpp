#include<iostream>
#include<string>


using namespace std;

//void Swap(int a, int b) {
//	int tmp = a;
//	a = b;
//	b = tmp;
//}


void Swap(int& a, int& b) {
	int tmp = a;
	a = b;
	b = tmp;
}


//全缺省
//半缺省
//void print(int a, int b, int c) {
//	cout << a << " " << b << " " << c << endl;
//}


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

//下面这个函数不构成函数重载, 和上面函数只有返回值不同, 编译错误
//void Add(int a, char b) {
//	return a + b;
//}

int a = 0;  

void test() {
	//int a[10];
	//auto& ra = a;
	//cout << typeid(a).name() << endl;
	cout << ++a << endl;
	
	if (a > 0) {
		int a = -1;
		cout << a << endl;
	}
	cout << a << endl;
}




class A {
	//里面不是空的, 有6个成员函数
public:
	A() {
		cout << "A()" << endl;
	}

	~A() {
		cout << "~A()" << endl;
	}
};


class Date {
public:
	//Date(int y = 0, int m = 0, int d = 0) {
	//	_year = y;
	//	_month = m;
	//	_day = d;
	//	cout << "Date(int, int, int)" << endl;
	//}

	//无参构造
	Date() {
		cout << "Date()" << endl;
	}

	//带参数的构造函数
	Date(int y, int m, int d) {
		_year = y;
		_month = m;
		_day = d;
		cout << "Date()" << endl;
	}


	//拷贝构造
	Date(Date& d) {
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}


	//析构函数
	~Date() {
		cout << "~Date()" << endl;
	}


	void Display() {
		cout << _year << " " << _month << " " << _day << endl;
		//cout << this->_year << " " << this->_month << " " << this->_day << endl;
	}
	

	// ==运算符重载函数
	//底层接口:  bool operator==(Date* const this, const Date& d)
	bool operator==(const Date& d) const {
		return _year == d._year
			&& _month == d._month
			&& _day == d._day;
	}

private:
	int _year = 2020;
	int _month;
	int _day;
};



void test2() {
	Date d(2020, 5, 20);
	//d.Display();
	Date d2(d);


	int ret = (d == d2);  
	d.operator==(d2);

	//构造
	Date d3(2000, 1, 1);
	//赋值
	d = d3;
	d.Display();

}


void test3() {
	int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

	int len = sizeof(arr) / sizeof(arr[0]);

	for (int i = 0; i < len; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;

	for (int e : arr) {
		cout << e << " ";
	}
	cout << endl;
}

void test4() {
	int a = 0; //初始化, 不是赋值

	a = 10; //赋值

}


int main() {
	//test();
	//test2();
	//test3();
	test4();

	return 0;
}