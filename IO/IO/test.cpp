#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

using namespace std;


void test() {
	int a;
	cin >> a;
	char ch;
	ch = getchar();
	//string str;
	//getline(cin, str);

	cout << ch << "end" << endl;
}


void test2() {
	ifstream fin;
	fin.open("test.txt");
	//Ҳ���Դ�����ʱ��ֱ�Ӵ��ļ�
	//ifstream fin("test.txt");

	//�ж��ļ��Ƿ��
	if (!fin.is_open()) {
		cout << "file open failed !" << endl;
		return;
	}


	//�����ַ�������
	// >>   getline   get
	int a;
	string str;
	//����(����/�ո�)����
	fin >> a;
	fin >> str;

	char arr[100];
	char arr2[100];
	char ch;
	
	//������Ϊ�������, ������
	fin.get(ch);
	fin.get(arr, 99);
	fin.get(ch);
	fin.getline(arr2, 99);


	//�����ֽ�������  read
		//ָ������7���ֽ�, ��������������
	fin.read(arr, 7);  
}


struct A {
	char name[30];
	int id;
};

void test3() {
	ofstream fout("test.txt");
	A a;
	strcpy(a.name, "monster");
	a.id = 2000;

	//�����ַ���д
	fout << a.name << endl;
	fout << a.id << endl;

	//��ʹ���ֶ��ر�, ��Ҳ��������ر�
	fout.close();


	//����
	A b;
	ifstream fin("test.txt");
	fin >> b.name;
	fin >> b.id;
	fin.close();
}


void test4() {
	A a;
	strcpy(a.name, "monster");
	a.id = 2000;

	//�ֽ���
	ofstream fout("test.binary.txt");
	if (!fout.is_open()) {
		return;
	}
	//ǿת��char*, ��1�ֽ�д��, Ȼ��sizeof(A)��Ҫд����ֽ���
	fout.write((char*)&a, sizeof(A));
	fout.close();


	A c;

	//ģʽmode: binary : ���ն����ƶ�����
	ifstream fin("test.binary.txt", ifstream::binary);
	fin.read((char*)&c, sizeof(A));
	fin.close();
}

/*
* ��д�ķ�ʽҪһ��: �������ļ�: �ֽ���   �ı��ļ�: �ַ���

	�ַ���: �ɶ���ǿ, ��д�ĸ�ʽҪһ��
	�ֽ���: ��дЧ�ʸ�, �ɶ��Բ�
*/



void test5() {
	int a = 1234;
	char arr1[50];
	char arr2[50];

	//����ת�ַ���
	_itoa(a, arr1, 10);  //10��Ҫת�����ֵĽ���

	//�ѱ���a����������ʽ��ӡ���ַ�����arr2
	sprintf(arr2, "%d", a);


	//1. ��stringstream��������� ����-->�ַ��� ��ת��
	stringstream ss;
	string str;
	ss << a;
	ss >> str;

	//str() : ��ȡstringstream�����е��ַ�������
	cout << ss.str() << endl;

	//clear() : �´�ת��֮ǰ, ����״̬λ
	ss.clear();

	//ʲô���Ͷ���ת��
	double d = 2.33333333;
	ss << d;
	ss >> str;
	cout << ss.str() << endl;

	//���stringstream�������е�����
	ss.str("");

	//2. stringstreamҲ��������ƴ���ַ���
	ss.clear();
	ss.str("");
	ss << "123" << "  " << "abc";
	ss << "  Best one";
	cout << ss.str() << endl;

}


class Date {
public:
	Date(int y = 2020, int m = 5, int d = 20)
		:_year(y), _month(m), _day(d) 
	{ }

	friend ostream& operator<<(ostream& cout, const Date& d);

private:
	int _year;
	int _month;
	int _day;
};
ostream& operator<<(ostream& cout, const Date& d) {
	cout << d._year << " " << d._month << " " << d._day << endl;
	return cout;
}

void Test() {
	Date d(2020, 12, 7);
	cout << d << endl;
}


int main() {
	//test();
	//test2();
	//test3();
	//test4();
	test5();
	//Test();

	return 0;
}