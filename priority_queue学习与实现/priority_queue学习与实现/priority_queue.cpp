#include<iostream>
#include<vector>
#include<list>
#include<queue>
#include<algorithm>
#include<functional>

using namespace std;


//仿函数类 : 功能类似于函数的类
//   必须重载 括号 () 运算符
template <class T>
struct Less {
	// ()运算符重载
	bool operator() (const T& val1, const T& val2) {
		return val1 < val2;
	}
};

template <class T>
struct Greater {
	// ()运算符重载
	bool operator() (const T& val1, const T& val2) {
		return val1 > val2;
	}
};



//	底层实现容器默认是vector
template <class T, class Container = vector<T>, class Compare = less<T>>
class PriorityQueue {
public:
	//向上调整
	void shiftUp(int child) {
		//获取父亲位置
		int parent = (child - 1) / 2;

		while (child > 0) {
			//如果父亲小于孩子, 交换, 更新
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


	//插入 :  尾插 + 向上调整
	void push(const T& val) {
		_c.push_back(val);
		shiftUp(_c.size() - 1);
	}


	//删除堆顶元素  :  首尾交换 + 尾删 + 向下调整
	void pop() {
		swap(_c[0], _c[_c.size() - 1]);
		_c.pop_back();
		shiftDown(0);
	}

	//向下调整
	void shiftDown(int parent) {
		//获取左孩子位置
		int child = 2 * parent + 1;

		while (child < _c.size()) {
			//找到左右孩子中的大者
			//if (child + 1 < _c.size() && _c[child] < _c[child + 1])
			if (child + 1 < _c.size() && _cmp(_c[child], _c[child + 1]))
				child++;

			//如果父亲小于孩子
			//if (_c[parent] < _c[child]) {
			if (_cmp(_c[parent], _c[child])) {
				swap(_c[child], _c[parent]);
				//更新
				parent = child;
				child = 2 * parent + 1;
			}
			else
				break;
		}
	}

	//获取堆顶元素
	T& top() {
		return _c.front();
	}

	//判空
	bool empty() {
		return _c.empty();
	}

	//获取size
	size_t size() {
		return _c.size();
	}


private:
	Container _c;
	Compare _cmp;
};


void test() {
	//大堆
	//优先级队列的默认容器是vector -->(随机访问效率高)
	//PriorityQueue<int, vector<int>, less<int>> pq;
	//PriorityQueue<int, deque<int>> pq;

	PriorityQueue<int, vector<int>, Less<int>> pq;


	//list不能作为底层容器, 因为不支持随机访问
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


//自定义类型要自己实现大于小于逻辑 ---> 重载 > , < 运算符

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