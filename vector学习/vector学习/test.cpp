#include<iostream>
#include<vector>

using namespace std;


struct A {
	int _a = 1105;
};

void test() {
	//vector����
	vector<int> v1;
	vector<char> v2;

	vector<int> v3(10, 1); //10��1
	vector<int> copy(v3); //��������


	int arr[] = { 1, 2, 3, 4, 5 };
	vector<int> v4(arr, arr + 5);

	//��ֵ: ���
	v1 = v4;
	//��������
	vector<int> v5 = v4;


	//������
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

	//�Զ�������
	vector<A> v6(5, A());
	vector<A>::iterator it3 = v6.begin();
	while (it3 != v6.end()) {
		cout << (*it3)._a << " ";
		it3++;
	}
	cout << endl;


	//���������
	vector<int>::reverse_iterator rit = v4.rbegin();
	while (rit != v4.rend()) {
		cout << *rit << " ";
		rit++;
	}
	cout << endl;


	//��Χfor
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


	//operator[]Խ��: assert����
	//at() Խ��: �쳣
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
	//vector����: PJ�汾: 1.5��    SGI: 2��
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


	//resize(n): n > size ��[size, n) ��Ĭ��ֵ:  0  '\0'  nullptr  �Զ������͵�Ĭ�Ϲ���
	//ԭ��: �������ͳ�ʼ��Ϊ���Ͷ�Ӧ��0, �Զ������͵�Ĭ�Ϲ���
	v.resize(5);

	vector<char> v2;
	v2.resize(5);

	vector<int*> v3;
	v3.resize(5);

	vector<A> v4;
	v4.resize(5);


	//resize(n, val) : һ��Ӱ��size: size = n
	// n > capacity ����
	//�� n > sizeʱval����Ч
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

	//reserve: ����Ӱ��size
	v.reserve(100);
	cout << "cap: " << v.capacity() << endl;

	//vector��reserveֻ������, �����С����
	v.reserve(10);
	cout << "cap: " << v.capacity() << endl;

	v.resize(35);
	//��С����, �ö���ʣ����
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


	//insert() λ�ñ����ɵ�����ָ��
	v = { 1, 2, 3 , 4 };
	v.insert(v.end(), 5);		 // 1 2 3 4 5
	v.insert(v.begin(), 0);		 // 0 1 2 3 4 5
	v.insert(v.begin() + 2, 10); // 0 1 10 2 3 4 5
	v.insert(v.end() - 1, 20);	 // 0 1 10 2 3 4 20 5

	v.insert(v.begin(), 3, -1);  //ͷ��3��-1

	vector<int> v2(3, 9);
	//ͷ��һ��v2������[begin, end)
	v.insert(v.begin(), v2.begin(), v2.end());// 9 9 9 ~

	//����������: ����ҿ�
	//����������: ��һ����vector������, 
	//ֻҪ�����������ú����ͺ�vector�������һ�¼���  (������һ����Ȼ�ĵ�����)
	int arr[] = { 5, 5, 5 };
	v.insert(v.end(), arr, arr + 2); // ~ 5 5  


	//erase ɾ��
	v = { 0, 1, 2, 3, 4, 5, 6, 7, 8 ,9 };
	v.erase(v.begin()); //ͷɾ  1 ~ 9
	v.erase(v.end() - 1); // βɾ  endλ��û��Ԫ�� 1 ~ 8
	v.erase(v.begin() + 1, v.end() - 1);// ֻʣͷβԪ�� 1 8

}


/*
	������ʧЧ:
		1.���������仯
		2. ����ɾ������
	���: ���»�ȡ������
*/
void test6() {
	//������ʧЧ
	//���������仯֮��, ���ܻ�����, ������ָ���ԭʼ�ռ䱻�ͷ�, ���·���Խ��

	vector<int> v;
	v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	vector<int>::iterator it = v.begin();
	cout << *it << endl;

	//1. ���뵼��
	for (int i = 0; i < 10; i++) {
		v.push_back(i);
		cout << *it << " ";  //����֮����ܻ�����, ����ʧЧ
	}
	cout << endl;

	//2.
	v.clear();
	it = v.begin();

	v.insert(it, 0);     //����û����
	cout << *it << endl; //����ռ��Ѿ�û��..

	//3. resize
	v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	it = v.begin();

	v.resize(5);
	cout << *it << endl; //��С����, û����

	v.resize(9);
	cout << *it << endl; // û����cap, ������, û����

	v.resize(10);
	cout << *it << endl; //����, ������ʧЧ

	//4. reserve
	v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	it = v.begin();

	v.reserve(5);
	cout << *it << endl; //�����С����, û����

	v.reserve(50);
	cout << *it << endl; // ����, ʧЧ

	//5. ɾ������
	v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	it = v.end() - 1; // ָ��9

	v.erase(it);
	cout << *it << endl; //λ��Խ��

	//6.
	v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	it = v.begin(); // ָ��1

	v.erase(it);
	cout << *it << endl; //λ�ô�λ, Ҳ��������� (PJ��)

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

	//����ֱ�Ӵ��Զ������͹��캯����Ҫ�Ĳ���, emplace�ڲ�ֱ�Ӵ�������
	v.emplace(v.begin(), 7, 8);
	//v.insert(v.begin(), 9, 10);   //�������

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