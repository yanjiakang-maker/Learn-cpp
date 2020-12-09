#include<iostream>
#include<list>
#include<queue>

using namespace std;


//template <class T>
//class Queue {
//public:
//	//���캯��Ҳ����д
//
//	//���  ---> β��
//	void push(const T& val) {
//		_lst.push_back(val);
//	}
//
//	//���� ---> ͷɾ (��˳���Ч�ʵ�)
//	void pop() {
//		_lst.pop_front();
//	}
//
//	//��ȡ��ͷԪ��
//	T& front() {
//		return _lst.front();
//	}
//
//	//��ȡ��βԪ��
//	T& back() {
//		return _lst.back();
//	}
//
//	//�п�
//	bool empty() {
//		return _lst.empty();
//	}
//
//	//size
//	size_t size() {
//		return _lst.size();
//	}
//
//private:
//	list<T> _lst;
//};



template <class T, class Container>
class Queue {
public:
	//���캯��Ҳ����д

	//���  ---> β��
	void push(const T& val) {
		_lst.push_back(val);
	}

	//���� ---> ͷɾ (��˳���Ч�ʵ�)
	void pop() {
		_lst.pop_front();
	}

	//��ȡ��ͷԪ��
	T& front() {
		return _lst.front();
	}

	//��ȡ��βԪ��
	T& back() {
		return _lst.back();
	}

	//�п�
	bool empty() {
		return _lst.empty();
	}

	//size
	size_t size() {
		return _lst.size();
	}

private:
	Container _lst;
};


//void test() {
//	Queue<int> q;
//	q.push(1);
//	q.push(2);
//	q.push(3);
//	q.push(4);
//	q.push(5);
//
//	while (!q.empty()) {
//		cout << q.front() << " ";
//		q.pop();
//	}
//	cout << endl;
//}


void test2() {
	Queue < int, list<int>> q;
	q.push(1);
	q.push(2);
	q.push(3);

	while (!q.empty()) {
		cout << q.front() << " ";
		q.pop();
	}
	cout << endl;


	//vector��������ʵ�ֶ���, ��Ϊvector���ṩpop_front�ӿ�

	//���еĶ���, Ҳ���Դ��ݵڶ�������, �ı�ײ������ʵ��
	queue <int, list<int>> q2;
	q2.push(1);
	q2.push(2);
	q2.push(3);

	while (!q2.empty()) {
		cout << q2.front() << " ";
		q2.pop();
	}
	cout << endl;
}



int main() {
	//test();
	test2();

	return 0;
}