#include<iostream>

using namespace std;


//����ȱʡ
//1. ȫȱʡ
//void print(int a = 0, int b = 0, int c = 0) {
//	cout << a << " " << b << " " << c << endl;
//}

//��ȱʡ :  ��������������ֵ
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

//����������������ɺ�������, �����溯��ֻ�з���ֵ��ͬ, �������
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
	////���� : ���� + & + ��������
	////�����ڶ���ʱ����Ҫ��ʼ��
	//int a = 10;
	////a�ı���
	//int& ra = a;
	//int& ra2 = a;
	//ra2 = 30;
	//ra = 100;
	//a = 1000;

	//cout << &a << endl;
	//cout << &ra << endl;
	//cout << &ra2 << endl;

	//int b = -1;
	////���ö���֮��, ������ȥ����ʵ���ָ��
	//// �����Ǹ�ֵ����, ��������ra��Ϊb�ı���
	//ra = b;
	//ra = -100;


	//auto a = 2;
	//auto f = 3.5;
	//auto c = 'a';
	//auto d = 'a' + 'b';

	//cout << typeid(a).name() << endl; // �������ܴ�ӡ��a������
	//cout << typeid(f).name() << endl;
	//cout << typeid(c).name() << endl;
	//cout << typeid(d).name() << endl;

	int array[] = { 1, 2, 3, 4, 5, 6 };
	int len = sizeof(array) / sizeof(array[0]);

	for (int i = 0; i < len; i++)
		cout << array[i] << " ";
	cout << endl;

	//��Χfor : ʹ�ó���: ���ݷ�Χȷ�� 
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

	//Ĭ�Ϲ��캯��
	Date(int y = 0, int m = 0, int d = 0)
		:_year(y) //��ʼ��
		,_month(m)
		,_day(d)
	{
		//��ֵ
		_year = y;
		_month = m;
		_day = d;

		//cout << "Date()" << endl;
		num++;
	}


	//�������� :  һ�����캯��, ���������ʱ�����, ��һ���Ѿ����ڵĶ���������һ���µĶ���
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

	//��ֵ��������غ���
	Date& operator=(const Date& d) {
		if (this != &d) {
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}

		return *this;
	}


	//��̬��Ա����
	static int getNum() {
		return num;
	}

	friend ostream& operator<<(ostream& cout, const Date& d);


private:
	//ֻ�Ǳ���������
	int _year;
	int _month;
	int _day;

public:
	static int num; //��¼�����ж��ٸ�Date����
};
//��̬��Ա������������г�ʼ��
int Date::num = 0;

//�����������غ���
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
	//(*pd).print(); //�ȼ�������

	Date d(2020, 12, 22);
	d.print();

	Date d2;  // �������� 
	d2.print();

	//���ÿ�������
	Date d3(d);

	d + d2;
	d.operator+(d2); //�ײ�д��
}


void test4() {
	Date d(2020, 5, 20);
	Date d2(2019, 2, 23);

	d2 = d;  //���ø�ֵ��������غ���
	d2.operator=(d); //������ȼ�
	//cout << d2 << endl;
	d2.print();

	Date d3(2000, 9, 28);
	//������ֵ: ��������ֵ
	d = d2 = d3;
	d.operator=(d2.operator=(d3));

	//���ÿ�������, ��Ϊd4������, ����Ҫ���ù��캯����������
	Date d4 = d3;

	//=����: ������󶼴���,���ø�ֵ���������, �����߲�����, ���ÿ�������
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


//����ģ��
template<class T>
T Add(T& a, T& b) {
	return a + b;
}


void test6() {
	int a = 1, b = 2;
	double c = 1.0, d = 2.0;
	char e = 'e', f = 'f';

	//��ʽʵ����, �������Զ��Ƶ�
	Add(a, b);
	Add(c, d);
	Add(e, f);

	//ǿ������ת�� --> ���Ƽ�
	Add(a, (int)d);

	//��ʽʵ����: ����<ʵ��������>(�����б�) --> �Ƽ�
	//Add<int>(a, d);
}



////����
//class Person {
//public:
//	void print() {
//		cout << "name:" << _name << endl;
//		cout << "age:" << _age << endl;
//	}
//
//protected:
//	string _name = "monster"; // ����
//	int _age = 18; // ����
//
//private:
//	int _id = 0; // ����������
//};
//
////ѧ���� : ���м̳�Person
//class Student : public Person {
//public:
//	void setName() {
//		//����ı�����Ա������ɼ�, �����ⲻ�ɼ�
//		_name = "123456";
//	}
//
////protected:
//	int _stuid = 2018; // ѧ��   
//};
//
//
//void test7() {
//	Person p;
//	Student s;
//	s.setName();
//
//	//"��Ƭ"���� :  ���� --> ����   
//	//(����ת��)  ���Ķ����Ƕ��, ��һ������
//	//����������ำֵ, �����������ڸ���������й�ȥ
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
	string _name = "monster"; // ����
	int _age = 18; // ����

	int _id = 0; // ����������
};


//ѧ���� : ���м̳�Person
class Student : public Person {
public:
	void setID() {
		//���������е�id, 
		//ͬ������ :  �����м̳е�ͬ��id������
		_id = 100;

		//ͨ�����������������ʸ����е�ͬ������
		Person::_id = 200;
	}

	/*
		ͬ������ : ����Ҳ��ͬ������, ֻҪ��������ͬ�ͻ�����, ���ܲ�����û��
		���Ǻ�������, ��Ϊ�������ص�ǰ������ͬһ��������
		(ͬ������ͨ��������������ʸ����ͬ������)
		����һ�㲻Ҫдͬ���ĳ�Ա, ���Լ��ڿӲ�����
	*/
	void func(int a) {
		cout << "Student::func()" << endl;
	}

	//protected:
	int _stuid = 2018; // ѧ��   
	int _id = 5; //����������
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


//���μ̳�
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