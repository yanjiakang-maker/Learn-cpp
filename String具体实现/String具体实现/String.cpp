#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<assert.h>

using namespace std;


class String {
public:
	//全缺省的构造函数
	String(const char* str = "") 
		:_ptr(new char[strlen(str) + 1])
		,_size(strlen(str))
		,_capacity(_size)
	{
		strcpy(_ptr, str);
	}


	//交换函数
	void Swap(String& str) {
		swap(_ptr, str._ptr);
		swap(_size, str._size);
		swap(_capacity, str._capacity);
	}

	//拷贝构造
	//传统写法
	//String(const String& str)
	//	:_ptr(new char[strlen(str._ptr) + 1])
	//	,_size(str._size)
	//	,_capacity(str._capacity)
	//{
	//	//拷贝
	//	strcpy(_ptr, str._ptr);
	//}

	//现代写法
	String(const String& str)
		:_ptr(nullptr)  //这里指针一定要初始化, 否则交换完释放的时候空间有问题
		, _size(0)
		, _capacity(0)
	{
		String tmp(str._ptr);
		Swap(tmp);
	}

	//赋值
	//传统写法
	//String& operator=(const String& str) {
	//	if (this != &str) {
	//		//开空间, 拷贝, 释放原有空间
	//		char* tmp = new char[strlen(str._ptr) + 1];
	//		strcpy(tmp, str._ptr);
	//		delete[] _ptr;

	//		//指向新的空间, 并更新size和cap
	//		_ptr = tmp;
	//		_size = str._size;
	//		_capacity = str._capacity;
	//	}
	//	return *this;
	//}


	//现代写法
	String& operator=(String str) {
		Swap(str);
		return *this;
	}


	//析构
	~String() {
		if (_ptr) {
			delete[] _ptr;
			_ptr = nullptr;
			_size = _capacity = 0;
		}
	}


	//增容, 不实现缩容
	void reserve(size_t n) {
		if (n > _capacity) {
			//开空间, 拷贝
			//这里无法保证_capacity和n的具体大小关系, 所以直接开够n个空间即可
			char* tmp = new char[n + 1];
			//strcpy(tmp, _ptr);
			//strcpy 遇到'\0'就会停止, 可能出现bug, 这里直接循环拷贝
			for (int i = 0; i < _size; i++) {
				tmp[i] = _ptr[i];
			}

			//释放空间, 改变指向, 更新容量
			delete[] _ptr;
			_ptr = tmp;
			_capacity = n;
		}
	}


	//尾插字符
	void push_back(const char ch) {
		if (_size == _capacity) {
			//增容
			//如果是空的话, 给初值为15(模拟库中的string), 否则以2倍增容
			size_t newCap = _capacity == 0 ? 15 : 2 * _capacity;
			reserve(newCap);
		}
		//尾插
		_ptr[_size++] = ch;
		//最后一定不要忘了补一个'\0'~
		_ptr[_size] = '\0';
	}

	//尾插字符串 append
	void append(const char* str) {
		//获取字符串长度
		size_t len = strlen(str);
		//判断增容
		if (_size + len > _capacity) {
			//直接增容到_size + len, 因为无法确定_size + len有多大
			reserve(_size + len);
		}

		//尾插字符串, 这里把str的'\0'也拷贝过来了
		strcpy(_ptr + _size, str);
		_size += len;
	}

	//+=运算符重载函数
	//+= char ch
	String& operator+=(const char ch) {
		push_back(ch);
		return *this;
	}

	//+= char* str
	String& operator+= (const char* str) {
		append(str);
		return *this;
	}

	//+= String
	String& operator+=(const String& str) {
		append(str._ptr);
		return *this;
	}


	//任意位置插入
	void insert(size_t pos, const char& ch) {
		assert(pos < _size);

		//判断增容 
		if (_size == _capacity) {
			size_t newCap = _capacity == 0 ? 15 : 2 * _capacity;
			reserve(newCap);
		}
		//移动元素 --> 从后向前, 不然会覆盖
		size_t end = _size;
		while (end > pos) {
			_ptr[end] = _ptr[end - 1];
			--end;
		}

		/*
		常见的错误写法:
			当pos = 0时,无限循环, 因为end是size_t类型, 无符号, 永远大于等于0
			while (end >= pos) {
			_ptr[end + 1] = _ptr[end];
			--end;
			}
		*/

		//插入新字符
		_ptr[pos] = ch;
		//添加新的结束标志
		_ptr[++_size] = '\0';
	}

	void insert(size_t pos, const char* str) {
		assert(pos <= _size);
		int len = strlen(str);
		
		//增容
		if (_size + len > _capacity) {
			reserve(_size + len);
		}

		//移动元素  
		size_t end = _size + len;
		// end: [pos + len, _size + len]  '\0'也一起移动到末尾了
		while (end >= pos + len) {
			_ptr[end] = _ptr[end - len];
			--end;
		}

		//插入字符串
		memcpy(_ptr + pos, str, len * sizeof(char));

		_size += len;
	}


	//删除
	void erase(size_t pos, size_t len) {
		//移动元素 ---> 从前向后移动, 不然会覆盖
		size_t start = pos + len;
		while (start <= _size) {
			_ptr[start - len] = _ptr[start];
			start++;
		}
		//更新_size
		_size -= len;
	}


	//获取size
	int size() const {
		return _size;
	}

	//获取capacity
	size_t capacity() const {
		return _capacity;
	}

	//判空
	bool empty() const {
		if (_size == 0)
			return true;
		return false;
	}


	//[]重载
	//可读可写
	char& operator[](size_t pos) {
		assert(pos < _size);
		return _ptr[pos];
	}

	//只读
	const char& operator[](size_t pos) const {
		assert(pos < _size);
		return _ptr[pos];
	}


	//迭代器: 访问容器元素的一种机制
	//类似于指针
	//操作: 移动, 解引用, 判断
	//迭代器实现: char*
	typedef char* iterator;
	typedef const char* const_iterator;

	//begin: 第一个元素的位置
	iterator begin() {
		return _ptr;
	}

	//end: 最后一个元素的下一个位置
	iterator end() {
		return _ptr + _size;
	}

	const_iterator begin() const {
		return _ptr;
	}

	const_iterator end() const {
		return _ptr + _size;
	}


	//resize(n, ch) 
	//		1. n <= size: 只需要修改size
	//		2. size < n <= capacity: 赋值ch  -->  [size, capacity) , 修改size
	//		3. n > capacity:  增容, 赋值, 修改size
	void resize(size_t n, char ch = '\0') {
		if (n > _capacity) {
			//增容
			reserve(n);
		}
		if (n > _size) {
			//赋值
			//默认要赋值'\0', 所以不能用strcpy, 只能逐个赋值或者用memset (字节拷贝)
			memset(_ptr + _size, ch, n - _size);
		}

		//修改size
		_size = n;
		_ptr[_size] = '\0';
	}


	//查找
	size_t find(const char& ch, size_t pos = 0) {
		for (int i = pos; i < _size; i++) {
			if (_ptr[i] == ch) {
				//找到了
				return i;
			}
		}
		//没找到
		return npos;
	}

	size_t find(const char* str, size_t pos = 0) {
		char* start = strstr(_ptr + pos, str);
		if (start) {
			//找到了, 返回偏移量
			return start - _ptr;
		}
		//没找到
		return npos;
	}

	const char* c_str() const {
		return _ptr;
	}

	void clear() {
		erase(0, strlen(_ptr));
		_size = 0;
	}


	bool operator<(const String& s) {
		return !(*this >= s);
	}

	bool operator<=(const String& s) {
		return !(*this > s);
	}

	bool operator>(const String& s) {
		if (strcmp(_ptr, s.c_str()) > 0) 
			return true;
		return false;
	}

	bool operator>=(const String& s) {
		return (*this > s) || (*this == s);
	}

	bool operator==(const String& s) {
		if (strcmp(_ptr, s.c_str()) == 0)
			return true;
		return false;
	}

	bool operator!=(const String& s) {
		return !(*this == s);
	}


	friend ostream& operator<<(ostream& _cout, const String& str);
	friend istream& operator>>(istream& _cin, String& str);

private:
	char* _ptr;
	size_t _size; //有效字符个数
	size_t _capacity; //可以存放的最大有效字符个数
	static const size_t npos;
};
const size_t String::npos = -1;


ostream& operator<<(ostream& _cout, const String& str) {
	//_cout << str._ptr;
	for (const auto& ch : str) {
		cout << ch;
	}
	return _cout;
}

istream& operator>>(istream& _cin, String& str) {
	char ch;
	str.clear();//先清空
	while ((ch = getchar()) != EOF) {
		if (ch == '\n')
			break;

		str += ch;
	}
	return _cin;
}


void test() {
	String s = "abcde";
	String s2("xyz");
	s2 = s;
	
	s.clear();
	s.push_back('1');
	s.push_back('2');
	s.push_back('3');

	s.append("abc");

	s2 += '0';
	s2 += "QAQ";
	s2 += s;
}

void test2() {
	string s = "abc";
	cout << s << endl;
	cin >> s;
	cout << s << endl;
}


void test3() {
	String s = "0123456789";
	s.insert(7, 'a');
	s.insert(3, "xyz");
	s.erase(2, 1);

	size_t pos = s.find('4', 0);
	pos = s.find("xyz", 0);
	pos = s.find("aaaaa", 0);
}


void test4() {
	String s = "12345";

	for (int i = 0; i < s.size(); i++) {
		cout << s[i] << " ";
	}
	cout << endl;

	String::iterator it = s.begin();
	while (it != s.end()) {
		cout << *it << " ";
		it++;
	}
	cout << endl;

	for (const auto& ch : s) {
		cout << ch << " ";
	}
	cout << endl;
}


void test5() {
	String s = "123";
	String s2 = "123";
	String s3 = "02";
	String s4 = "9";

	cout << (s == s2) << endl;
	cout << (s != s2) << endl;
	cout << (s > s3) << endl;
	cout << (s <= s4) << endl;
	cout << (s >= s2) << endl;
	cout << (s4 < s2) << endl;

}


int main() {
	//test();
	test2();
	//test3();
	//test4();
	//test5();

	return 0;
}