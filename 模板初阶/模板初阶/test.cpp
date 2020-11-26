#include<iostream>

using namespace std;

//����ģ��
template<typename T>
void Swap(T& a, T& b) {
	T tmp = b;
	b = a;
	a = tmp;
}
/*
	����ģ��ֻ��һ��ģ��, �����Ǻ���, ���ǿ�ִ�д���
	ʵ�ʿ�ִ�еĴ����ڱ���ʱ����
*/


template<class T>
T Add(const T& a, const T& b) {
	return a + b;
}

//��ͨ�����ͺ���ģ�干��
int Add(int& a, int& b) {
	return a + b;
}


template<class T, class T2>
T Add(const T& a, const T2& b) {
	return a + b;
}



void test() {
	int a = 1, b = 2;
	double c = 1.0, d = 2.0;
	char e = 'e', f = 'f';

	//��ʽʵ����, �������Զ��Ƶ�
	Swap(a, b);
	Swap(c, d);
	Swap(e, f);

	//ǿת
	//Swap(a, (int)d); //���ﲻ������Ϊǿת֮������һ����ʱ����(���г���), ����Ҫ��const����

	Add(a, b);
	Add(c, d);
	Add(e, f);

	//ǿ������ת�� --> ���Ƽ�
	Add(a, (int)d);
	//��ʽʵ����: ����<ʵ��������>(�����б�) --> �Ƽ�
	Add<int>(a, d);
}


void test2() {
	int a = 1, b = 2;
	
	//����������ͺ���ͨ������ȫƥ��, �����ȵ�����ͨ����, ������к���ģ���ʵ����(������Ҳ�Ƚ���~)
	Add(a, b);

	double c = 1.0;
	//�������ģ��������ɲ������͸���ƥ��ĺ���, ���ִ��ʵ���� (����ȷ)
	Add(a, c);

	//���ָ��Ҫ��ʽʵ����, ��Ҫִ��ʵ����, ���������ͨ����
	Add<int>(a, b);
}



template<class T>
struct seqList {
	T* _array;
	size_t _size = 0;
	size_t _capacity = 10;

	seqList(size_t num = 10)
		:_array(new T[num])
	{}

	void push_back(T x) {
		_array[_size++] = x;
	}
};

void test3() {

	//ʵ��������Ϊ��ʾʵ����
	//����: ����<��������>       ���� != ����
	seqList<int> sq;
	seqList<char> sq2;
	seqList<double> sq3;

	sq.push_back(1);
	sq.push_back(2);
	sq.push_back(3);

	sq2.push_back('a');
	sq2.push_back('b');
	sq2.push_back('c');

	sq3.push_back(1.0);
	sq3.push_back(2.0);
	sq3.push_back(3.0);
	  
}


int main() {
	test();
	//test2();
	//test3();

	return 0;
}