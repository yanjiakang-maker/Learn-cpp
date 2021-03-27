#include <iostream>

using namespace std;


void test() {
	//��ʽ����ת�����������Ƶ�����
	int a = 10;
	char b = 'a';
	float c = 2.3;

	//��ʽ����ת��
	a = b;
	c = b;

	//ǿ������ת��
	int ptrInt = (int)&a;
	cout << ptrInt << endl;

	int* ptr = (int*)a; // 0xa
	//���պܴ󣺷Ƿ�����
	cout << *ptr << endl;
}


void test2() {
	int a = 10;
	char b = 'b';
	double f = 3.5;

	//static_cast<����>: ֧��C���Ե���ʽ����ת��
	//�ɶ���ǿ
	b = static_cast<char> (a);
	a = static_cast<int> (f);

	//reinterpret_cast<����>:֧��C���Ե�ǿ������ת��
	//�ɶ���ǿ
	int* ptr = reinterpret_cast<int*> (a);

	//const_cast<����>:ȥ�����ݵ�const����
	const int* ptr2 = &a;
	int* ptr3 = const_cast<int*>(ptr2);

	const int c = 20;
	int d = c;

}


class Base {
public:
	virtual void fun() {
		cout << "Base fun()" << endl;
	}
};

class Derived : public Base {
public:
	virtual void fun() {
		cout << "Derived fun()" << endl;
	}

	int _b = 100;
};

void test3() {
	//����ת��: ��Ƭ (����-->����)
	Base base;
	Derived derived;
	base = derived;
	//����ת��: ����-->����
	Base base2;
	Derived derived2;
	//derived2 = static_cast<Derived>(base2);
	Derived* ptr = static_cast<Derived*>(&base2);
	//�Ƿ�����
	cout << ptr->_b << endl;

	//����������ǰ�ȫ��
	Base* bPtr = &derived2;
	Derived* ptr2 = static_cast<Derived*>(bPtr);
	cout << ptr2->_b << endl;


	//dynamic_cast<����>:��̬����������ת�� (�����Ƕ�̬)
	//��ȫ���: ��ȫ������ת��, ����ȫ����nullptr
	ptr = dynamic_cast<Derived*> (&base2);
	ptr2 = dynamic_cast<Derived*>(bPtr);
}


int main() {
	//test();
	test3();

	return 0;
}