#include<iostream>

using namespace std;


//结点
template <class T>
struct ListNode {
	T _data;
	ListNode<T>* _next;
	ListNode<T>* _prev;

	ListNode(const T& val = T()) 
		:_data(val)
		,_next(nullptr)
		,_prev(nullptr)
	{}
};


template <class T, class Ref, class Ptr>
struct ListIterator {
	typedef ListNode<T> Node;
	typedef ListIterator<T, Ref, Ptr> Self;

	//封装一个结点
	Node* _node;

	ListIterator(Node* node)
		:_node(node)
	{}

	//让迭代器类型支持解引用操作, 就要对相关运算符进行重载
	//解引用:  *it ---> 获取结点的数据value
	Ref operator*() {
		return _node->_data;
	}


	// ++ :  移动到下一个结点的位置 
	Self& operator++() {
		//移动到下一个元素的位置
		_node = _node->_next;
		return *this;
	}

	//后置++
	Self operator++(int) {
		Self tmp(*this);
		_node = _node->_next;
		return tmp;
	}


	// --
	Self& operator--() {
		_node = _node->_prev;
		return *this;
	}

	Self operator--(int) {
		Self tmp(*this);
		_node = _node->_prev;
		return tmp;
	}
	

	// != :  判断两个结点的val是否相同 
	bool operator!=(const Self& it) {
		//判断两个数据的位置是否相同
		return _node != it._node;
	}

	bool operator==(const Self& it) {
		return _node == it._node;
	}


	//-> : 访问自定义类型的成员
	//单目运算符, 返回数据的指针即可
	Ptr operator->() {
		return &_node->_data;
	}

};


template <class T>
class List {
public:
	typedef ListNode<T> Node;

	List() {
		//空的带头双向循环链表
		_header = new Node;
		_header->_next = _header->_prev = _header;
	}


	//拷贝构造
	List(const List<T>& lst) {
		//深拷贝
		_header = new Node;
		_header->_next = _header->_prev = _header;

		//插入lst中的每个数据
		for (const auto& e : lst)
			push_back(e);
	}


	//赋值
	//List<T>& operator= (const List<T>& lst) {
	//	if (this != &lst) {
	//		//先清空数据
	//		clear();
	//		//再插入
	//		for (consy auto& e : lst)
	//			push_back(e);
	//	}
	//	return *this;
	//}

	//现代写法
	List<T>& operator= (List<T> lst) {
		swap(_header, lst._header);
		return *this;
	}


	//析构
	~List() {
		clear();
		delete _header;
	}


	//获取size
	size_t size() {
		size_t cnt = 0;
		auto it = begin();
		while (it != end()) {
			cnt++;
			it++;
		}
		return cnt;
	}

	
	//判空
	bool empty() {
		return begin() == end();
	}


	//尾插
	void push_back(const T& val) {
		Node* cur = new Node(val);
		//获取尾结点
		Node* tail = _header->_prev;

		//改变链接
		tail->_next = cur;
		cur->_prev = tail;

		cur->_next = _header;
		_header->_prev = cur;
	}


	void print() {
		Node* cur = _header->_next;
		while (cur != _header) {
			cout << cur->_data << " ";
			cur = cur->_next;
		}
		cout << endl;
	}



	//迭代器:  
	//新封装了一个迭代器类型, 实现迭代器的功能
	typedef ListIterator<T, T&, T*> iterator;
	typedef ListIterator<T, const T&, const T*> const_iterator;

	iterator begin() {
		//第一个元素的位置, 封装第一个结点
		return iterator(_header->_next);
	}

	iterator end() {
		//最后一个元素的下一个位置, 封装头结点
		return iterator(_header);
	}

	const_iterator begin() const {
		return const_iterator(_header->_next);
	}

	const_iterator end() const {
		return const_iterator(_header);
	}


	//在pos位置前插入一个元素
	void insert(iterator pos, const T& val) {
		//获取当前结点及其前驱结点
		Node* cur = pos._node;
		Node* prev = cur->_prev;
		
		//创建新的结点
		Node* newNode = new Node(val);

		//改变链接
		prev->_next = newNode;
		newNode->_prev = prev;

		newNode->_next = cur;
		cur->_prev = newNode;
	}

	//头插
	void push_front(const T& val) {
		insert(begin(), val);
	}



	//删除pos位置的数据, 
	//返回被删除数据的下一个位置
	iterator erase(iterator pos) {
		//不能删除头结点, 即end()迭代器指向的数据
		if (pos != end()) {
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* next = cur->_next;

			prev->_next = next;
			next->_prev = prev;

			delete cur;

			//创建指向下一个结点的迭代器
			return iterator(next);
		}
		
		return pos;
	}

	//尾删
	void pop_back() {
		erase(--end());
	}

	//头删
	void pop_front() {
		erase(begin());
	}


	//清空所有有效数据
	void clear() {
		Node* cur = _header->_next;
		while (cur != _header) {
			Node* next = cur->_next;
			delete cur;
			cur = next;
		}
		//恢复循环结构
		_header->_next = _header->_prev = _header;
	}

private:
	Node* _header;
};
   

template <class T>
void printList(const List<T>& lst) {
	auto cit = lst.begin();
	while (cit != lst.end()) {
		cout << *cit << " ";
		cit++;
	}
	cout << endl;
}

template <class T>
void printFor(const List<T>& lst) {
	for (const auto e : lst) {
		cout << e << " ";
	}
	cout << endl;
}


void test() {
	List<int> lst;
	lst.push_back(1);
	lst.push_back(2);
	lst.push_back(3);
	lst.push_back(5);
	lst.push_back(4);


	lst.print();

	List<int>::iterator it = lst.begin();
	while (it != lst.end()) {
		cout << *it << " ";
		//可读可写
		*it = 9; 
		++it;
	}
	cout << endl;

	//再次遍历, 看是否修改成功
	it = lst.begin();
	while (it != lst.end()) {
		cout << *it << " ";
		++it;
	}
	cout << endl;
}



class B {
public:
	B(int a = 0, int b = 0)
		:_a(a)
		,_b(b)
	{}

	int _a;
	int _b;
};


void test2() {
	List<B> lst;
	lst.push_back(B(1, 2));
	lst.push_back(B(3, 4));
	lst.push_back(B(5, 6));

	B* pb = new B(7, 8);
	cout << pb->_a << " " << pb->_b << endl;

	List<B>::iterator it = lst.begin();
	while (it != lst.end()) {
		//cout << *it << " "; //*it是B类型, 他不一定重载了输出运算符
		
		//所以我们这里重载 -> 运算符就可以访问到自定义类型的成员了
		cout << it->_a << " " << it->_b << endl;

		//完整形式
		cout << it.operator->()->_a << " " << it.operator->()->_b << endl;
		it++;
	}

}


void test3() {
	List<int> lst;
	lst.push_back(1);
	lst.push_back(2);
	lst.push_back(3);
	lst.push_back(4);

	cout << lst.size() << endl;

	printList(lst);
	printFor(lst);

	lst.insert(++lst.begin(), 9);
	printFor(lst);

	lst.erase(--lst.end());
	printFor(lst);

	//除了头结点全部删除
	auto it = lst.begin();
	while (it != lst.end()) {
		cout << *it << " ";
		it = lst.erase(it);
	}
	cout << endl;

	printFor(lst);
	printFor(lst);
	printFor(lst);

	if (lst.empty())
		cout << "list是空的" << endl;
	else
		cout << "list不是空的" << endl;


	lst.push_back(1);
	lst.push_back(2);
	lst.push_back(3);
	lst.push_back(4);

	printFor(lst);

	lst.pop_back();
	printFor(lst);
	lst.pop_front();
	printFor(lst);

	cout << lst.size() << endl;

	if (lst.empty())
		cout << "list是空的" << endl;
	else
		cout << "list不是空的" << endl;
}


int main() {
	//test();
	//test2();
	test3();

	return 0;
}