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
		//��ʼ���б�:    : ��Ա(��ʼ��ֵ/���ʽ) , ��Ա2(��ʼ��ֵ/���ʽ) ......
		//ÿһ����Ա����ֻ���ڳ�ʼ���б��г���һ��
		//����ĳ�Ա��������ĵط�: ��ʼ���б�
		//��������ó�Ա, const��Ա, û��Ĭ�Ϲ�����Զ����Ա, �����ڳ�ʼ���б��н��г�ʼ��, ��Ȼ���벻ͨ��
		//������Ա���Բ�������ʽ��ʼ��
		//�����Զ����Ա, ����ڳ�ʼ���б��г�ʼ��, ��ʹ���ڳ�ʼ���б�����ʽ��ʼ��, 
		//       ������Ҳ���ڳ�ʼ���б����Զ������Զ����Ա��Ĭ�Ϲ�����ɳ�ʼ��
		//��Ա�����ڳ�ʼ���б��еĳ�ʼ��˳�� :  ������˳��һ��, �������б��е�˳���޹�
		//ע��: ��ó�ʼ���б������˳�򱣳�һ��
		: _year(y)
		, _month(m)
		, _day(d)
		, _a(y)
		, _b(y)
		, _time(y)
	{
		//�����Ǹ�ֵ
		_year = y;
		_month = m;
		_day = d;
		//�����Ǹ�_time���¸�ֵ, ���ǳ�ʼ��
		_time = 10;
	}

private:
	//�����ǳ�Ա���������ĵط�, ����ĵط��ڳ�ʼ���б�
	int _year;
	int _month;
	int _day;

	int& _a; // �����ڶ���ʱ�����ʼ��
	const int _b; // const�����ڶ���ʱ�����ʼ��
	Time _time;
};


void test() {
	Date d(2020, 5, 20);
}


class A {
public:
	//explicit: �������ι��캯������ʽ����ת��
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
	A a(1);   // ��������
	A a2 = 2; // �������� : ���ι��캯������ʽ����ת�� --> 
			  //			���ù��캯������һ���������� + ��������(ͨ���������󿽱�����a2����)
			  // �������Ż�(Ĭ����Ϊ): 2��Ϊʵ�δ��빹�캯��ֱ�ӹ���a2

	cout << "a2 = 10" << endl;
	a2 = 10; //10��Ϊ�������빹�캯��, ������������, ���ø�ֵ, ʹ�����������a2��ֵ
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

	//��̬��Ա����
	//���ܷ��ʷǾ�̬��Ա, û��thisָ�� (���ʾ�̬��Աʱ, ������ܲ�����, ��ô�Ͷ���ǿ��صĶ�����������)
	//Ҳ�������Ǿ�̬��Ա����, ��Ϊû��thisָ��, ��������
	static int getCount() {
		return _cnt;
	}


private:
	//C++11�ĳ�ʼ����ʽ: �൱�ڸ�һ��ȱʡֵ
	//���һ��ѡ�� (��̥)
	int _year = 1;
	int _month = 1;
	int _day = 1;
	
	//��̬��Ա����, ���ж�����˳�Ա����(�൱�������е�ȫ�ֱ���), ���Կ������Ա
	//��̬��Ա����������������ʱ���Ĭ��
	//��̬��Ա���ڶ���ģ����, һ���������ݶ�, �����ڳ�ʼ���б��г�ʼ��
public:
	static int _cnt;
};
//��̬��Ա�����������ʼ��
int date::_cnt = 0;


void test3() {
	date d;
	date d2(2020, 5, 20);
}


void test4() {
	date d;
	date* p = &d;

	date d2;


	//��̬��Ա�������ʷ�ʽ:
	//1. �������
	cout << &d._cnt << endl;
	cout << &d2._cnt << endl;
	cout << p->_cnt << endl;

	//2. ���� + �������޶���
	//���ʾ�̬��Ա��������Ҫ���Ƕ���治����
	cout << &date::_cnt << endl;
	cout << date::_cnt << endl;

	//��̬��Ա����Ҳ�����ַ��ʷ�ʽ, ͬ��
}




class time {
	//DATE��time����Ԫ�� : DATE���е����г�Ա������time�����Ԫ����  (��Ԫ��ϵ�ǵ����, Ҳ���ܴ���)
	friend class DATE;
private:
	int _h = 24;
	int _m = 0;
	int _s = 0;
};


class DATE {
public:
	//������Ԫ����
	//��Ԫ�������Է���������г�Ա 
	//��Ȼ����һ����ͨ����, ���ǳ�Ա����,   ����������, ���ⶨ�� (�����������κεط�����)
	//��������ʱ��� friend , �����ʱ���ü�
	//��Ϊ��Ԫ��һ��ͻ�Ʒ�װ���﷨, ���Բ��˶���
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

	//�ڲ���
	//��Ȼ���ⲿ�����Ԫ��, ���Է����ⲿ������г�Ա
	//ע��: ��ͨ��Ԫ����, static��Ա������Ҫͨ�����������������
	class b {
	public:
		void printa(const a& a) {
			//	  ��ͨ��Ա: ͨ���������
			cout << a._a << endl;

			//	  static��Ա:  ֱ�ӷ���
			cout << _s << endl;

		}

	private:
		int _b;
	};

	//�ⲿ����ʲ����ڲ����˽�г�Ա, �ڲ����Ƕ������ⲿ����ڵ�
private:
	int _a;
	static int _s;
};
int a::_s = 100;

void test7() {
	cout << sizeof(a::b) << endl; //4
	cout << sizeof(a) << endl;   //��̬��Ա�������ڶ���ģ���д��, ���ھ�̬������
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