#include<iostream>

using namespace std;


//���
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

	//��װһ�����
	Node* _node;

	ListIterator(Node* node)
		:_node(node)
	{}

	//�õ���������֧�ֽ����ò���, ��Ҫ������������������
	//������:  *it ---> ��ȡ��������value
	Ref operator*() {
		return _node->_data;
	}


	// ++ :  �ƶ�����һ������λ�� 
	Self& operator++() {
		//�ƶ�����һ��Ԫ�ص�λ��
		_node = _node->_next;
		return *this;
	}

	//����++
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
	

	// != :  �ж���������val�Ƿ���ͬ 
	bool operator!=(const Self& it) {
		//�ж��������ݵ�λ���Ƿ���ͬ
		return _node != it._node;
	}

	bool operator==(const Self& it) {
		return _node == it._node;
	}


	//-> : �����Զ������͵ĳ�Ա
	//��Ŀ�����, �������ݵ�ָ�뼴��
	Ptr operator->() {
		return &_node->_data;
	}

};


template <class T>
class List {
public:
	typedef ListNode<T> Node;

	List() {
		//�յĴ�ͷ˫��ѭ������
		_header = new Node;
		_header->_next = _header->_prev = _header;
	}


	//��������
	List(const List<T>& lst) {
		//���
		_header = new Node;
		_header->_next = _header->_prev = _header;

		//����lst�е�ÿ������
		for (const auto& e : lst)
			push_back(e);
	}


	//��ֵ
	//List<T>& operator= (const List<T>& lst) {
	//	if (this != &lst) {
	//		//���������
	//		clear();
	//		//�ٲ���
	//		for (consy auto& e : lst)
	//			push_back(e);
	//	}
	//	return *this;
	//}

	//�ִ�д��
	List<T>& operator= (List<T> lst) {
		swap(_header, lst._header);
		return *this;
	}


	//����
	~List() {
		clear();
		delete _header;
	}


	//��ȡsize
	size_t size() {
		size_t cnt = 0;
		auto it = begin();
		while (it != end()) {
			cnt++;
			it++;
		}
		return cnt;
	}

	
	//�п�
	bool empty() {
		return begin() == end();
	}


	//β��
	void push_back(const T& val) {
		Node* cur = new Node(val);
		//��ȡβ���
		Node* tail = _header->_prev;

		//�ı�����
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



	//������:  
	//�·�װ��һ������������, ʵ�ֵ������Ĺ���
	typedef ListIterator<T, T&, T*> iterator;
	typedef ListIterator<T, const T&, const T*> const_iterator;

	iterator begin() {
		//��һ��Ԫ�ص�λ��, ��װ��һ�����
		return iterator(_header->_next);
	}

	iterator end() {
		//���һ��Ԫ�ص���һ��λ��, ��װͷ���
		return iterator(_header);
	}

	const_iterator begin() const {
		return const_iterator(_header->_next);
	}

	const_iterator end() const {
		return const_iterator(_header);
	}


	//��posλ��ǰ����һ��Ԫ��
	void insert(iterator pos, const T& val) {
		//��ȡ��ǰ��㼰��ǰ�����
		Node* cur = pos._node;
		Node* prev = cur->_prev;
		
		//�����µĽ��
		Node* newNode = new Node(val);

		//�ı�����
		prev->_next = newNode;
		newNode->_prev = prev;

		newNode->_next = cur;
		cur->_prev = newNode;
	}

	//ͷ��
	void push_front(const T& val) {
		insert(begin(), val);
	}



	//ɾ��posλ�õ�����, 
	//���ر�ɾ�����ݵ���һ��λ��
	iterator erase(iterator pos) {
		//����ɾ��ͷ���, ��end()������ָ�������
		if (pos != end()) {
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* next = cur->_next;

			prev->_next = next;
			next->_prev = prev;

			delete cur;

			//����ָ����һ�����ĵ�����
			return iterator(next);
		}
		
		return pos;
	}

	//βɾ
	void pop_back() {
		erase(--end());
	}

	//ͷɾ
	void pop_front() {
		erase(begin());
	}


	//���������Ч����
	void clear() {
		Node* cur = _header->_next;
		while (cur != _header) {
			Node* next = cur->_next;
			delete cur;
			cur = next;
		}
		//�ָ�ѭ���ṹ
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
		//�ɶ���д
		*it = 9; 
		++it;
	}
	cout << endl;

	//�ٴα���, ���Ƿ��޸ĳɹ�
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
		//cout << *it << " "; //*it��B����, ����һ����������������
		
		//���������������� -> ������Ϳ��Է��ʵ��Զ������͵ĳ�Ա��
		cout << it->_a << " " << it->_b << endl;

		//������ʽ
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

	//����ͷ���ȫ��ɾ��
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
		cout << "list�ǿյ�" << endl;
	else
		cout << "list���ǿյ�" << endl;


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
		cout << "list�ǿյ�" << endl;
	else
		cout << "list���ǿյ�" << endl;
}


int main() {
	//test();
	//test2();
	test3();

	return 0;
}