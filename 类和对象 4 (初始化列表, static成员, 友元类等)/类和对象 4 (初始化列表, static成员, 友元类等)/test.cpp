#include<iostream>

using namespace std;


class Time {
public:
	Time(int a = 1) {
		_a = a;
	}

private:
	int _a;
};


class Date {
public:
	Date(int y = 2000, int m = 1, int d = 1)
		//初始化列表:    : 成员(初始化值/表达式) , 成员2(初始化值/表达式) ......
		//每一个成员变量只能在初始化列表中出现一次
		//对象的成员变量定义的地方: 初始化列表
		//如果有引用成员, const成员, 没有默认构造的自定义成员, 必须在初始化列表中进行初始化, 不然编译不通过
		//其他成员可以不进行显式初始化
		//对于自定义成员, 最好在初始化列表中初始化, 即使不在初始化列表中显式初始化, 
		//       编译器也会在初始化列表中自动调用自定义成员的默认构造完成初始化
		//成员变量在初始化列表中的初始化顺序 :  和声明顺序一致, 与其在列表中的顺序无关
		//注意: 最好初始化列表和声明顺序保持一致
		: _year(y)
		, _month(m)
		, _day(d)
		, _a(y)
		, _b(y)
		, _time(y)
	{
		//这里是赋值
		_year = y;
		_month = m;
		_day = d;
		//这里是给_time重新赋值, 不是初始化
		_time = 10;
	}

private:
	//这里是成员变量声明的地方, 定义的地方在初始化列表
	int _year;
	int _month;
	int _day;

	int& _a; // 引用在定义时必须初始化
	const int _b; // const变量在定义时必须初始化
	Time _time;
};


void test() {
	Date d(2020, 5, 20);
}


class A {
public:
	//explicit: 禁掉单参构造函数的隐式类型转换
	/*explicit*/ A(int a)
		:_a(a)
	{
		cout << "A(int)" << endl;
	}

	A(const A& a)
		:_a(a._a)
	{
		cout << "A(const A&)" << endl;
	}

	A& operator=(const A& a) {
		if (this != &a) {
			_a = a._a;
		}
		cout << "A& operator=(const A& a)" << endl;
		return *this;
	}

private:
	int _a;
};

void test2() {
	A a(1);   // 创建对象
	A a2 = 2; // 创建对象 : 单参构造函数的隐式类型转换 --> 
			  //			调用构造函数创建一个匿名对象 + 拷贝构造(通过匿名对象拷贝构造a2对象)
			  // 编译器优化(默认行为): 2作为实参传入构造函数直接构造a2

	cout << "a2 = 10" << endl;
	a2 = 10; //10作为参数传入构造函数, 创建匿名对象, 调用赋值, 使用匿名对象给a2赋值
}


//class B {
//public:
//	B() {
//		cout << "B()" << endl;
//	}
//
//	B(const B& b) {
//		cout << "B(const B& b)" << endl;
//	}
//};
//
//B fun(B b) {
//	B a = b;
//	return a;
//}
//
//void test5() {
//	//B b;
//	fun(B());
//	//cout << cnt << endl;
//}


class date {
public:
	date(int y = 2020, int m = 2, int d = 22)
		: _year(y)
		, _month(m)
		, _day(d)
	{
		_cnt++;
	}

	//静态成员函数
	//不能访问非静态成员, 没有this指针 (访问静态成员时, 对象可能不存在, 那么和对象强相关的东西都不存在)
	//也调不动非静态成员函数, 因为没有this指针, 参数不够
	static int getCount() {
		return _cnt;
	}


private:
	//C++11的初始化方式: 相当于给一个缺省值
	//最后一个选择 (备胎)
	int _year = 1;
	int _month = 1;
	int _day = 1;
	
	//静态成员变量, 所有对象共享此成员变量(相当于类域中的全局变量), 可以看成类成员
	//静态成员变量不能在声明的时候给默认
	//静态成员不在对象模型中, 一般存放在数据段, 不能在初始化列表中初始化
public:
	static int _cnt;
};
//静态成员必须在类外初始化
int date::_cnt = 0;


void test3() {
	date d;
	date d2(2020, 5, 20);
}


void test4() {
	date d;
	date* p = &d;

	date d2;


	//静态成员变量访问方式:
	//1. 对象访问
	cout << &d._cnt << endl;
	cout << &d2._cnt << endl;
	cout << p->_cnt << endl;

	//2. 类名 + 作用域限定符
	//访问静态成员变量不需要考虑对象存不存在
	cout << &date::_cnt << endl;
	cout << date::_cnt << endl;

	//静态成员函数也有两种访问方式, 同上
}




class time {
	//DATE是time的友元类 : DATE类中的所有成员函数是time类的友元函数  (友元关系是单向的, 也不能传递)
	friend class DATE;
private:
	int _h = 24;
	int _m = 0;
	int _s = 0;
};


class DATE {
public:
	//声明友元函数
	//友元函数可以访问类的所有成员 
	//仍然属于一个普通函数, 不是成员函数,   在类内声明, 类外定义 (可以在类内任何地方声明)
	//在声明的时候加 friend , 定义的时候不用加
	//因为友元是一种突破封装的语法, 所以不宜多用
	friend ostream& operator<< (ostream& _cout, const DATE& d);
	friend istream& operator>> (istream& _cin, DATE& d);


	DATE(int y, int m, int d) {
		_y = y;
		_m = m;
		_d = d;
	}

	void printDATE() {
		cout << _y << "-" << _m << "-" << _d << endl;
		cout << _t._h << "-" << _t._m << "-" << _t._s << endl;
	}

	//ostream& operator<< (ostream& _cout) {
	//	_cout << _y << "-" << _m << "-" << _d << endl;
	//	return _cout;
	//}

private:
	int _y;
	int _m;
	int _d;
	time _t;
};

ostream& operator<< (ostream& _cout, const DATE& d) {
	_cout << d._y << "-" << d._m << "-" << d._d << endl;
	return _cout;
}

istream& operator>> (istream& _cin, DATE& d) {
	_cin >> d._y >> d._m >> d._d;
	return _cin;
}



void test6() {
	DATE d(2020, 10, 22);
	d.printDATE();

	cin >> d;
	cout << d << endl;
	//d << cout << endl;
	//d.operator<<(cout);
}



class a {
public:
	a(int a = 1)
		:_a(a)
	{}

	//内部类
	//天然是外部类的友元类, 可以访问外部类的所有成员
	//注意: 普通友元函数, static成员还是需要通过对象或者类名访问
	class b {
	public:
		void printa(const a& a) {
			//	  普通成员: 通过对象访问
			cout << a._a << endl;

			//	  static成员:  直接访问
			cout << _s << endl;

		}

	private:
		int _b;
	};

	//外部类访问不到内部类的私有成员, 内部类是独立于外部类存在的
private:
	int _a;
	static int _s;
};
int a::_s = 100;

void test7() {
	cout << sizeof(a::b) << endl; //4
	cout << sizeof(a) << endl;   //静态成员变量不在对象模型中存放, 放在静态数据区
}

int main() {
	//test();
	//test2();
	//test3();
	//test4();
	//test5();
	//test6();
	test7();

	return 0;
}



//class AA {
//public:
//	AA(int a)
//		:_a1(a)
//		,_a2(_a1)
//	{}
//
//	void print() {
//		cout << _a1 << " " << _a2 << endl;
//	}
//
//private:
//	int _a2;
//	int _a1;
//};
//
//int main() {
//	AA aa(1);
//	aa.print();
//}