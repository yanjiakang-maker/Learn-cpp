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


//ȫȱʡ
//��ȱʡ
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

//����������������ɺ�������, �����溯��ֻ�з���ֵ��ͬ, �������
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
	//���治�ǿյ�, ��6����Ա����
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

	//�޲ι���
	Date() {
		cout << "Date()" << endl;
	}

	//�������Ĺ��캯��
	Date(int y, int m, int d) {
		_year = y;
		_month = m;
		_day = d;
		cout << "Date()" << endl;
	}


	//��������
	Date(Date& d) {
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}


	//��������
	~Date() {
		cout << "~Date()" << endl;
	}


	void Display() {
		cout << _year << " " << _month << " " << _day << endl;
		//cout << this->_year << " " << this->_month << " " << this->_day << endl;
	}
	

	// ==��������غ���
	//�ײ�ӿ�:  bool operator==(Date* const this, const Date& d)
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

	//����
	Date d3(2000, 1, 1);
	//��ֵ
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
	int a = 0; //��ʼ��, ���Ǹ�ֵ

	a = 10; //��ֵ

}


int main() {
	//test();
	//test2();
	//test3();
	test4();

	return 0;
}