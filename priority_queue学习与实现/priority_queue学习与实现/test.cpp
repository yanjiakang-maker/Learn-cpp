#include<iostream>
#include<queue>
#include<functional>

using namespace std;


void test1() {
	//默认大堆
	//priority_queue<int> pq;

	//建小堆
	priority_queue<int, vector<int>, greater<int>> pq;
	pq.push(1);
	pq.push(12);
	pq.push(3);
	pq.push(16);
	pq.push(30);
	
	while (!pq.empty()) {
		//获取堆顶元素
		cout << pq.top() << " ";
		//删除堆顶元素
		pq.pop();
	}
	cout << endl;
}


struct Time {
	Time(int h = 0, int m = 0, int s = 0)
		:_h(h)
		,_m(m)
		,_s(s)
	{}

	int _h;
	int _m;
	int _s;

	// < 重载
	bool operator<(const Time& t) const {
		if (_h < t._h)
			return true;
		else if (_h == t._h) {
			if (_m < t._m)
				return true;
			else if (_m == t._m) {
				if (_s < t._s)
					return true;
			}
		}
		return false;
	}

	bool operator==(const Time& t) const {
		return _h == t._h && _m == t._m
			&& _s == t._s;
	}

	bool operator> (const Time& t) const {
		return !(*this < t || *this == t);
	}
};
ostream& operator<< (ostream& cout, const Time& t) {
	cout << t._h << ":" << t._m << ":" << t._s << endl;
	return cout;
}


void test2() {
	//存放自定义类型
	//建大堆: 要重载 < 运算符
	//priority_queue<Time> pq;
	
	//建小堆, 要重载 >
	priority_queue<Time, vector<Time>, less<Time>> pq;

	pq.push(Time(20, 50, 20));
	pq.push(Time(15, 30, 50));
	pq.push(Time(24, 0, 0));
	pq.push(Time(6, 50, 0));

	while (!pq.empty()) {
		cout << pq.top();
		pq.pop();
	}
}


//int main() {
//	//test1();
//	test2();
//
//	return 0;
//}