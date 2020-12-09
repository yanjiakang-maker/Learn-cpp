#include<iostream>
#include<vector>
#include<list>

using namespace std;


//栈没有迭代器, 不能进行遍历
//template <class T>
//class Stack {
//public:
//	//构造函数不用写
//
//
//	//入栈
//	void push(const T& val) {
//		_v.push_back(val);
//	}
//
//	//出栈
//	void pop() {
//		_v.pop_back();
//	}
//
//	//获取栈顶元素
//	T& top() {
//		return _v.back();
//	}
//
//	//判空
//	bool empty() {
//		return _v.empty();
//	}
//
//	//size
//	size_t size() {
//		return _v.size();
//	}
//
//private:
//	vector<T> _v;
//};



template <class T, class Container>
class Stack {
public:
	//构造函数不用写


	//入栈
	void push(const T& val) {
		_v.push_back(val);
	}

	//出栈
	void pop() {
		_v.pop_back();
	}

	//获取栈顶元素
	T& top() {
		return _v.back();
	}

	//判空
	bool empty() {
		return _v.empty();
	}

	//size
	size_t size() {
		return _v.size();
	}

private:
	Container _v;
};



//void test() {
//	Stack<int> st;
//	st.push(1);
//	st.push(2);
//	st.push(3);
//	st.push(5);
//	st.push(4);
//
//	while (!st.empty()) {
//		cout << st.top() << " ";
//		st.pop();
//	}
//	cout << endl;
//}


//void test2() {
//	Stack<int, vector<int>> st;
//	Stack<int, list<int>> st2;
//
//	st.push(1);
//	st.push(2);
//	st.push(3);
//	st.push(4);
//
//	st2.push(1);
//	st2.push(2);
//	st2.push(3);
//	st2.push(4);
//	  
//	while (!st.empty()) {
//		cout << st.top() << " ";
//		st.pop();
//	}
//	cout << endl;
//
//
//	while (!st2.empty()) {
//		cout << st2.top() << " ";
//		st2.pop();
//	}
//	cout << endl;
//}
//
//
//int main() {
//	//test();
//	test2();
//
//	return 0;
//}