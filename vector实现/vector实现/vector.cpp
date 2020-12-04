#include<iostream>
#include<vector>
#include<string>
#include<assert.h>

using namespace std;


template <class T>
class Vector {
public:
	//构造函数
	Vector()
		: _start(nullptr)
		, _finish(nullptr)
		, _endofstorage(nullptr)
	{}


	//拷贝构造
	Vector(const Vector& v)
		: _start(nullptr)
		, _finish(nullptr)
		, _endofstorage(nullptr)
	{
		//开好空间
		reserve(v.capacity());
		iterator it = begin();
		const_iterator vit = v.begin();
		//遍历赋值
		while (vit != v.end()) {
			*it = *vit;
			it++;
			vit++;
		}
		//修改_finish指针
		_finish += v.size();
	}


	//交换函数
	void Swap(Vector<T> v) {
		swap(_start, v._start);
		swap(_finish, v._finish);
		swap(_endofstorage, v._endofstorage);
	}

	//赋值运算符
	Vector<T>& operator=(Vector<T> v) {
		Swap(v);
		return *this;
	}


	//获取size
	size_t size() const {
		return _finish - _start;
	}


	//获取容量capacity
	size_t capacity() const {
		return _endofstorage - _start;
	}


	//增容
	void reserve(size_t n) {
		if (n > capacity()) {
			//保存size
			size_t sz = size();

			//1. 开空间
			T* tmp = new T[n];
			
			//2. 内容拷贝

			//memcpy为内存拷贝, 是浅拷贝, 遇到有资源的类型会发生问题
			//memcpy(tmp, _start, sizeof(T) * size());

			//执行T类型的赋值操作, 进行深拷贝
			for (int i = 0; i < sz; ++i) {
				tmp[i] = _start[i];
			}

			//3. 释放原有空间
			delete[] _start;

			//4. 更新成员变量
			_start = tmp;
			_endofstorage = _start + n;
			_finish = _start + sz;
		}
	}


	//尾插
	void push_back(const T& val) {
		//1. 检查容量
		if (_finish == _endofstorage) {
			//判断是否是空的vector
			size_t newCap = _start == nullptr ? 1 : 2 * capacity();
			reserve(newCap);
		}

		//2. 尾插
		*_finish = val;

		//3.更新size
		_finish++;
	}


	//operator[]   获取pos位置元素
	T& operator[](size_t pos) {
		assert(pos < size());
		return _start[pos];
	}

	// [] const接口
	const T& operator[](size_t pos) const {
		assert(pos < size());
		return _start[pos];
	}



	//Vector迭代器:  T*
	typedef T* iterator;
	typedef const T* const_iterator;


	iterator begin() {
		return _start;
	}

	iterator end() {
		return _finish;
	}

	const_iterator begin() const {
		return _start;
	}

	const_iterator end() const {
		return _finish;
	}

	
	//设置size
	void resize(size_t n, const T& val = T()) {
		//增容
		if (n > capacity()) {
			reserve(n);
		}

		//给新的位置赋值 [size, n)
		if (n > size()) {
			iterator it = end();
			while (it != _start + n) {
				*it = val;
				++it;
			}
		}

		//修改size
		_finish = _start + n;
	}


	//插入  在pos位置插入一个元素
	void insert(iterator pos, const T& val) {
		assert(pos >= begin() && pos <= end());

		//获取pos 和 begin的偏移量
		int offset = pos - _start;

		//检查容量
		if (_finish == _endofstorage) {
			size_t newCap = (_start == nullptr) ? 1 : 2 * capacity();
			reserve(newCap);
		}
		
		//增容后, 原有空间被释放, pos迭代器失效, 需要更新pos的位置
		pos = _start + offset;

		//元素移动 --- 从后向前
		iterator it = end();
		while (it != pos) {
			*it = *(it - 1);
			--it;
		}

		//插入
		*pos = val;

		//更新size
		++_finish;
	}


	//删除   
	iterator erase(iterator pos) {
		assert(pos >= begin() && pos < end());

		//移动元素 --- 从前向后
		iterator it = pos + 1;
		while (it != end()) {
			*(it - 1) = *it;
			//*it = *(it + 1);  错误的, 因为end()位置不是有效位置, 没有元素
			++it;
		}

		//更新size
		--_finish;

		//返回被删除元素的下一个位置, 即pos的位置 (被删除的下一个位置移到pos这了)
		return pos;
	}

	void pop_back() {
		erase(end() - 1);
	}


	//析构
	~Vector() {
		if (_start) {
			delete[] _start;
			_start = _finish = _endofstorage = nullptr;
		}
	}

private:
	T* _start;		//start: 首元素地址
	T* _finish;		//finish: 最后一个元素的下一个位置
	T* _endofstorage;	//endofstorage: 整个空间的尾地址
};



void test() {
	Vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);


	Vector<int> v2(v);
	v2.pop_back();
	Vector<int> v3;
	v3 = v2;
	v3.pop_back();

	//[]遍历
	cout << "operator[]: " << endl;
	for (size_t i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
		//可以修改
		v[i] = 10;
	}
	cout << endl;

	
	for (size_t i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;

	//迭代器
	cout << "iterator: " << endl;
	Vector<int>::iterator it = v.begin();
	while (it != v.end()) {
		cout << *it << " ";
		*it = 5;
		it++;
	}
	cout << endl;

	it = v.begin();
	while (it != v.end()) {
		cout << *it << " ";
		it++;
	}
	cout << endl;

	//范围for
	cout << "范围for: " << endl;
	for (auto& e : v) {
		cout << e << " ";
		e = 7;
	}
	cout << endl;

	for (const auto& e : v) {
		cout << e << " ";
	}
	cout << endl;
}

template <class T>
void printV(const Vector<T>& v) {
	for (const auto& e : v) {
		cout << e << " ";
	}
	cout << endl;
}

void test2() {
	Vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);

	printV(v);
	v.resize(9);
	printV(v);
	v.resize(4, 20);
	printV(v);
	v.resize(6, 30);
	printV(v);
}


void test3() {
	Vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	
	v.insert(v.end(), 4);
	v.insert(v.begin(), 0);

	printV(v);
}


void test4() {
	Vector<int> v;
	v.push_back(1);
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(1);
	v.push_back(1);
	v.push_back(1);
	printV(v);

	//删除所有的1
	Vector<int>::iterator it = v.begin();
	while (it != v.end()) {
		//删除之后, 要从新获取erase接口的返回值, 让it更新到被删除元素的下一个位置
		if (*it == 1)
			it = v.erase(it);
		else
			++it;
	}
	printV(v);
}


void test5() {
	Vector<string> v;
	v.push_back("123");
	v.push_back("456");
	v.push_back("78");
	v.push_back("9");

	printV(v);
}




int main() {
	//test();
	//test2();
	//test3();
	//test4();
	test5();

	return 0;
}