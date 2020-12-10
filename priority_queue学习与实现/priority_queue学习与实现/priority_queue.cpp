#include<iostream>
#include<vector>
#include<list>
#include<queue>
#include<algorithm>
#include<functional>

using namespace std;


//�º����� : ���������ں�������
//   �������� ���� () �����
template <class T>
struct Less {
	// ()���������
	bool operator() (const T& val1, const T& val2) {
		return val1 < val2;
	}
};

template <class T>
struct Greater {
	// ()���������
	bool operator() (const T& val1, const T& val2) {
		return val1 > val2;
	}
};



//	�ײ�ʵ������Ĭ����vector
template <class T, class Container = vector<T>, class Compare = less<T>>
class PriorityQueue {
public:
	//���ϵ���
	void shiftUp(int child) {
		//��ȡ����λ��
		int parent = (child - 1) / 2;

		while (child > 0) {
			//�������С�ں���, ����, ����
			//if (_c[parent] < _c[child]) {
			if (_cmp(_c[parent], _c[child])) {
				swap(_c[parent], _c[child]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
				break;
		}

	}


	//���� :  β�� + ���ϵ���
	void push(const T& val) {
		_c.push_back(val);
		shiftUp(_c.size() - 1);
	}


	//ɾ���Ѷ�Ԫ��  :  ��β���� + βɾ + ���µ���
	void pop() {
		swap(_c[0], _c[_c.size() - 1]);
		_c.pop_back();
		shiftDown(0);
	}

	//���µ���
	void shiftDown(int parent) {
		//��ȡ����λ��
		int child = 2 * parent + 1;

		while (child < _c.size()) {
			//�ҵ����Һ����еĴ���
			//if (child + 1 < _c.size() && _c[child] < _c[child + 1])
			if (child + 1 < _c.size() && _cmp(_c[child], _c[child + 1]))
				child++;

			//�������С�ں���
			//if (_c[parent] < _c[child]) {
			if (_cmp(_c[parent], _c[child])) {
				swap(_c[child], _c[parent]);
				//����
				parent = child;
				child = 2 * parent + 1;
			}
			else
				break;
		}
	}

	//��ȡ�Ѷ�Ԫ��
	T& top() {
		return _c.front();
	}

	//�п�
	bool empty() {
		return _c.empty();
	}

	//��ȡsize
	size_t size() {
		return _c.size();
	}


private:
	Container _c;
	Compare _cmp;
};


void test() {
	//���
	//���ȼ����е�Ĭ��������vector -->(�������Ч�ʸ�)
	//PriorityQueue<int, vector<int>, less<int>> pq;
	//PriorityQueue<int, deque<int>> pq;

	PriorityQueue<int, vector<int>, Less<int>> pq;


	//list������Ϊ�ײ�����, ��Ϊ��֧���������
	//PriorityQueue<int, list<int>> pq;
	
	pq.push(10);
	pq.push(1);
	pq.push(16);
	pq.push(99);
	pq.push(33);

	while (!pq.empty()) {
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;
}


//�Զ�������Ҫ�Լ�ʵ�ִ���С���߼� ---> ���� > , < �����

void testless() {
	Less<int> less;
	int a = 2, b = 5;

	if (less(a, b)) {
		cout << "a < b" << endl;
	}
	else {
		cout << "a > b" << endl;
	}

	
	a = 5;
	b = 2;

	if (less(a, b)) {
		cout << "a < b" << endl;
	}
	else {
		cout << "a > b" << endl;
	}
}


int main() {
	test();
	//testless();

	return 0;
}