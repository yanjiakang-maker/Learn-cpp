#include<iostream>
#include<string>

using namespace std;


class Person {
public:
	void print() {
		cout << "name:" << _name << endl;
		cout << "age:" << _age << endl;
	}


	void func() {
		cout << "Person::func()" << endl;
	}

protected:
	string _name = "monster"; // ����
	int _age = 18; // ����

//private:
	int _id = 0; // ����������
};


//ѧ���� : ���м̳�Person
class Student : public Person {
public:
	void setID() {
		//�����˽�г�Ա�������в��ɼ�. ����ȷʵ������̳�������
		_id = 10;

		//���������е�id, 
		//ͬ������ :  �����м̳е�ͬ��id������
		_id = 100;

		//ͨ�����������������ʸ����е�ͬ������
		Person::_id = 200;
	}

	/*
		ͬ������ : ����Ҳ��ͬ������, ֻҪ��������ͬ�ͻ�����, ���ܲ�����û��
		���Ǻ�������, ��Ϊ�������ص�ǰ������ͬһ��������
		(ͬ������ͨ��������������ʸ����ͬ������)
		����һ�㲻Ҫдͬ���ĳ�Ա, ���Լ��ڿӲ�����
	*/
	void func(int a) {
		cout << "Student::func()" << endl;
	}


	void setName() {
		//����ı�����Ա������ɼ�, �����ⲻ�ɼ�
		_name = "123456";
	}

//protected:
	int _stuid = 2018; // ѧ��   
	int _id = 5; //����������
};


class Teacher : public Person {
protected:
	int _jobid = 2022; // ����
};

void Test() {
	Student s;
	s.func(10);
	s.Person::func();
}


void test() {
	cout << sizeof(Person) << endl;
	cout << sizeof(Student) << endl;

	Person p;
	Student s;
}


void test2() {
	int a = 2.5; //��ʽ����ת��

	Person p;
	Student s;
	s.setName();
	//"��Ƭ"���� :  ���� --> ����   (����ת��)  ���Ķ����Ƕ��, ��һ������
	//����������ำֵ, �����������ڸ���������й�ȥ
	p = s;		
	Person* ptr = &s;  
	Person& ref = s;   


	
	//���������תΪ�������  (����ת��, ���Ķ�������, ����������ݸ���ȥ?)
	//s = p;
	//s = (Student)p;


	//����ָ��/���ò���ת��Ϊ�����ָ��/����
	//ǿת����ת, ������ȫ, ���ʲ��������������ĳ�Ա
	//Student* ptr2 = &p;
	Student* ptr2 = (Student*)&p;
	//Student& ref2 = p;
	Student& ref2 = (Student&)p;
	
	//Խ�����, ��Ȼû����, ���Ѿ�Խ����
	ptr2->_stuid = 2;
	ref2._stuid = 10;
}




class A {
public:
	A() {
		cout << "A()" << endl;
	}

	A(int a)
		: _a(a) {
		cout << "A()" << endl;
	}

	A(const A& a) {
		cout << "A(const A& a)" << endl;
	}

	A& operator=(const A& a) {
		cout << "operator=(const A& a)" << endl;
		return *this;
	}
	
	~A() {
		cout << "~A()" << endl;
	}

private:
	int _a;
};


class B : public A {
public:
	/*
		���๹�������๹���ʼ���б��Զ�����
		��ִ�и���Ĺ��캯��, ��ִ������Ĺ��캯��
		�������û��Ĭ�Ϲ���, ����Ҫ��ʽָ��  (�ڳ�ʼ���б���ָ��)
	 */
	B() 
		:A(5) {
		cout << "B()" << endl;
	}

	//�̳��Ը���ĳ�Ա����������๹����ɳ�ʼ��
	//���������๹���н��г�ʼ��
	B(int a, int b)
		:A(a)
		, _b(b) {
		cout << "B(int, int)" << endl;
	}

	//�������: 
	//B(int a, int b)
	//	:_a(a) {}

	/*
	*	û����ʽ��������Ŀ�������:
	*		���ø���Ŀ�������
	* 
	*	��ʽ��������Ŀ�������:
			Ĭ���ȵ��ø���Ĺ��캯��, Ȼ���ٵ�������Ŀ�������
			��ʽָ�����ø���Ŀ�������, ����ȵ��ø���Ĺ��캯��, Ȼ���ٵ�������Ŀ�������
	*/
	B(const B& b) 
		: A(b) {
		cout << "B(const B& b)" << endl;
	}

	/*
		û����ʽ��������ĸ�ֵ: 
			Ĭ�ϵ��ø���ĸ�ֵ

		��ʽ��������ĸ�ֵ: 
			Ĭ�ϵ�������ĸ�ֵ, ������ø���ĸ�ֵ

		�븸��ĸ�ֵ���������ͬ������
		���Ҫ���ø���ĸ�ֵ, Ҫ�Ӹ����������
	 */
	B& operator=(const B& b) {
		A::operator=(b);
		cout << "operator=(const B& b)" << endl;
		return *this;
	}

	/*
		����˳��͹����෴
			�ȵ������������, �ٵ���������

		�ײ����֮�����������͸���������������ͬ, ����ͬ������
		����ø�������Ҫ�Ӹ���������

		���������κ�����¶����Զ����ø��������
			����Ҫ������������������ʽ���ø�������, ����ᵼ�¸�����������������, ��ɶ����ͷ�
	*/
	~B() {
		cout << "~B()" << endl;
	}

private:
	int _b = 0;
};


void test3() {
	//������������ʱ��, ���Զ����������Ĭ�Ϲ���
	//B b;
	//B b2 = b;

	//B b(1, 2);
	//B b2(3, 4);
	//b = b2;

	B b;
	//B b1;
}


/*
	��Ԫ��ϵ���ܼ̳�, �������Ԫ���ܷ�������ĳ�Ա
		�Ҳ���ʶ�Ҹ�ĸ������..��������
*/

/*
	���ඨ��ľ�̬��Ա, �������̳���ϵ��ֻ����һ����̬��Ա
	���������˶�����, ��Щ�඼����һ����̬��Ա
*/
class C {
public:
	static int _i;
};
int C::_i = 0;

class D : public C {

};

class E : public D {

};

void test4() {
	C c;
	D d;
	E e;
	cout << &c._i << endl;
	cout << &d._i << endl;
	cout << &e._i << endl;
}


//���μ̳�
class AA {
public:
	int _aa;
};

class BB : virtual public AA {   //AA::_aa
public:
	int _bb;
};

class CC : virtual public AA {   //AA::_aa
public:
	int _cc;
};

class DD : public BB, public CC {   //BB::_a   CC::_a
public:
	int _dd;
};

void test5() {
	DD d;
	//�ڴ水�ռ̳�˳������ :  �ȴ�ż̳еĸ���(��˳��), Ȼ�����Լ��ĳ�Ա

	//���μ̳�: �����Ļ����Ա���������, ��������, ��ʹ��ʱҪ��������, �Ƚ��鷳 
	d.BB::_aa = 1;
	d._bb = 2;
	d.CC::_aa = 5;
	d._cc = 3;
	d._dd = 4;

	/*
	*	������μ̳���������Ͷ����Ե�����
		����̳� : �ھ��й����������������ļ̳з�ʽǰ ����virtual
			�����ĸ���
	*/
	d._aa = 8;


	//���, �̳�
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