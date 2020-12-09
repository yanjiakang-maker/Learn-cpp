#include<iostream>
#include<list>
#include<queue>

using namespace std;


//template <class T>
//class Queue {
//public:
//	//构造函数也不用写
//
//	//入队  ---> 尾插
//	void push(const T& val) {
//		_lst.push_back(val);
//	}
//
//	//出队 ---> 头删 (用顺序表效率低)
//	void pop() {
//		_lst.pop_front();
//	}
//
//	//获取队头元素
//	T& front() {
//		return _lst.front();
//	}
//
//	//获取队尾元素
//	T& back() {
//		return _lst.back();
//	}
//
//	//判空
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
	//构造函数也不用写

	//入队  ---> 尾插
	void push(const T& val) {
		_lst.push_back(val);
	}

	//出队 ---> 头删 (用顺序表效率低)
	void pop() {
		_lst.pop_front();
	}

	//获取队头元素
	T& front() {
		return _lst.front();
	}

	//获取队尾元素
	T& back() {
		return _lst.back();
	}

	//判空
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


	//vector不能用来实现队列, 因为vector不提供pop_front接口

	//库中的队列, 也可以传递第二个参数, 改变底层的容器实现
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