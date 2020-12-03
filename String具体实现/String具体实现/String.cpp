#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<assert.h>

using namespace std;


class String {
public:
	//ȫȱʡ�Ĺ��캯��
	String(const char* str = "") 
		:_ptr(new char[strlen(str) + 1])
		,_size(strlen(str))
		,_capacity(_size)
	{
		strcpy(_ptr, str);
	}


	//��������
	void Swap(String& str) {
		swap(_ptr, str._ptr);
		swap(_size, str._size);
		swap(_capacity, str._capacity);
	}

	//��������
	//��ͳд��
	//String(const String& str)
	//	:_ptr(new char[strlen(str._ptr) + 1])
	//	,_size(str._size)
	//	,_capacity(str._capacity)
	//{
	//	//����
	//	strcpy(_ptr, str._ptr);
	//}

	//�ִ�д��
	String(const String& str)
		:_ptr(nullptr)  //����ָ��һ��Ҫ��ʼ��, ���򽻻����ͷŵ�ʱ��ռ�������
		, _size(0)
		, _capacity(0)
	{
		String tmp(str._ptr);
		Swap(tmp);
	}

	//��ֵ
	//��ͳд��
	//String& operator=(const String& str) {
	//	if (this != &str) {
	//		//���ռ�, ����, �ͷ�ԭ�пռ�
	//		char* tmp = new char[strlen(str._ptr) + 1];
	//		strcpy(tmp, str._ptr);
	//		delete[] _ptr;

	//		//ָ���µĿռ�, ������size��cap
	//		_ptr = tmp;
	//		_size = str._size;
	//		_capacity = str._capacity;
	//	}
	//	return *this;
	//}


	//�ִ�д��
	String& operator=(String str) {
		Swap(str);
		return *this;
	}


	//����
	~String() {
		if (_ptr) {
			delete[] _ptr;
			_ptr = nullptr;
			_size = _capacity = 0;
		}
	}


	//����, ��ʵ������
	void reserve(size_t n) {
		if (n > _capacity) {
			//���ռ�, ����
			//�����޷���֤_capacity��n�ľ����С��ϵ, ����ֱ�ӿ���n���ռ伴��
			char* tmp = new char[n + 1];
			//strcpy(tmp, _ptr);
			//strcpy ����'\0'�ͻ�ֹͣ, ���ܳ���bug, ����ֱ��ѭ������
			for (int i = 0; i < _size; i++) {
				tmp[i] = _ptr[i];
			}

			//�ͷſռ�, �ı�ָ��, ��������
			delete[] _ptr;
			_ptr = tmp;
			_capacity = n;
		}
	}


	//β���ַ�
	void push_back(const char ch) {
		if (_size == _capacity) {
			//����
			//����ǿյĻ�, ����ֵΪ15(ģ����е�string), ������2������
			size_t newCap = _capacity == 0 ? 15 : 2 * _capacity;
			reserve(newCap);
		}
		//β��
		_ptr[_size++] = ch;
		//���һ����Ҫ���˲�һ��'\0'~
		_ptr[_size] = '\0';
	}

	//β���ַ��� append
	void append(const char* str) {
		//��ȡ�ַ�������
		size_t len = strlen(str);
		//�ж�����
		if (_size + len > _capacity) {
			//ֱ�����ݵ�_size + len, ��Ϊ�޷�ȷ��_size + len�ж��
			reserve(_size + len);
		}

		//β���ַ���, �����str��'\0'Ҳ����������
		strcpy(_ptr + _size, str);
		_size += len;
	}

	//+=��������غ���
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


	//����λ�ò���
	void insert(size_t pos, const char& ch) {
		assert(pos < _size);

		//�ж����� 
		if (_size == _capacity) {
			size_t newCap = _capacity == 0 ? 15 : 2 * _capacity;
			reserve(newCap);
		}
		//�ƶ�Ԫ�� --> �Ӻ���ǰ, ��Ȼ�Ḳ��
		size_t end = _size;
		while (end > pos) {
			_ptr[end] = _ptr[end - 1];
			--end;
		}

		/*
		�����Ĵ���д��:
			��pos = 0ʱ,����ѭ��, ��Ϊend��size_t����, �޷���, ��Զ���ڵ���0
			while (end >= pos) {
			_ptr[end + 1] = _ptr[end];
			--end;
			}
		*/

		//�������ַ�
		_ptr[pos] = ch;
		//����µĽ�����־
		_ptr[++_size] = '\0';
	}

	void insert(size_t pos, const char* str) {
		assert(pos <= _size);
		int len = strlen(str);
		
		//����
		if (_size + len > _capacity) {
			reserve(_size + len);
		}

		//�ƶ�Ԫ��  
		size_t end = _size + len;
		// end: [pos + len, _size + len]  '\0'Ҳһ���ƶ���ĩβ��
		while (end >= pos + len) {
			_ptr[end] = _ptr[end - len];
			--end;
		}

		//�����ַ���
		memcpy(_ptr + pos, str, len * sizeof(char));

		_size += len;
	}


	//ɾ��
	void erase(size_t pos, size_t len) {
		//�ƶ�Ԫ�� ---> ��ǰ����ƶ�, ��Ȼ�Ḳ��
		size_t start = pos + len;
		while (start <= _size) {
			_ptr[start - len] = _ptr[start];
			start++;
		}
		//����_size
		_size -= len;
	}


	//��ȡsize
	int size() const {
		return _size;
	}

	//��ȡcapacity
	size_t capacity() const {
		return _capacity;
	}

	//�п�
	bool empty() const {
		if (_size == 0)
			return true;
		return false;
	}


	//[]����
	//�ɶ���д
	char& operator[](size_t pos) {
		assert(pos < _size);
		return _ptr[pos];
	}

	//ֻ��
	const char& operator[](size_t pos) const {
		assert(pos < _size);
		return _ptr[pos];
	}


	//������: ��������Ԫ�ص�һ�ֻ���
	//������ָ��
	//����: �ƶ�, ������, �ж�
	//������ʵ��: char*
	typedef char* iterator;
	typedef const char* const_iterator;

	//begin: ��һ��Ԫ�ص�λ��
	iterator begin() {
		return _ptr;
	}

	//end: ���һ��Ԫ�ص���һ��λ��
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
	//		1. n <= size: ֻ��Ҫ�޸�size
	//		2. size < n <= capacity: ��ֵch  -->  [size, capacity) , �޸�size
	//		3. n > capacity:  ����, ��ֵ, �޸�size
	void resize(size_t n, char ch = '\0') {
		if (n > _capacity) {
			//����
			reserve(n);
		}
		if (n > _size) {
			//��ֵ
			//Ĭ��Ҫ��ֵ'\0', ���Բ�����strcpy, ֻ�������ֵ������memset (�ֽڿ���)
			memset(_ptr + _size, ch, n - _size);
		}

		//�޸�size
		_size = n;
		_ptr[_size] = '\0';
	}


	//����
	size_t find(const char& ch, size_t pos = 0) {
		for (int i = pos; i < _size; i++) {
			if (_ptr[i] == ch) {
				//�ҵ���
				return i;
			}
		}
		//û�ҵ�
		return npos;
	}

	size_t find(const char* str, size_t pos = 0) {
		char* start = strstr(_ptr + pos, str);
		if (start) {
			//�ҵ���, ����ƫ����
			return start - _ptr;
		}
		//û�ҵ�
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
	size_t _size; //��Ч�ַ�����
	size_t _capacity; //���Դ�ŵ������Ч�ַ�����
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
	str.clear();//�����
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