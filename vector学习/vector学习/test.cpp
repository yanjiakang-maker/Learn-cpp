#include<iostream>
#include<vector>

using namespace std;


struct A {
	int _a = 1105;
};

void test() {
	//vector构造
	vector<int> v1;
	vector<char> v2;

	vector<int> v3(10, 1); //10个1
	vector<int> copy(v3); //拷贝构造


	int arr[] = { 1, 2, 3, 4, 5 };
	vector<int> v4(arr, arr + 5);

	//赋值: 深拷贝
	v1 = v4;
	//拷贝构造
	vector<int> v5 = v4;


	//迭代器
	vector<int>::iterator it = v4.begin();
	while (it != v4.end()) {
		cout << *it << " ";
		it++;
	}
	cout << endl;

	vector<char>::iterator it2 = v2.begin();
	while (it2 != v2.end()) {
		cout << *it2 << " ";
		it2++;
	}
	cout << endl;

	//自定义类型
	vector<A> v6(5, A());
	vector<A>::iterator it3 = v6.begin();
	while (it3 != v6.end()) {
		cout << (*it3)._a << " ";
		it3++;
	}
	cout << endl;


	//反向迭代器
	vector<int>::reverse_iterator rit = v4.rbegin();
	while (rit != v4.rend()) {
		cout << *rit << " ";
		rit++;
	}
	cout << endl;


	//范围for
	for (const auto& val : v4) {
		cout << val << " ";
	}
	cout << endl;

	//operator[]
	for (int i = 0; i < v4.size(); i++) {
		cout << v4.operator[](i) << " ";
		cout << v4[i] << " ";
	}
	cout << endl;


	//operator[]越界: assert错误
	//at() 越界: 异常
	cout << v4[20] << endl;
	cout << v4.at(20) << endl;

}


void test2() {
	vector<int> v(3, 1);
	vector<char> v2(10, 'a');
	vector<A> v3(5, A());

	cout << "v size: " << v.size() << endl;
	cout << "v2 size: " << v2.size() << endl;
	cout << "v3 size: " << v3.size() << endl;

	cout << "v max size: " << v.max_size() << endl;
	cout << "v2 max size: " << v2.max_size() << endl;
	cout << "v3 max size: " << v3.max_size() << endl;
	

	vector<int> v4;
	vector<char> v5;
	cout << v4.capacity() << endl;
	cout << v5.capacity() << endl;

	v4.push_back(1);
	cout << v4.capacity() << endl;
	v4.push_back(2);
	cout << v4.capacity() << endl;
}


void printCap() {
	vector<int> v;
	//vector增容: PJ版本: 1.5倍    SGI: 2倍
	size_t cap = v.capacity();
	cout << "v capacity: " << v.capacity() << endl;
	for (int i = 0; i < 150; i++) {
		v.push_back(i);
		if (cap != v.capacity()) {
			cap = v.capacity();
			cout << v.capacity() << endl;
		}
	}
}


void test3() {
	vector<int> v;

	cout << v.size() << endl;
	cout << v.capacity() << endl;


	//resize(n): n > size 在[size, n) 赋默认值:  0  '\0'  nullptr  自定义类型调默认构造
	//原则: 内置类型初始化为类型对应的0, 自定义类型调默认构造
	v.resize(5);

	vector<char> v2;
	v2.resize(5);

	vector<int*> v3;
	v3.resize(5);

	vector<A> v4;
	v4.resize(5);


	//resize(n, val) : 一定影响size: size = n
	// n > capacity 增容
	//当 n > size时val才有效
	vector<char> v5(10, 'a');
	cout << "size: " << v5.size() << endl;
	cout << "cap: " << v5.capacity() << endl;

	v5.resize(20, 'b');
	cout << "size: " << v5.size() << endl;
	cout << "cap: " << v5.capacity() << endl;

	v5.resize(21, 'c');
	cout << "size: " << v5.size() << endl;
	cout << "cap: " << v5.capacity() << endl;

	v5.resize(5, 'd');
	cout << "size: " << v5.size() << endl;
	cout << "cap: " << v5.capacity() << endl;
}


void test4() {
	vector<int> v;
	cout << "cap: " << v.capacity() << endl;

	//reserve: 不会影响size
	v.reserve(100);
	cout << "cap: " << v.capacity() << endl;

	//vector的reserve只能增容, 不会减小容量
	v.reserve(10);
	cout << "cap: " << v.capacity() << endl;

	v.resize(35);
	//减小容量, 用多少剩多少
	v.shrink_to_fit();
	cout << "cap: " << v.capacity() << endl;

}


void test5() {
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	v.pop_back();
	v.pop_back();
	v.pop_back();


	//insert() 位置必须由迭代器指定
	v = { 1, 2, 3 , 4 };
	v.insert(v.end(), 5);		 // 1 2 3 4 5
	v.insert(v.begin(), 0);		 // 0 1 2 3 4 5
	v.insert(v.begin() + 2, 10); // 0 1 10 2 3 4 5
	v.insert(v.end() - 1, 20);	 // 0 1 10 2 3 4 20 5

	v.insert(v.begin(), 3, -1);  //头插3个-1

	vector<int> v2(3, 9);
	//头插一个v2的区间[begin, end)
	v.insert(v.begin(), v2.begin(), v2.end());// 9 9 9 ~

	//迭代器区间: 左闭右开
	//迭代器类型: 不一定是vector迭代器, 
	//只要迭代器解引用后类型和vector存放类型一致即可  (数组是一个天然的迭代器)
	int arr[] = { 5, 5, 5 };
	v.insert(v.end(), arr, arr + 2); // ~ 5 5  


	//erase 删除
	v = { 0, 1, 2, 3, 4, 5, 6, 7, 8 ,9 };
	v.erase(v.begin()); //头删  1 ~ 9
	v.erase(v.end() - 1); // 尾删  end位置没有元素 1 ~ 8
	v.erase(v.begin() + 1, v.end() - 1);// 只剩头尾元素 1 8

}


/*
	迭代器失效:
		1.容量发生变化
		2. 进行删除操作
	解决: 重新获取迭代器
*/
void test6() {
	//迭代器失效
	//容量发生变化之后, 可能会增容, 迭代器指向的原始空间被释放, 导致访问越界

	vector<int> v;
	v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	vector<int>::iterator it = v.begin();
	cout << *it << endl;

	//1. 插入导致
	for (int i = 0; i < 10; i++) {
		v.push_back(i);
		cout << *it << " ";  //插入之后可能会增容, 导致失效
	}
	cout << endl;

	//2.
	v.clear();
	it = v.begin();

	v.insert(it, 0);     //插入没问题
	cout << *it << endl; //这里空间已经没了..

	//3. resize
	v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	it = v.begin();

	v.resize(5);
	cout << *it << endl; //减小容量, 没问题

	v.resize(9);
	cout << *it << endl; // 没超过cap, 不增容, 没问题

	v.resize(10);
	cout << *it << endl; //增容, 迭代器失效

	//4. reserve
	v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	it = v.begin();

	v.reserve(5);
	cout << *it << endl; //不会减小容量, 没问题

	v.reserve(50);
	cout << *it << endl; // 增容, 失效

	//5. 删除导致
	v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	it = v.end() - 1; // 指向9

	v.erase(it);
	cout << *it << endl; //位置越界

	//6.
	v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	it = v.begin(); // 指向1

	v.erase(it);
	cout << *it << endl; //位置错位, 也不允许访问 (PJ版)

}


void test7() {
	vector<int> v(2, 1);
	vector<int> v2(5, 5);

	v.swap(v2);
	v2.swap(v);
	swap(v, v2);
}


void test8() {
	vector<int> v;
	v.emplace(v.begin(), 1);
	v.insert(v.begin(), 0);

	v.emplace_back(2);
	v.push_back(3);
}

struct B {
	B(int a, int b)
		:_a(a)
		,_b(b)
	{}

	int _a;
	int _b;
};

void test9() {
	vector<B> v;
	v.emplace(v.begin(), B(1, 2));
	v.insert(v.begin(), B(3, 4));

	//可以直接传自定义类型构造函数需要的参数, emplace内部直接创建对象
	v.emplace(v.begin(), 7, 8);
	//v.insert(v.begin(), 9, 10);   //这个不行

	v.emplace_back(10, 11);
}


int main() {
	//test();
	//test2();
	//printCap();
	//test3();
	//test4();
	//test5();
	//test6();

	return 0;
}