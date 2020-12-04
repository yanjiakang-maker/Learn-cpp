#include<iostream>
#include<vector>
#include<string>
#include<assert.h>

using namespace std;


template <class T>
class Vector {
public:
	//���캯��
	Vector()
		: _start(nullptr)
		, _finish(nullptr)
		, _endofstorage(nullptr)
	{}


	//��������
	Vector(const Vector& v)
		: _start(nullptr)
		, _finish(nullptr)
		, _endofstorage(nullptr)
	{
		//���ÿռ�
		reserve(v.capacity());
		iterator it = begin();
		const_iterator vit = v.begin();
		//������ֵ
		while (vit != v.end()) {
			*it = *vit;
			it++;
			vit++;
		}
		//�޸�_finishָ��
		_finish += v.size();
	}


	//��������
	void Swap(Vector<T> v) {
		swap(_start, v._start);
		swap(_finish, v._finish);
		swap(_endofstorage, v._endofstorage);
	}

	//��ֵ�����
	Vector<T>& operator=(Vector<T> v) {
		Swap(v);
		return *this;
	}


	//��ȡsize
	size_t size() const {
		return _finish - _start;
	}


	//��ȡ����capacity
	size_t capacity() const {
		return _endofstorage - _start;
	}


	//����
	void reserve(size_t n) {
		if (n > capacity()) {
			//����size
			size_t sz = size();

			//1. ���ռ�
			T* tmp = new T[n];
			
			//2. ���ݿ���

			//memcpyΪ�ڴ濽��, ��ǳ����, ��������Դ�����ͻᷢ������
			//memcpy(tmp, _start, sizeof(T) * size());

			//ִ��T���͵ĸ�ֵ����, �������
			for (int i = 0; i < sz; ++i) {
				tmp[i] = _start[i];
			}

			//3. �ͷ�ԭ�пռ�
			delete[] _start;

			//4. ���³�Ա����
			_start = tmp;
			_endofstorage = _start + n;
			_finish = _start + sz;
		}
	}


	//β��
	void push_back(const T& val) {
		//1. �������
		if (_finish == _endofstorage) {
			//�ж��Ƿ��ǿյ�vector
			size_t newCap = _start == nullptr ? 1 : 2 * capacity();
			reserve(newCap);
		}

		//2. β��
		*_finish = val;

		//3.����size
		_finish++;
	}


	//operator[]   ��ȡposλ��Ԫ��
	T& operator[](size_t pos) {
		assert(pos < size());
		return _start[pos];
	}

	// [] const�ӿ�
	const T& operator[](size_t pos) const {
		assert(pos < size());
		return _start[pos];
	}



	//Vector������:  T*
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

	
	//����size
	void resize(size_t n, const T& val = T()) {
		//����
		if (n > capacity()) {
			reserve(n);
		}

		//���µ�λ�ø�ֵ [size, n)
		if (n > size()) {
			iterator it = end();
			while (it != _start + n) {
				*it = val;
				++it;
			}
		}

		//�޸�size
		_finish = _start + n;
	}


	//����  ��posλ�ò���һ��Ԫ��
	void insert(iterator pos, const T& val) {
		assert(pos >= begin() && pos <= end());

		//��ȡpos �� begin��ƫ����
		int offset = pos - _start;

		//�������
		if (_finish == _endofstorage) {
			size_t newCap = (_start == nullptr) ? 1 : 2 * capacity();
			reserve(newCap);
		}
		
		//���ݺ�, ԭ�пռ䱻�ͷ�, pos������ʧЧ, ��Ҫ����pos��λ��
		pos = _start + offset;

		//Ԫ���ƶ� --- �Ӻ���ǰ
		iterator it = end();
		while (it != pos) {
			*it = *(it - 1);
			--it;
		}

		//����
		*pos = val;

		//����size
		++_finish;
	}


	//ɾ��   
	iterator erase(iterator pos) {
		assert(pos >= begin() && pos < end());

		//�ƶ�Ԫ�� --- ��ǰ���
		iterator it = pos + 1;
		while (it != end()) {
			*(it - 1) = *it;
			//*it = *(it + 1);  �����, ��Ϊend()λ�ò�����Чλ��, û��Ԫ��
			++it;
		}

		//����size
		--_finish;

		//���ر�ɾ��Ԫ�ص���һ��λ��, ��pos��λ�� (��ɾ������һ��λ���Ƶ�pos����)
		return pos;
	}

	void pop_back() {
		erase(end() - 1);
	}


	//����
	~Vector() {
		if (_start) {
			delete[] _start;
			_start = _finish = _endofstorage = nullptr;
		}
	}

private:
	T* _start;		//start: ��Ԫ�ص�ַ
	T* _finish;		//finish: ���һ��Ԫ�ص���һ��λ��
	T* _endofstorage;	//endofstorage: �����ռ��β��ַ
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

	//[]����
	cout << "operator[]: " << endl;
	for (size_t i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
		//�����޸�
		v[i] = 10;
	}
	cout << endl;

	
	for (size_t i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << endl;

	//������
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

	//��Χfor
	cout << "��Χfor: " << endl;
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

	//ɾ�����е�1
	Vector<int>::iterator it = v.begin();
	while (it != v.end()) {
		//ɾ��֮��, Ҫ���»�ȡerase�ӿڵķ���ֵ, ��it���µ���ɾ��Ԫ�ص���һ��λ��
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