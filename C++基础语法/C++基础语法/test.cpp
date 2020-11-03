#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<stdio.h>
#include<time.h>

using namespace std;


//�����ռ� namespace
namespace bite {
	void print(int a) {
		printf("%d\n", a);
	}

	int a;
	int b;

	//����Ƕ�׶���
	namespace bite_69 {
		void fun1(int a) {
			printf("%d\n", a);
		}

		int a;
		int b;
	}
}

//���Էֶζ���,��������ϲ���ͬ�������ռ�
//��ͬ�������ռ䲻�ܶ����ظ��ı����ͺ���
namespace bite {
	int c;
	int d;

	void fun2() {
		printf("fun2()\n");
	}
}


int a;
int b;

/*
	�����ռ��Աʹ�÷�ʽ
	1. �����ռ� :: ��Ա
	2. �����Ա using + �����ռ� :: ��Ա    ����ʹ�ó�Աʱ����Ҫ�ټ�������
	     ������Ա��¶��ȫ������, ���ȫ��������ͬ����Ա, ��ᵼ��������ͻ
	3. չ�������ռ� using + �����ռ�   �����ռ������еĳ�Ա��¶��ȫ������
*/

using bite::fun2;
//using namespace bite;

void test() {
	bite::a = 1;
	bite::print(bite::a); //bite�����ռ��µĳ�Աa
	bite::print(a); //ȫ��a

	bite::bite_69::a = 2;
	bite::c = 3;
	bite::fun2();
	fun2();
}


void test2(int a) {
	a = 10; //�ֲ���
	bite::a = 20; //�����ռ���
	bite::bite_69::a = 30; //�����ռ���
	::a = 40; //ȫ����
}


//�������
void test3() {
	int a = 10;
	int b;
	printf("%d\n", a);
	scanf("%d", &b);
	
	//C++������� :  ͷ�ļ�<iostream> + std�����ռ�
	//����Ҫ��ʾָ��������������ĸ�ʽ, ֧���������������
	std::cout << a << std::endl;
	std::cin >> b >> a;

	const char* p = "1234";
	int* pa = &a;
	std::cout << pa << std::endl; // ���ַ���ָ�������ַ
	std::cout << p << std::endl; // �ַ���ָ���������
}


//ȱʡ����: ����������һ��Ĭ��ֵ, ʵ��ʹ��ʱ, ���û�д���, ��Ӧ���β�ʹ��Ĭ��ֵ
//ȫȱʡ : ���в�������ȱʡֵ
void test4(int a = 1, int b = 2, int c = 3) {
	cout << a << " " << b << " " << c << endl;
}

//��ȱʡ : ���ֲ�����ȱʡֵ
//      ������������������θ�ֵ, �м䲻���м��
void test5(int a, int b = 1, int c = 2) {
	cout << a << " " << b << " " << c << endl;
}

//ȱʡֵֻ�ܳ������������߶���ĵط�, ����ͬʱ���� (��������ѡ������֢, ����д�����ԵĴ���)
void test6(int a = 1, int b = 2, int c = 3);
void test6(int a, int b, int c) {
	cout << a << " " << b << " " << c << endl;
}


//�������� : ��������ͬ, ������ͬ, ����ͬһ��������
//������ͬ : ����, ����, ˳��ͬ
//���з���ֵ���Ͳ�ͬ, ���ܹ��ɺ�������
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

//void Add(int a, char b) {
//	return a + b;
//}


void test7() {
	int a = 1;
	int b = 2;
	float c = 1.5;
	float d = 2.5;
	char f = 'a';
	int e = 3;
	Add(a, b);
	Add(c, d);
	Add(a, b, e);
	Add(a, f);
	Add(f, b);
}

////extern "C" �ñ���������C���Եı��������б���
//extern "C" {
//	int sub(int a, int b);
//	int mul(int a, int b);
//}
//void test8() {
//	sub(1, 2);
//	mul(2, 8);
//}


//����
void test9() {
	//���� : ���� + & + ��������
	//�����ڶ���ʱ����Ҫ��ʼ��
	int a = 10;
	//a�ı���
	int& ra = a;
	int& ra2 = a;
	ra2 = 30;
	ra = 100;
	a = 1000;

	cout << &a << endl;
	cout << &ra << endl;
	cout << &ra2 << endl;

	int b = -1;
	//���ö���֮��, ������ȥ����ʵ���ָ��
	// �����Ǹ�ֵ����, ��������ra��Ϊb�ı���
	ra = b;
	ra = -100;
}

void test10() {
	//const ����
	const int a = 10;
	const int& ra = a;
	const int& r = 10;

	double d = 2.0;
	double& rd = d;

	int c = d;
	//d��ʽ����ת��, ����һ����ʱ�����ͱ���, rd2ָ���λ����ʱ����
	//��ʱ�������г���, ����Ҫ�Ӹ�const
	const int& rd2 = d;
}


void Swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void Swap(int& ra, int& rb) {
	int tmp = ra;
	ra = rb;
	rb = tmp;
}

void t() {
	int a = 1;
	int b = 2;
	Swap(&a, &b);
	cout << a << " " << b << endl;
	Swap(a, b);
	cout << a << " " << b << endl;
}

int& Add(int& a) {
	return ++a;
}

//����������ֵ: ע�ⷵ�ر�������������һ��Ҫ���ں�������������
int& Add2(int a) {
	return ++a;
}

void t2() {
	int a = 0;
	int& b = Add(a); 
	int c = Add(a);
	int& d = Add2(a); //�������ͱ��� dָ��Add2()����ջ֡�еľֲ�����a, ��Add2��������֮�����a����
					  //�����int d = Add2(a) ��û������, ��Ϊ�ǿ�����һ���µĿռ䱣��a��ֵ
	cout << d << endl;
	cout << a << endl;
	cout << d << endl;
}


struct A {
	int array[10000];
};

void fun1(A a) {
}
void fun2(A& a) {
}
void t3() {
	A a;
	int n = 100000;
	size_t begin = clock();
	for (int i = 0; i < n; i++)
		fun1(a);
	size_t end = clock();
	cout << "fun1(int): " << end - begin << endl;

	begin = clock();
	for (int i = 0; i < n; i++)
		fun2(a);
	end = clock();
	cout << "fun2(int&): " << end - begin << endl;
}

A g;

A fun3() {
	return g;
}

A& fun4() {
	return g;
}

void t4() {
	A a;
	int n = 100000;
	size_t begin = clock();
	for (int i = 0; i < n; i++)
		fun1(a);
	size_t end = clock();
	cout << "fun3(): " << end - begin << endl;

	begin = clock();
	for (int i = 0; i < n; i++)
		fun2(a);
	end = clock();
	cout << "fun4(): " << end - begin << endl;
}

//�ڵײ� ����ͨ��ָ��ʵ��   ����һ���������ͱ����൱�ڶ���һ��ָ�����ͱ���
//�﷨: �����Ǳ���, ����ָ��, û�з������� 
void t5() {
	int a = 10;
	int* pa = &a;
	*pa = 20;

	int& ra = a;
	ra = 30;
}


//��������: ����������ʱ, ����к���ָ���չ��, û��ջ֡�Ŀ���, ��ߴ���Ч��
//����꺯��ʹ��
inline int ADD(int a, int b) {
	return a + b;
}
//inline ֻ��һ������, �����������ʵ����������ж�, ��������, ֱ��չ��, ���븴���򲻻�չ��
inline void fun5() {
	for (int i = 0; i < 10000; i++) {
		int a = i;
		int b = a * i;
		int c = b * i;
	}
}

void t6() {
	int c = ADD(3, 5);
	fun5();
}


void t7() {
	//auto : C++��, �Զ������Ƶ�, �������������
	//����ʱ, ���ݳ�ʼ�����ʽ�Զ��Ƶ� (���԰�, �����ʼ��)
	//auto�൱�����͵�ռλ��, ���������ڱ���ʱ�����Ƶ�
	auto a = 2;
	auto f = 3.5;
	auto c = 'a';
	auto d = 'a' + 'b';
	cout << typeid(a).name() << endl;
	cout << typeid(f).name() << endl;
	cout << typeid(c).name() << endl;
	cout << typeid(d).name() << endl;

	//auto���Զ���������, ��������Ҫһ��(ֻ��һ���Ƶ�)
	auto a1 = 2, c1 = 6;
	//auto a2 = 2.5, c2 = 5;

	//auto����ָ��ʱ, �Ӳ���*,û������
	auto pa = &a;
	auto* pa2 = &a;
	cout << typeid(pa).name() << endl;
	cout << typeid(pa2).name() << endl;

	//��������ʱ�����&����
	auto& ra = a; //int&
	auto ra2 = a; //int
}
////�����������Ͳ���ʹ��auto
//void fun6(auto a) {
//}
////�������鲻����auto
//auto array[] = { 0, 1, 2, 3, 4 };


//��Χfor ->   Ҫ�����ı���  :  ������Χ
void t8() {
	int array[] = { 1, 2, 3, 4, 5, 6 };
	for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++)
		cout << array[i] << " ";
	cout << endl;

	//��Χfor : ʹ�ó���: ���ݷ�Χȷ�� 
	for (auto e : array)
		cout << e << " ";
	cout << endl;
}


//ָ��ֵnullptr
void t9() {
	int* p = NULL; // �ȼ��� int* p = 0;
}

void fun7(int a) {
	cout << "fun7(int)" << endl;
}

void fun7(int* pa) {
	cout << "fun7(int*)" << endl;
}

struct AS {

};

void t10() {
	fun7(NULL); //������Ĭ��NULLΪ���͵�0, ������ָ���ֵ
	fun7((int*)NULL);// NULL�ж�����: ָ���ֵ �� ����0

	//nullptr: ָ���ֵ, ������ȷ
	fun7(nullptr);

	//nullptr������ʽת���������ָ������(���ú��Զ���)
	int* p = nullptr;
	char* p1 = nullptr;
	float* p2 = nullptr;
	AS* pas = nullptr;

	//nullptr����Ϊ: nullptr_t
	cout << typeid(nullptr).name() << endl;
	cout << sizeof(nullptr) << endl;

	auto p3 = nullptr;
	cout << typeid(p3).name() << endl;
}




int main() {
	//test();
	//test2(0);
	//test3();
	//test4(1, 2, 3);
	//test4();
	//test4(100, 200, 300);
	//test5(10);
	//test6();
	//test7();
	//test8();
	//test9();
	//test10();
	//t();
	//t2();
	//t3();
	t4();
	//t6();
	//t7();
	//t8();
	//t10();

	return 0;
}