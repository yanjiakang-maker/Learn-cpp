#include<iostream>

using namespace std;

int a; //������һ������
int b = 1; //��ʼ��


class Date {
public:
	Date(int y = 2000, int m = 1, int d = 1)
		//��ʼ���б�   �﷨ -->   : ����1(ֵ) , ����2(ֵ) .......
	{
		//��ֵ
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


	//����Print��������Date�����Ԫ����
	friend void Print(const Date& d);

	friend ostream& operator<<(ostream& cout, const Date& d);

private:
	//ֻ�ǳ�Ա���������ĵط�
	int _year;
	int _month;
	int _day;
	
public:
	//��̬��Ա���� :  ��������, �������ж��ٸ�Date����
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

	//��̬��Ա�����ķ��ʷ�ʽ
	//1. ͨ���������  (���г�Ա)
	cout << d.num << endl; 
	//2. ͨ����������  (����)
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

	//�ȼ�������
	operator<<(cout, d2);

	delete pd;
}


//void print(int a, int b, int c = 1) {
//	cout << a << " " << b << " " << c << endl;
//}



void test3() {
	int a = 1; // ջ

	int* arr = new int[10000000]; // ��

	int* pa = new int;  // ��

	static int b = 0;  // ���ݶ�

	const char* p = "12345";  // �����

	delete[] arr;

	Date d;
	d.printnum();
	Date* pd = &d;
	pd->printnum();   //  ->  �ȼ���   * .   (*pd).printnum



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