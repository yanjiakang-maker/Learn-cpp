#include<iostream>

using namespace std;

class A {
	//���治�ǿյ�, ��6����Ա����

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
		���캯��:  ��������������ͬ, �޷���ֵ, ��������, �������ڴ���ʱ�Զ�����
		(ֻҪ��ʽ�����˹��캯��, �Ͳ����Զ�����Ĭ�Ϲ���, �����㶨����ǲ���Ĭ�Ϲ���)
		��������һ��ֱ����ʽ��һ��ȫȱʡ�Ĺ��캯��

		Ĭ�Ϲ���:  ֻ�ܴ���һ��
			1. ������Ĭ������ 
			2. ��ʾ������޲ι���
			3. ȫȱʡ���캯��
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
		��������: ���캯����һ��������ʽ, Ҳ���ڴ�������ʱ�Զ�����
		���ó���: ��һ���Ѿ����ڵĶ���ȥ����һ���µĶ���, �������¶���͵�ǰ����������ͬ
		���ͱ���������, �������������ݹ�, ��������֧�ִ�ֵ����
		������Ĭ�����ɵĿ�������Ϊ�ֽڿ���, ǳ����(ֻ��������ģ���е�����, ��������Դ)
		�������Դ, ������ʽ���忽������, ������
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
		��������غ���: ��ǿ����Ŀɶ���
		����������, �����ʹ�÷�ʽ����ͨ����һ��
		����ֵ operator + ��Ҫ���ص������ (�����б�) { ������ }
		��������غ�������ǳ�Ա����, ������ĸ������������Ҫ�ĸ�����һ��
		�������ᴫ��thisָ����Ϊ��һ������
		thisָ��ʼ��ռ��������������ĵ�һ��λ��
	*/
	//�ײ�ӿ�:  bool operator==(Date* const this, const Date& d)
	bool operator==(const Date& d) { 
		return _year == d._year
			&& _month == d._month
			&& _day == d._day;
	}


	/*
		��ֵ��������غ���  d = d2
		�޸��Ѿ����ڵĶ��������, ����ȥ�����µĶ���
		�����д, ������Ҳ��Ĭ������
		����Ĭ�����ɵ�Ҳ���ֽڿ���(ǳ����), 
		�����ǰ��������Դ, �������ʽ���帳ֵ��������غ���, ������
	*/
	Date& operator=(const Date& d2) {
		//�ж��Ƿ���Լ���ֵ
		if (this != &d2) {
			_year = d2._year;
			_month = d2._month;
			_day = d2._day;
			cout << "operator=(const Date& d2)" << endl;
		}
		//���ص�ǰ���ô˺����Ķ����� 
		return *this;
	}



	//��������: ������Դ, �������ٶ���, �ڶ����������ڽ���ʱ, �������Զ�����
	//���û����Դ��Ҫ����, ���Բ���д��������, ֱ��ʹ�ñ�����Ĭ�����ɵ���������
	~Date() {
		//���Զ������͵Ļ�, �Զ������Զ������͵���������, ����Զ����Ա����Դ����
		//cout << "~Date()" << endl;
	}


	//Display(Date* const this)
	void Display() {
		cout << _year << " " << _month << " " << _day << endl;
		//��const��Ա�������Ե���const��Ա����, ��дȨ��û���Ŵ�
	}

	//const��Ա�����е�const���ε��ǵ�һ������, ��thisָ��
	//const��Ա�����ڲ������޸ĳ�Ա������ֵ
	//Display(const Date* const this)
	void Display() const {
		cout << _year << " " << _month << " " << _day << endl;
		//const��Ա�������ܵ��÷�const��Ա����, ��дȨ�޲��ܱ��Ŵ�
	}


	//ȡ��ַ��������غ���: operator&
	//һ�㲻��Ҫ��ʽ����, ֱ����Ĭ�ϼ���
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
	//������д����Զ����Ա, ���캯�����Զ������Զ����Ա��Ĭ�Ϲ���,����Զ����Ա�ĳ�ʼ��
	//����Զ����Աû��Ĭ�Ϲ��캯��, ������������
	A _a;
};

//��ͨ����������غ���, �����ĸ������������Ҫ�ĸ���һ��
//���Ƽ�д��ͨ����������غ���, ��Ϊ��ôдҪ�����е�˽�г�Ա��, ����Ӱ�찲ȫ��
bool operator==(const Date& d, const Date& d1) {
	return d1._year == d._year
		&& d1._month == d._month
		&& d1._day == d._day;
}
//�����������غ���
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

	Date d3();//��������һ������, ���ǵ����޲ι���
}


void test1() {
	Date d;
	Date copy(d);

	Date copy2(Date(2020, 5, 20));//�Ż�: ֱ���ù��캯������copy2  
								//���Ż�: ���ù��촴���������� + ��������
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

	cout << (d == d2) << endl;  //�ȼ��� d.operator==(d2);
	cout << d.operator==(d2) << endl;
	cout << (d == d3) << endl;  //�ȼ���d.operator==(d3);
	cout << d.operator==(d3) << endl;

	cout << d << endl;
}


void test4() {
	Date d(2020, 5, 20);
	Date d2(2019, 2, 23);
	d2 = d;  //���ø�ֵ��������غ���
	d2.operator=(d); //������ȼ�
	cout << d2 << endl;

	Date d3(2000, 9, 28);
	//������ֵ: ��������ֵ
	d = d2 = d3;
	d.operator=(d2.operator=(d3));

	//���ÿ�������, ��Ϊd4������, ����Ҫ���ù��캯����������
	Date d4 = d3;

	//=����: ������󶼴���,���ø�ֵ���������, �����߲�����, ���ÿ�������

}

void test5() {
	Date d1(2020, 5, 20);
	const Date d2(d1);
	d1.Display(); // ��const����(�ɶ���д), ���÷�const��Ա����, Ҳ���Ե���const��Ա����
				  // ԭ��: ��дȨ��û�б��Ŵ�
	d2.Display(); // const����(ֻ��), ����const��Ա����, ���ܵ��÷�const��Ա����
				  // ԭ��: ��дȨ�޲��ܱ��Ŵ�
}


int main() {
	//test();
	//test1();
	//test3();
	test4();

	return 0;
}