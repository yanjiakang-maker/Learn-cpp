#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>


//�����ռ�
namespace bite {
	//���Զ������, ����. Ҳ����Ƕ�׶��������ռ�
	int a;
	int b;

	void fun1(int a) {
		printf("%d\n", a);
	}

	namespace bite_69 {
		int a;
	}
}


void test0() {
	//1. ʹ�������ռ�Ҫ  �ռ��� + :: + ������
	//2. ���� using ����ռ��Ա
	//3. ���� using ���������ռ�
	//�Ƽ�ʹ�õ�һ��

	bite::a = 10;
	bite::fun1(bite::a);

	bite::bite_69::a = 20;
	bite::fun1(bite::bite_69::a);
}


void test() {
	int a = 0;
	int b = 0;

	//c���Ե��������
	scanf("%d", &a);
	printf("%d\n", a);
	
	//c++���������
	//����<iostream>ͷ�ļ� + std�����ռ�
	//����Ҫָ����������ı�����ʽ, ֧���������������
	std::cin >> b;
	std::cout << b << '\n';
}


void test2() {
	//�������Ҫ�� const
	const char* p = "abcd";
	
}


//ȱʡ���� : ����������һ��Ĭ��ֵ, ʹ��ʱû�д��εĻ�, ��ʹ��Ĭ��ֵ
//ȫȱʡ
void func2(int a = 1, int b = 2, int c = 3) {
	std::cout << a << b << c << std::endl;
}

//��ȱʡ : ��������������θ�ֵ, �м䲻�ܼ��
void func3(int a, int b = 2, int c = 3) {
	std::cout << a << b << c << std::endl;
}
//�����Ǵ�����
//void func3(int a = 1, int b, int c = 3);
//void func3(int a, int b = 2, int c);



//��������: ��������ͬ, ������ͬ, ����ͬһ��������	c++֧��
//������ͬ : ����, ����, ˳��ͬ
//���ֻ�Ƿ���ֵ���Ͳ�ͬ, ���ܹ��ɺ�������

int Add(int a, int b) {
	return a + b;
}

int Add(int a, int b, int c) {
	return a + b + c;
}

float Add(float a, float b) {
	return a + b;
}

int Add(int a, char b) {
	return a + b;
}

int Add(char a, int b) {
	return a + b;
}

//extern "C" �����ñ���������c���Եı��������б���
//extern "C" { }  ��ʾ�� { } �ڵĴ��붼����C�������
extern "C" int sub(int a, int b) {

}



//����
void test5(){
	//���� + & + ��������
	int a = 10;
	//a�ı���
	//�����൱�������, ����ra, ra1 ������� a ָ��ͬһ���ڴ�ռ�, ��һ���䶼��
	int& ra = a;
	int& ra1 = a;


	int b = -1;
	ra = b;//����ֻ�Ǹ�ֵ,���ö���֮�󲻻���ȥ�ı�ʵ���ָ�� (���Ǳ�ʾra��b�ı���, ra�ı䲢����ı�b��ֵ)
	        
	//�����ڶ���ʱ�����ʼ��
	//int& ra3;
}





int main() {
	//test();
	//test0();

	//���ε�ʱ��Ҳ�����м���, Ҫ�����������θ�ֵ
	func2(10, 20, 30);
	func2(10); 
	func2();

	func3(2);
	func3(2, 3);

	return 0;
}