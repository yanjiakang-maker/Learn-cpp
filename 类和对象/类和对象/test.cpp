#define _CRT_SECURE_NO_WARNINGS
#pragma pack(8) //修改默认对齐数
#include<iostream>

using namespace std;


//C++的struct: 可以定义数据和函数
//C++定义类的方式:
//   1. struct + 类名 + { } + ;  (默认访问权限是public)
//   2. class + 类名 + {} + ;    (默认访问权限是private)
struct Student {
	void display() {

	}

	void setId(int id) {
		_id = id;
	}

	void setNumber(int num) {
		_number = num;
	}


	int _number;
	int _id;
	char name[10];
	char gender[10];
	char major[10];
};

//C++的封装的语法体现: 类, 访问限定符
//访问限定符 : public, protected, private
//作用范围: 从当前限定符到下一个限定符
//只限制成员在类外的访问权限, 类内部不受限制
class Student2 {
//公有成员, 在类外可见
public:
	//成员函数
	void display() {
	}
	void setId(int id) {
		_id = id;
	}
	void setNumber(int num) {
		_number = num;
	}
//私有成员, 在类外不可见
private:
	//成员变量
	int _number;
	int _id;
//保护成员, 在类外不可见
protected:
	char name[10];
	char gender[10];
	char major[10];
};


void test() {
	Student st;
	strcpy(st.name, "123");
	st.display();
}


class A {
	void fun();
};
//在类内声明类外定义要加上类域
void A::fun() {
	cout << "fun()" << endl;
}


//我们定义的类不占内存, 相当于设计图纸
//创建的类变量才占空间
void test2() {
	//类的实例化: 创建一个类类型的变量的过程
	//变量: 对象--> 自定义类型的变量一般称为对象
	A a;
}


class C {
	int _c;
};

class D {
	int _c;
	void fun1() {
		int a = 1;
		float b = 2.0;
		char c = 'c';
	}
};

class E {
	void fun1() {
		int a = 1;
		float b = 2.0;
		char c = 'c';
	}
};

class F {
	
};

//对象模型中只存放普通的成员变量, 不存放成员函数, 成员函数放在公共的代码段
//空类的大小为1 (这一个字节可以理解成标记字节, 描述这个类是存在的)
void test3() {
	cout << sizeof(C) << endl;
	cout << sizeof(D) << endl;
	cout << sizeof(E) << endl;
	cout << sizeof(F) << endl;
}


//类的大小也遵循内存对齐的规则
class G {
	char _c; //1
	double _d; //16
	int _a; //20
	char _c2; //21
	//24

	//嵌套
	class H {
		double _d; //8
		char _c;  //9

		int _a;   //16
		char _f;  //17
	};
	H _h;//这里创建成员对象才算H的大小, 否则不算H, G的大小还是24
};


struct I {
	char _c; //1
	double _d; //16
	int _a; //20
	char _c2; //21
};


void test4() {
	I i;
	//计算偏移量
	cout << (char*)&i._c2 - (char*)&i << endl;
}


//大端序: 低地址存高位, 高地址存低位  (阅读序, 网络字节序为大端序)
//小端序: 低地址存低位, 高地址存高位
union U {
	int _a;
	char _c;
};

void test5() {
	int a = 1;
	char* pa = (char*)&a;
	if (*pa == 1)
		cout << "little end" << endl;
	else
		cout << "big end" << endl;

	U u;
	u._a = 1;
	if (u._c == 1)
		cout << "little end" << endl;
	else
		cout << "big end" << endl;
}


class Date {
public:
	/*
		void Display(Date* const this) 始终指向挡前调用此函数的对象
		this指针类型: 类类型* const
		this指针只存在于成员函数中
		this指针始终作为成员函数的第一个形参
		编译器自动传递, 不用显示定义
		this不是类的成员, 只是一个函数形参, 按理存在栈上, 一般会做优化,存在寄存器中
	*/
	void Display() { 
		cout << _year << " " << _month << " " << _day << endl;
		cout << this->_year << " " << this->_month << " " << this->_day << endl;
	}

	void SetDate(int y, int m, int d) {
		_year = y;
		_month = m;
		_day = d;
	}

	void fun1() {
		cout << "Date::fun1()" << endl;
	}

private:
	int _year;
	int _month;
	int _day;
};

void test6() {
	Date d1, d2;
	d1.SetDate(2020, 5, 20);
	d2.SetDate(2020, 10, 1);
	d1.Display();
	d2.Display();

	Date* pd1 = &d1;
	pd1->Display();
	pd1 = nullptr;
	//this在不做解引用的场景下可以为空
	pd1->Display();  //this指针为空, 解引用异常
	pd1->fun1(); // this指针为空, 但是this没有解引用, 程序正常执行
	//底层就变成了 ---> fun1(pd1)
	(*pd1).fun1(); //同上
}

int main() {
	test3();
	//cout << sizeof(G) << endl;
	//test4();
	//test5();
	//test6();
		
	return 0;
}