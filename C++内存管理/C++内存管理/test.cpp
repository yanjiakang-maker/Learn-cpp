#include<iostream>

using namespace std;



void test() {
	int num = 4;

	//malloc: ֻ����ռ�
	int* p1 = (int*)malloc(sizeof(int) * num);

	//calloc: ����ռ� ���ҳ�ʼ��Ϊ0
	//calloc(���ݸ���, ���ݴ�С)
	int* p2 = (int*)calloc(num, sizeof(int));

	//realloc: �����ռ�, �����ʼ��, ���´��ԭ������
	//realloc(�ռ��׵�ַ, ��С)
	//�����ռ�ʱ���p1�ͷ�, �����µĿռ�, ���һ��p1���ݿ�������
	int* p3 = (int*)realloc(p1, sizeof(int) * 100);


	//realloc(nullptr, ��С)  �ȼ���malloc
	char* p4 = (char*)realloc(nullptr, sizeof(char));


	free(p2);
	free(p3);
}


void test2() {
	//realloc��3�����

	//1. 
	int* p = (int*)malloc(sizeof(int));
	*p = 10;

	int* p2 = (int*)realloc(p, sizeof(int) * 100);

	//2. 
	char* pa = (char*)malloc(sizeof(char));
	*pa = 'a';
	char* pc = (char*)realloc(pa, sizeof(char) * 2);

	//3.
	char* pd = (char*)realloc(pc, sizeof(char));

	free(p);
	free(p2);
	free(pa);
	free(pc);
	free(pd);


}


class Date {
public:
	Date(int y = 1, int m = 1, int d = 1)
		:_year(y)
		,_month(m)
		,_day(d)
	{
		cout << "Date(int, int, int)" << endl;
	}


	void* operator new(size_t size) {
		cout << "operator new" << endl;
		void* ptr = malloc(size);
		return ptr;
	}


	~Date() {
		cout << "~Date()" << endl;
	}

private:
	int _year = 2020;
	int _month = 5;
	int _day = 20;
};


void test3() {
	//����һ������
	int* pa = (int*)malloc(sizeof(int));
	int* pa2 = new int;

	//���������ռ�
	int* pb = (int*)malloc(sizeof(int) * 10);
	int* pb2 = new int[10];

	//�������, ���ҳ�ʼ��Ϊ20
	int* d = new int(20);

	//�ͷ�һ��Ԫ��
	free(pa);
	delete pa2;
	delete d;
	
	//�ͷ������ռ�
	free(pb);
	delete[] pb2;
}

void test4() {

	Date* pd = (Date*)malloc(sizeof(Date));
	
	//�Զ�����Ĭ�Ϲ�����ɳ�ʼ��
	Date* pd1 = new Date;

	Date* pd2 = new Date(2020, 10, 24);

	//�ڶ��ϴ����Զ�����������, newֻ�ܵ���Ĭ�Ϲ��� (û���Լ�����ʼֵ, Ҳ����[]��()����ͬʱ����)
	Date* pd3 = new Date[10];


	//delete�������������, delete[]����ö������
	free(pd);
	delete pd1;
	delete pd2;
	delete[] pd3;


	//new:  ���ռ� --> ����
	//delete: ���� --> �ͷſռ� 
}


void test5() {
	//new --> operator new --> malloc --> ���캯��
	//operator new ������������غ���, ֻ��һ��ȫ�ֺ���
	//ʵ������ malloc + �쳣 �ķ�װ
	Date* pd = new Date;
}




class A {
public:
	A() {
		cout << "A()" << endl;
	}

	A(int a) {
		cout << "A(int)" << endl;
	}

	~A() {
		cout << "~A()" << endl;
	}
};


void test6() {
	//new�Ķ�λ���ʽ

	A* pa = (A*)malloc(sizeof(A));
	//��ʾ���ù��캯��
	new (pa)A();

	A* pa2 = (A*)malloc(sizeof(A));
	new (pa2)A(10);

	
	//��ʾ��������, ��������е���Դ
	pa->~A();
	pa2->~A();


	//�ͷŶ���ռ�
	free(pa);
	free(pa2);
}


void test7() {
	char* p = new char[100];
	delete p;
}


int main() {
	//test();
	test2();
	//test4();
	//test5();
	//test6();
	//test7();

	return 0;
}


int globalVar = 1;
static int staticGlobalVar = 1;

void Test() {
	static int staticVar = 1;
	int localVar = 1;
	int num1[10] = { 1, 2, 3, 4 };

	char char2[] = "abcd";
	const char* pChar3 = "abcd";

	int* ptr1 = (int*)malloc(sizeof(int) * 4);
	int* ptr2 = (int*)calloc(4, sizeof(int));
	int* ptr3 = (int*)realloc(ptr2, sizeof(int) * 4);

	free(ptr1);
	free(ptr3);
}