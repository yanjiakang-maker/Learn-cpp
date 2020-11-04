#define _CRT_SECURE_NO_WARNINGS
#pragma pack(8) //�޸�Ĭ�϶�����
#include<iostream>

using namespace std;


//C++��struct: ���Զ������ݺͺ���
//C++������ķ�ʽ:
//   1. struct + ���� + { } + ;  (Ĭ�Ϸ���Ȩ����public)
//   2. class + ���� + {} + ;    (Ĭ�Ϸ���Ȩ����private)
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

//C++�ķ�װ���﷨����: ��, �����޶���
//�����޶��� : public, protected, private
//���÷�Χ: �ӵ�ǰ�޶�������һ���޶���
//ֻ���Ƴ�Ա������ķ���Ȩ��, ���ڲ���������
class Student2 {
//���г�Ա, ������ɼ�
public:
	//��Ա����
	void display() {
	}
	void setId(int id) {
		_id = id;
	}
	void setNumber(int num) {
		_number = num;
	}
//˽�г�Ա, �����ⲻ�ɼ�
private:
	//��Ա����
	int _number;
	int _id;
//������Ա, �����ⲻ�ɼ�
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
//�������������ⶨ��Ҫ��������
void A::fun() {
	cout << "fun()" << endl;
}


//���Ƕ�����಻ռ�ڴ�, �൱�����ͼֽ
//�������������ռ�ռ�
void test2() {
	//���ʵ����: ����һ�������͵ı����Ĺ���
	//����: ����--> �Զ������͵ı���һ���Ϊ����
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

//����ģ����ֻ�����ͨ�ĳ�Ա����, ����ų�Ա����, ��Ա�������ڹ����Ĵ����
//����Ĵ�СΪ1 (��һ���ֽڿ������ɱ���ֽ�, ����������Ǵ��ڵ�)
void test3() {
	cout << sizeof(C) << endl;
	cout << sizeof(D) << endl;
	cout << sizeof(E) << endl;
	cout << sizeof(F) << endl;
}


//��Ĵ�СҲ��ѭ�ڴ����Ĺ���
class G {
	char _c; //1
	double _d; //16
	int _a; //20
	char _c2; //21
	//24

	//Ƕ��
	class H {
		double _d; //8
		char _c;  //9

		int _a;   //16
		char _f;  //17
	};
	H _h;//���ﴴ����Ա�������H�Ĵ�С, ������H, G�Ĵ�С����24
};


struct I {
	char _c; //1
	double _d; //16
	int _a; //20
	char _c2; //21
};


void test4() {
	I i;
	//����ƫ����
	cout << (char*)&i._c2 - (char*)&i << endl;
}


//�����: �͵�ַ���λ, �ߵ�ַ���λ  (�Ķ���, �����ֽ���Ϊ�����)
//С����: �͵�ַ���λ, �ߵ�ַ���λ
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
		void Display(Date* const this) ʼ��ָ��ǰ���ô˺����Ķ���
		thisָ������: ������* const
		thisָ��ֻ�����ڳ�Ա������
		thisָ��ʼ����Ϊ��Ա�����ĵ�һ���β�
		�������Զ�����, ������ʾ����
		this������ĳ�Ա, ֻ��һ�������β�, �������ջ��, һ������Ż�,���ڼĴ�����
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
	//this�ڲ��������õĳ����¿���Ϊ��
	pd1->Display();  //thisָ��Ϊ��, �������쳣
	pd1->fun1(); // thisָ��Ϊ��, ����thisû�н�����, ��������ִ��
	//�ײ�ͱ���� ---> fun1(pd1)
	(*pd1).fun1(); //ͬ��
}

int main() {
	test3();
	//cout << sizeof(G) << endl;
	//test4();
	//test5();
	//test6();
		
	return 0;
}