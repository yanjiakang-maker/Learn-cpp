#include<iostream>
#include<stack>
#include<queue>

using namespace std;


void test() {
	stack<int> st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	st.push(5);

	//��Ϊ�յĻ���ӡջ��Ԫ��, Ȼ���ջ, ����ѭ��
	while (!st.empty()) {
		cout << st.top() << " ";
		st.pop();
	}
	cout << endl;
}


void test2() {
	//���ȼ�����
	//ͨ����ʵ��, Ĭ��Ϊ���
	priority_queue<int> pq;
	pq.push(10);
	pq.push(1);
	pq.push(15);
	pq.push(23);
	pq.push(50);
	pq.push(40);

	while (!pq.empty()) {
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;
}


struct C {

	C(int a = 0, int b = 0, int c = 0)
		:_a(a)
		,_b(b)
		,_c(c)
	{}

	bool operator<(const C& c) const {
		return _a < c._a;
	}

	bool operator>(const C& c) const {
		return _a > c._a;
	}

	int _a;
	int _b;
	int _c;
};
ostream& operator<<(ostream& cout, const C& c) {
	cout << c._a << " " << c._b << " " << c._c << endl;
	return cout;
}

//�º�����ģ��
template <class T>
class Less {
public:
	//�������������
	//����ֵ���Ͳ���, �Ӿ����������
	bool operator()(const T& c1, const T& c2) {
		return c1 < c2;
	}
};

template <class T>
class Greater {
public:
	//�������������
	//����ֵ���Ͳ���, �Ӿ����������
	bool operator()(const T& c1, const T& c2) {
		return c1 > c2;
	}
};


void test3() {
	//���ȼ����д���Զ�������, �Զ���������Ҫ֧�ִ�С�Ƚ�����
	//�����, Ҫ�ṩС�������
	priority_queue<C> pq;
	pq.push(C(1, 1, 1));
	pq.push(C(2, 1, 1));
	pq.push(C(5, 1, 1));
	pq.push(C(4, 1, 1));
	pq.push(C(3, 1, 1));

	while (!pq.empty()) {
		cout << pq.top();
		pq.pop();
	}
}


void test4() {
	Less<C> lc;
	C c1(1, 2, 3);
	C c2(2, 2, 2);
	bool ret = lc.operator()(c1, c2);
	ret = lc(c1, c2); // ������ȼ�
}


void test5() {
	//���ȼ����д���Զ�������, �Զ���������Ҫ֧�ִ�С�Ƚ�����
	//��С��, Ҫ�ṩ���Խ���С�ڱȽϵķº�����
	priority_queue<C, vector<C>, Greater<C>> pq;
	pq.push(C(1, 1, 1));
	pq.push(C(2, 1, 1));
	pq.push(C(5, 1, 1));
	pq.push(C(4, 1, 1));
	pq.push(C(3, 1, 1));

	while (!pq.empty()) {
		cout << pq.top();
		pq.pop();
	}

	//����ѵ�����д��, �ṩLess
	priority_queue<C, vector<C>, Less<C>> pq1;

}


void test6() {
	queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	q.push(5);

	while (!q.empty()) {
		cout << q.front() << " ";
		//ɾ����ͷԪ��
		q.pop();
	}
	cout << endl;
}


int main() {
	//test();
	//test2();
	//test3();
	//test4();
	//test5();
	test6();

	return 0;
}