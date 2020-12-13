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
	//也可以创建的时候直接打开文件
	//ifstream fin("test.txt");

	//判断文件是否打开
	if (!fin.is_open()) {
		cout << "file open failed !" << endl;
		return;
	}


	//按照字符流读入
	// >>   getline   get
	int a;
	string str;
	//遇到(换行/空格)结束
	fin >> a;
	fin >> str;

	char arr[100];
	char arr2[100];
	char ch;
	
	//换行作为结束标记, 不读入
	fin.get(ch);
	fin.get(arr, 99);
	fin.get(ch);
	fin.getline(arr2, 99);


	//按照字节流读入  read
		//指定读入7个字节, 不关心数据类型
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

	//按照字符流写
	fout << a.name << endl;
	fout << a.id << endl;

	//即使不手动关闭, 他也会调析构关闭
	fout.close();


	//读入
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

	//字节流
	ofstream fout("test.binary.txt");
	if (!fout.is_open()) {
		return;
	}
	//强转成char*, 按1字节写入, 然后sizeof(A)是要写入的字节数
	fout.write((char*)&a, sizeof(A));
	fout.close();


	A c;

	//模式mode: binary : 按照二进制读内容
	ifstream fin("test.binary.txt", ifstream::binary);
	fin.read((char*)&c, sizeof(A));
	fin.close();
}

/*
* 读写的方式要一致: 二进制文件: 字节流   文本文件: 字符流

	字符流: 可读性强, 读写的格式要一致
	字节流: 读写效率高, 可读性差
*/



void test5() {
	int a = 1234;
	char arr1[50];
	char arr2[50];

	//数字转字符串
	_itoa(a, arr1, 10);  //10是要转换数字的进制

	//把变量a按照整数形式打印到字符数组arr2
	sprintf(arr2, "%d", a);


	//1. 用stringstream流对象进行 数字-->字符串 的转换
	stringstream ss;
	string str;
	ss << a;
	ss >> str;

	//str() : 获取stringstream对象中的字符串内容
	cout << ss.str() << endl;

	//clear() : 下次转换之前, 重置状态位
	ss.clear();

	//什么类型都能转换
	double d = 2.33333333;
	ss << d;
	ss >> str;
	cout << ss.str() << endl;

	//清空stringstream流对象中的内容
	ss.str("");

	//2. stringstream也可以用于拼接字符串
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