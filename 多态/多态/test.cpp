#include<iostream>

using namespace std;


class AA { };

class BB : public AA { };



/*
*	ʵ�ֶ�̬ (ǰ��: �̳�)

	���ú���������̬����Ϊ :
		1. ��������Ϊ�麯��  virtual ����
		2. �麯����Ҫ����������д
		3. �����麯��ʱ, ������ָ��������õ���
*/

class Person {
public:
	virtual void buyTicket() {
		cout << "��ͨƱ -- ȫ��" << endl;
	}

	//virtual AA* buyTicket() {
	//	cout << "��ͨƱ -- ȫ��" << endl;
	//	return &AA();
	//}

};

class Student : public Person {
public:
	/*
		��������麯������д
		�������¶���һ���͸���ӿ���ȫ��ͬ�ĺ��� (������, ����, ����ֵ����ͬ)

		ֻ��һ������ :  Э��  (����ֵ���Բ�ͬ)
			������ֵ�����ǹ��ɸ��Ӽ̳й�ϵ��ָ��/����
			һ�㲻Ҫд����, ���
	*/
	virtual void buyTicket() {
		cout << "ѧ��Ʊ -- ���" << endl;
	}

	//virtual BB* buyTicket() {
	//	cout << "ѧ��Ʊ -- ���" << endl;
	//	return &BB();
	//}

	~Student() {

	}
};


void func(Person* p) {
	p->buyTicket();
}

void func(Person p) {
	p.buyTicket();
}

void test() {
	Person p;
	Student s;

	Person* pp = &p;
	Student* ps = &s;

	//�������ָ�����һ�¶�Ӧ�ĺ�������, ���Ƕ�̬
	pp->buyTicket();
	ps->buyTicket();
	cout << endl;

	// ��̬ : ������
	func(&p); 
	func(&s);
	cout << endl;

	// �Ƕ�̬ : ������
	func(p);
	func(s);
	cout << endl;
}



class A {
public:
	//��������д���麯��
	virtual ~A() {
		cout << "~A()" << endl;
	}

	//�������д�� :  �����virtual, ���಻��, ���๹�ɶ�̬
	//               ���಻��virtual, �������, ��ʱ���಻���ɶ�̬ 
	//      ����һ�����麯��������virtual, ����Լ����鷳


	//final�ؼ��� : ���ε��麯��, �������в����ٱ���д  (������ʵ�ּ̳�,  �Ҽ̳�����ֱ����, ������д)
	virtual void func() final {
		cout << "A::func()" << endl;
	}

	virtual void func2() {
		cout << "A::func2()" << endl;
	}


	//���麯��   (û�к�����)
	//������ :  �������麯������
	//�����಻��ʵ���� :  ��Ա������
	//����̳��˳�����, ����ʵ�ִ��麯��, �����ʵ��, Ҳ��һ��������, ����ʵ����

	//virtual void func4() = 0;

};

class B : public A {
public:
	//��д������������� :  ��Ϊ�ײ�ĺ���������ͬ��, �ӿ���ȫһ��  (��ô��ƾ���Ϊ��ʵ�ֶ�̬)
	virtual ~B() {
		cout << "~B()" << endl;
	}

	//override :  ǿ������ĺ���������д�����һ���麯��  (�����˽ӿڼ̳�, ��ֻ����Ľӿ�, ��������߼�)
	//һ��������д����, ��һ���Ա��Լ����������ػ�����д
	virtual void func2() override {
		cout << "B::func2()" << endl;
	}


	//��д�����еĴ��麯��
	virtual void func4() {
		cout << "B::func4()" << endl;
	}
};


void test2() {
	A* pa = new A;
	B* pb = new B;
	delete pa;
	delete pb;

	//��Ƭ :  ���ڴ�й©�ķ��� (�������Ƕ�̬)
	//��̬ :  ������  --> �������  -->  ��������
	//�ø���ָ��/���� ָ��̳���ϵ�еĶ���
	A* pc = new B;
	delete pc;   //ֻ���ø�������, �������������Դ, ������ڴ�й©, �������Դ���ᱻ�ͷ�
				 // �����������д���麯��, �ͽ�������� ()
}



//class Base {
//public:
//	//ʹ���麯����, ���ڶ����д��һ�����ָ��  
//	//(��� : ����麯���ĵ�ַ, ���麯����ָ������)
//	//���ָ��ָ�������׵�ַ, �Ƕ���ָ��  
//	virtual void func1() {
//		cout << "func1()" << endl;
//	}
//
//	virtual void func2() {
//		cout << "func2()" << endl;
//	}
//
//private:
//	int _a = 1;
//};
//
//void test3() {
//	cout << sizeof(Base) << endl;
//
//	//������֤���ָ�������
//
//	//���ݶ�
//	static int si = 3;
//	//ջ
//	int stackval = 2;
//	//��
//	int* heapval = new int;
//	//�����
//	const char* p = "123";
//
//	Base b;
//	//���ָ�� : ����ͷ4/8�ֽ�
//	int addr = *((int*) &b);  //��ȡ����ͷ4���ֽڵ�����
//	cout << "���ָ��: ";
//	printf("%p\n", addr);
//
//	printf("�����: %p\n", p);	
//	printf("���ݶ�: %p\n", &si);	
//	printf("��: %p\n", &heapval);
//	printf("ջ: %p\n", &stackval);
//
//	//���¿���֤����VS��, �����ڴ����
//		/*
//			���ָ��: ������   (��������׵�ַ)
//			���: �����  (����麯�����׵�ַ)
//			�麯��: �����
//		*/
//}



/*
	��̬ : ������
		�麯������Ϊ : ����д�ŵ�ʵ�ʵ�ַ����

	��̬���� : 
		1. ����ͨ��ָ��/���ö�λ��ʵ�ʵĶ���
		2. �Ӷ����л�ȡʵ�������׵�ַ (���ָ��)
		3. ��������ҵ�������ʵ�ʵ�ַ
		���ִ��
*/

class Base {
public:
	virtual void func1() { cout << "Base::func1" << endl; }
	virtual void func2() { cout << "Base::func2" << endl; }
private:
	int a;
};

class Derive : public Base {
public:
	virtual void func1() { cout << "Derive::func1" << endl; }
	virtual void func3() { cout << "Derive::func3" << endl; }
	virtual void func4() { cout << "Derive::func4" << endl; }
private:
	int b;
};

typedef void (*pfun)();

void printVfptr(pfun* vftable) {
	cout << "����ַ: " << vftable << endl;

	for (; vftable != nullptr; ++vftable) {
		cout << "������ַ: " << *vftable << " ";
		(*vftable)();
		cout << endl;
	}
}


void test4() {
	Base b;
	pfun* vftable = (pfun*)*((int*)&b);
	(*vftable)();
	(*(vftable + 1))();

	Derive d;
	pfun* vftable2 = (pfun*)*((int*)&d);
	(*vftable2)();
	(*(vftable2 + 1))();
	(*(vftable2 + 2))();
	(*(vftable2 + 3))();


}



int main() {
	//test();
	//test2();
	//test3();
	test4();

	return 0;
}