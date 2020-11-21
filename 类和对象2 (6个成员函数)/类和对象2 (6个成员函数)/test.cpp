#include<iostream>

using namespace std;

class A {
	//里面不是空的, 有6个成员函数

public:
	A() {
		//cout << "A()" << endl;
	}

	~A() {
		//cout << "~A()" << endl;
	}
};


class Date {
public:
	/*
		构造函数:  函数名和类名相同, 无返回值, 可以重载, 编译器在创建时自动调用
		(只要显式定义了构造函数, 就不会自动生成默认构造, 不管你定义的是不是默认构造)
		所以我们一般直接显式给一个全缺省的构造函数

		默认构造:  只能存在一个
			1. 编译器默认生成 
			2. 显示定义的无参构造
			3. 全缺省构造函数
	*/

	//Date() {

	//} 

	Date(int y = 2020, int m = 5, int d = 20) {
		_year = y;
		_month = m;
		_day = d;
		//cout << "Date()" << endl;
	}


	void SetDate(int y, int m, int d) {
		_year = y;
		_month = m;
		_day = d;
	}


	/*
		拷贝构造: 构造函数的一种重载形式, 也是在创建对象时自动调用
		调用场景: 用一个已经存在的对象去创建一个新的对象, 创建的新对象和当前对象内容相同
		类型必须是引用, 否则会引发无穷递归, 编译器不支持传值类型
		编译器默认生成的拷贝构造为字节拷贝, 浅拷贝(只拷贝对象模型中的内容, 不拷贝资源)
		如果有资源, 必须显式定义拷贝构造, 完成深拷贝
	*/
	Date(const Date& d) {
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}


	bool isEqual(const Date& d) {
		return _year == d._year
			&& _month == d._month
			&& _day == d._day;
	}

	/*
		运算符重载函数: 增强代码的可读性
		函数名特殊, 定义和使用方式和普通函数一样
		返回值 operator + 需要重载的运算符 (参数列表) { 函数体 }
		运算符重载函数如果是成员函数, 则参数的个数比运算符需要的个数少一个
		编译器会传入this指针作为第一个参数
		this指针始终占用运算符操作数的第一个位置
	*/
	//底层接口:  bool operator==(Date* const this, const Date& d)
	bool operator==(const Date& d) { 
		return _year == d._year
			&& _month == d._month
			&& _day == d._day;
	}


	/*
		赋值运算符重载函数  d = d2
		修改已经存在的对象的内容, 不是去创建新的对象
		如果不写, 编译器也会默认生成
		但是默认生成的也是字节拷贝(浅拷贝), 
		如果当前类中有资源, 则必须显式定义赋值运算符重载函数, 完成深拷贝
	*/
	Date& operator=(const Date& d2) {
		//判断是否给自己赋值
		if (this != &d2) {
			_year = d2._year;
			_month = d2._month;
			_day = d2._day;
			cout << "operator=(const Date& d2)" << endl;
		}
		//返回当前调用此函数的对象本身 
		return *this;
	}



	//析构函数: 清理资源, 不是销毁对象, 在对象生命周期结束时, 编译器自动调用
	//如果没有资源需要清理, 可以不用写析构函数, 直接使用编译器默认生成的析构即可
	~Date() {
		//有自定义类型的话, 自动调用自定义类型的析构函数, 完成自定义成员的资源清理
		//cout << "~Date()" << endl;
	}


	//Display(Date* const this)
	void Display() {
		cout << _year << " " << _month << " " << _day << endl;
		//非const成员函数可以调用const成员函数, 读写权限没被放大
	}

	//const成员函数中的const修饰的是第一个参数, 即this指针
	//const成员函数内部不能修改成员变量的值
	//Display(const Date* const this)
	void Display() const {
		cout << _year << " " << _month << " " << _day << endl;
		//const成员函数不能调用非const成员函数, 读写权限不能被放大
	}


	//取地址运算符重载函数: operator&
	//一般不需要显式定义, 直接用默认即可
	Date* operator&() {
		return this;
	}

	const Date* operator&() const {
		return this;
	}


//private:
	int _year;
	int _month;
	int _day;
	//如果类中存在自定义成员, 则构造函数会自动调用自定义成员的默认构造,完成自定义成员的初始化
	//如果自定义成员没有默认构造函数, 会产生编译错误
	A _a;
};

//普通的运算符重载函数, 参数的个数和运算符需要的个数一致
//不推荐写普通的运算符重载函数, 因为这么写要把类中的私有成员打开, 严重影响安全性
bool operator==(const Date& d, const Date& d1) {
	return d1._year == d._year
		&& d1._month == d._month
		&& d1._day == d._day;
}
//输出运算符重载函数
ostream& operator<<(ostream& _cout, const Date& date) {
	_cout << date._year << " " << date._month << " " << date._day << endl;
	return _cout;
}


void test() {
	Date d;
	d.SetDate(2020, 5, 1);
	d.Display();

	Date d2(2020, 5, 20);
	d2.Display();

	Date d3();//这是声明一个函数, 不是调用无参构造
}


void test1() {
	Date d;
	Date copy(d);

	Date copy2(Date(2020, 5, 20));//优化: 直接用构造函数创建copy2  
								//不优化: 调用构造创建匿名对象 + 拷贝构造
}


void test2() {
	const int a = 10;
	int* pa = (int*)&a;
	*pa = 20;
	cout << a << endl;
	cout << *pa << endl;
}


void test3() {
	Date d(2020, 1, 1);
	Date d2(d);

	Date d3(2020, 5, 20);
	cout << d.isEqual(d2) << endl;
	cout << d.isEqual(d3) << endl;

	cout << (d == d2) << endl;  //等价于 d.operator==(d2);
	cout << d.operator==(d2) << endl;
	cout << (d == d3) << endl;  //等价于d.operator==(d3);
	cout << d.operator==(d3) << endl;

	cout << d << endl;
}


void test4() {
	Date d(2020, 5, 20);
	Date d2(2019, 2, 23);
	d2 = d;  //调用赋值运算符重载函数
	d2.operator=(d); //和上面等价
	cout << d2 << endl;

	Date d3(2000, 9, 28);
	//连续赋值: 从右向左赋值
	d = d2 = d3;
	d.operator=(d2.operator=(d3));

	//调用拷贝构造, 因为d4不存在, 所以要调用构造函数创建变量
	Date d4 = d3;

	//=调用: 如果对象都存在,调用赋值运算符重载, 如果左边不存在, 调用拷贝构造

}

void test5() {
	Date d1(2020, 5, 20);
	const Date d2(d1);
	d1.Display(); // 非const对象(可读可写), 调用非const成员函数, 也可以调用const成员函数
				  // 原因: 读写权限没有被放大
	d2.Display(); // const对象(只读), 调用const成员函数, 不能调用非const成员函数
				  // 原因: 读写权限不能被放大
}


int main() {
	//test();
	//test1();
	//test3();
	test4();

	return 0;
}