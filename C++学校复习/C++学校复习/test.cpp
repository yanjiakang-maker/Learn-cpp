#include<iostream>

using namespace std;


//函数缺省
//1. 全缺省
//void print(int a = 0, int b = 0, int c = 0) {
//	cout << a << " " << b << " " << c << endl;
//}

//半缺省 :  从右向左连续赋值
void print(int a, int b = 0, int c = 0) {
	cout << a << " " << b << " " << c << endl;
}



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



void Swap(int* a, int* b) {
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void Swap(int& a, int& b) {
	int tmp;
	tmp = a;
	a = b;
	b = tmp;
}


void test() {
	//int a = 1;
	//int* pa = &a;

	//const char* str = "12345";

	//cout << pa << endl;
	//cout << str << endl;


	//print(1, 2, 3);

	int a = 5, b = 10;
	Swap(a, b);
	cout << a << " " << b << endl;


}

void test2() {
	////引用 : 类型 + & + 引用名称
	////引用在定义时必须要初始化
	//int a = 10;
	////a的别名
	//int& ra = a;
	//int& ra2 = a;
	//ra2 = 30;
	//ra = 100;
	//a = 1000;

	//cout << &a << endl;
	//cout << &ra << endl;
	//cout << &ra2 << endl;

	//int b = -1;
	////引用定义之后, 不会再去更改实体的指向
	//// 这里是赋值操作, 并不是让ra作为b的别名
	//ra = b;
	//ra = -100;


	//auto a = 2;
	//auto f = 3.5;
	//auto c = 'a';
	//auto d = 'a' + 'b';

	//cout << typeid(a).name() << endl; // 这句代码能打印出a的类型
	//cout << typeid(f).name() << endl;
	//cout << typeid(c).name() << endl;
	//cout << typeid(d).name() << endl;

	int array[] = { 1, 2, 3, 4, 5, 6 };
	int len = sizeof(array) / sizeof(array[0]);

	for (int i = 0; i < len; i++)
		cout << array[i] << " ";
	cout << endl;

	//范围for : 使用场景: 数据范围确定 
	for (auto e : array) {
		cout << e << " ";
		e = 10;
	}
	cout << endl;

	for (auto e : array) {
		cout << e << " ";
	}
	cout << endl;


	cout << typeid(nullptr).name() << endl;

}


class Time {
public:
	Time(int t) {
		cout << "Time()" << endl;
	}
private:
	int _hour;
};


class Date {
public:
	//Date() {

	//}

	//Date(int y, int m, int d) {
	//	_year = y;
	//	_month = m;
	//	_day = d;
	//}

	//默认构造函数
	Date(int y = 0, int m = 0, int d = 0)
		:_year(y) //初始化
		,_month(m)
		,_day(d)
	{
		//赋值
		_year = y;
		_month = m;
		_day = d;

		//cout << "Date()" << endl;
		num++;
	}


	//拷贝构造 :  一个构造函数, 创建对象的时候调用, 拿一个已经存在的对象来创建一个新的对象
	Date(Date& d) {
		_year = d._year;
		_month = d._month;
		_day = d._day;
		num++;
	}


	void setDate(int y, int m, int d) {
		this->_year = y;
		this->_month = m;
		this->_day = d;
	}
	

	void display() {
		cout << _year << " " << _month << " " << _day << endl;
	}

	void print() const {
		cout << _year << " " << _month << " " << _day << endl;
	}


	~Date() {
		//cout << "~Date()" << endl;
	}

	Date& operator+ (Date& d) {
		return *this;
	}

	//赋值运算符重载函数
	Date& operator=(const Date& d) {
		if (this != &d) {
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}

		return *this;
	}


	//静态成员函数
	static int getNum() {
		return num;
	}

	friend ostream& operator<<(ostream& cout, const Date& d);


private:
	//只是变量的声明
	int _year;
	int _month;
	int _day;

public:
	static int num; //记录现在有多少个Date对象
};
//静态成员必须在类外进行初始化
int Date::num = 0;

//输出运算符重载函数
ostream& operator<<(ostream& cout, const Date& d) {
	cout << d._year << " " << d._month << " " << d._day << endl;
	return cout;
}

void test3() {
	//Date d;
	//d.setDate(2020, 12, 22);
	//d.print();

	//Date d2;
	//d2.setDate(2000, 1, 1);
	//d2.print();

	//Date* pd = &d;
	//pd->print();
	//(*pd).print(); //等价于上面

	Date d(2020, 12, 22);
	d.print();

	Date d2;  // 函数声明 
	d2.print();

	//调用拷贝构造
	Date d3(d);

	d + d2;
	d.operator+(d2); //底层写法
}


void test4() {
	Date d(2020, 5, 20);
	Date d2(2019, 2, 23);

	d2 = d;  //调用赋值运算符重载函数
	d2.operator=(d); //和上面等价
	//cout << d2 << endl;
	d2.print();

	Date d3(2000, 9, 28);
	//连续赋值: 从右向左赋值
	d = d2 = d3;
	d.operator=(d2.operator=(d3));

	//调用拷贝构造, 因为d4不存在, 所以要调用构造函数创建变量
	Date d4 = d3;

	//=调用: 如果对象都存在,调用赋值运算符重载, 如果左边不存在, 调用拷贝构造
}


void test5() {
	//const Date d(2020, 12, 22);
	//d.print();

	//Date d2;
	//d2.print();

	Date d(2020, 12, 22);
	Date d2;
	Date d3;
	Date d4;

	cout << d.num << endl;
	cout << Date::num << endl;

	cout << d << endl;
}


//函数模板
template<class T>
T Add(T& a, T& b) {
	return a + b;
}


void test6() {
	int a = 1, b = 2;
	double c = 1.0, d = 2.0;
	char e = 'e', f = 'f';

	//隐式实例化, 编译器自动推导
	Add(a, b);
	Add(c, d);
	Add(e, f);

	//强制类型转换 --> 不推荐
	Add(a, (int)d);

	//显式实例化: 函数<实例化类型>(参数列表) --> 推荐
	//Add<int>(a, d);
}



////基类
//class Person {
//public:
//	void print() {
//		cout << "name:" << _name << endl;
//		cout << "age:" << _age << endl;
//	}
//
//protected:
//	string _name = "monster"; // 姓名
//	int _age = 18; // 年龄
//
//private:
//	int _id = 0; // 父类作用域
//};
//
////学生类 : 公有继承Person
//class Student : public Person {
//public:
//	void setName() {
//		//基类的保护成员在子类可见, 在类外不可见
//		_name = "123456";
//	}
//
////protected:
//	int _stuid = 2018; // 学号   
//};
//
//
//void test7() {
//	Person p;
//	Student s;
//	s.setName();
//
//	//"切片"操作 :  子类 --> 父类   
//	//(向上转型)  给的东西是多的, 切一下正好
//	//用子类给父类赋值, 把子类中属于父类的内容切过去
//	p = s;
//	Person* ptr = &s;
//	Person& ref = s;
//
//	//Student* ptr2 = &p;
//	Student* ptr2 = (Student*)&p;
//	//Student& ref2 = p;
//	Student& ref2 = (Student&)p;
//	ptr2->_stuid = 2;
//	ref2._stuid = 10;
//}

class Person {
public:
	void func() {
		cout << "Person::func()" << endl;
	}

protected:
	string _name = "monster"; // 姓名
	int _age = 18; // 年龄

	int _id = 0; // 父类作用域
};


//学生类 : 公有继承Person
class Student : public Person {
public:
	void setID() {
		//设置子类中的id, 
		//同名隐藏 :  父类中继承的同名id被隐藏
		_id = 100;

		//通过父类作用域来访问父类中的同名变量
		Person::_id = 200;
	}

	/*
		同名隐藏 : 函数也会同名隐藏, 只要函数名相同就会隐藏, 不管参数有没有
		不是函数重载, 因为函数重载的前提是在同一作用域下
		(同样可以通过父类作用域访问父类的同名函数)
		不过一般不要写同名的成员, 给自己挖坑不好哇
	*/
	void func(int a) {
		cout << "Student::func()" << endl;
	}

	//protected:
	int _stuid = 2018; // 学号   
	int _id = 5; //子类作用域
};


void Test() {
	Student s;
	s.func(1);
	s.Person::func();
	s.setID();
}


class A {
public:
	A(int a) {
		cout << "A()" << endl;
	}

private:
	int _a;
};


class B : public A {
public:
	B() 
		:A(5)
	{
		cout << "B()" << endl;
	}

private:
	int _b = 0;
};


//菱形继承
class AA {
public:
	int _aa;
};

class BB : virtual public AA {   //AA::_aa
public:
	int _bb;
};

class CC : virtual public AA {   //AA::_aa
public:
	int _cc;
};

class DD : public BB, public CC {   //BB::_a   CC::_a
public:
	int _dd;
};

void Test2() {
	DD d;
	d.BB::_aa = 1;
	d._bb = 2;
	d.CC::_aa = 5;
	d._cc = 3;
	d._dd = 4;
}

class D {
public:
	virtual void act1() {
		cout << "D::act1()" << endl;
	}

	void act2() {
		act1();
	}
};

class E : public D {
public:
	void act1() {
		cout << "E::act1()" << endl;
	}
};

void Test3() {
	//E e;
	//e.act2();

	const char* str = "12345";
	void* p = (void*)str;
}


int main() {
	//test();
	//test2();
	//test3();
	//test4();
	//test5();
	//test6();
	//test7();
	//Test();
	//Test2();
	Test3();

	return 0;
}