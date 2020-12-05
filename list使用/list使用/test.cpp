#include<iostream>
#include<list>

using namespace std;

	//list: ��ͷ˫��ѭ������
	//����������ָ���һ��val


void test() {
	//���캯��
	list<int> lst;
	list<int> lst2(5, 10);  //5��10
	list<int> lst3(lst2.begin(), lst2.end());

	//��������
	list<int> copy(lst3);


	//������
	list<int>::iterator it = lst2.begin();
	while (it != lst2.end()) {
		cout << *it << " ";
		*it = 5;
		++it;
	}
	cout << endl;

	it = lst2.begin();
	while (it != lst2.end()) {
		cout << *it << " ";
		++it;
	}
	cout << endl;
}


void test2() {
	list<int> lst;
	lst.push_back(1);
	lst.push_back(2);
	lst.push_back(3);
	lst.push_back(4);

	list<int>::reverse_iterator rit = lst.rbegin();
	while (rit != lst.rend()) {
		cout << *rit << " ";
		*rit = 5;
		rit++;
	}
	cout << endl;

	list<int>::iterator it = lst.begin();
	while (it != lst.end()) {
		cout << *it << " ";
		it++;
	}
	cout << endl;
}


template <class T>
void printList(const list<T>& lst) {
	for (const auto& e : lst) {
		cout << e << " ";
	}
	cout << endl;
}


void test3() {
	list<int> lst;
	lst.push_back(1);
	lst.push_back(2);
	lst.push_back(3);
	lst.push_back(4);

	printList(lst);

	cout << "size: " << lst.size() << endl;
}


void test4() {
	list<int> lst;

	//ͷ��
	lst.push_front(0);
	lst.emplace_front(-1);

	//β��
	lst.push_back(1);
	lst.emplace_back(2);
	printList(lst);


	int arr[] = { 1, 2, 3 };

	list<int> lst2;
	//assign: ��ֵ
	lst2.assign(arr, arr + 3);
	printList(lst2);

	lst2.assign(3, 5); //3��5
	printList(lst2);

}


void test5() {
	list<int> lst;

	//����insert, �ڵ�����λ�õ�ǰ�����
	lst.insert(lst.begin(), 0); //0
	lst.insert(lst.end(), 1);   //0 1 
	lst.insert(--lst.end(), 2); // 0 2 1

	lst.insert(--lst.end(), 3, 5); // 0 2 5 5 5 1

	int arr[] = { 7, 8 };
	lst.insert(lst.begin(), arr, arr + 2); // 7 8 0 2 5 5 5 1


	list<int>::iterator it = ++lst.begin();
	cout << *it << " ";  //8
	lst.insert(it, 9);  //7 9 8 0 2 5 5 5 1
	cout << *it << endl; //8    
	//list����������ᵼ�µ�����ʧЧ, ֻҪ��ɾ����, �����������һֱָ����


	lst.erase(it); //7 9 0 2 5 5 5 1
	//ɾ������ҿ������Ԫ��
	lst.erase(++lst.begin(), --lst.end()); // 7 1
	//ɾ���ᵼ�µ�����ʧЧ, ��Ϊ����ɾ��ʱ��ɾ��Ԫ�صĿռ䱻�ͷ���
}



void test6() {
	list<int> lst;
	cout << "size: " << lst.size() << endl;

	lst.resize(2);
	cout << "size: " << lst.size() << endl;
	printList(lst); // 0 0

	lst.resize(5, 5);
	cout << "size: " << lst.size() << endl;
	printList(lst); // 0 0 5 5 5


	list<string> lst2;
	lst2.resize(2);
	printList(lst2); // "" ""

	lst2.resize(5, "ab");
	printList(lst2); // "" "" "ab" "ab" "ab"


	lst.clear();
	printList(lst);
}


void test7() {
	list<int> lst;
	list<int> lst2;

	lst.push_back(1);
	lst.push_back(2);
	lst.push_back(3);

	lst2.push_back(4);
	lst2.push_back(5);

	//ƴ��, ���޸Ĵ����list���������
	//ֱ�Ӱ�lis2ƴ�ӵ�lst��, lst2��û��
	lst.splice(lst.begin(), lst2); //lst: 4 5 1 2 3  lst2: ��
	printList(lst);
	printList(lst2);

	//lst2: 4   lst: 5 1 2 3
	lst2.splice(lst2.end(), lst, lst.begin());
	
	//lst2: 4 1 2   lst: 5 3
	lst2.splice(lst2.end(), lst, ++lst.begin(), --lst.end());


	printList(lst2);
	//remove ɾ��ֵ, ���û����������
	lst2.remove(4);
	printList(lst2);

	lst2.remove(100);
	printList(lst2);
}


void test8() {
	list<int> lst;
	lst.push_back(1);
	lst.push_back(2);
	lst.push_back(5);
	lst.push_back(1);
	lst.push_back(1);
	lst.push_back(1);
	lst.push_back(1);

	printList(lst);

	//ȥ��
	//Ҫ��Ԫ������, �������ȥ�ص����� (��Ȼ����̫��)
	lst.sort();
	lst.unique();
	printList(lst);
}


void test9() {
	list<int> lst;
	list<int> lst2;

	lst.push_back(1);
	lst.push_back(2);
	lst.push_back(3);

	lst2.push_back(5);
	lst2.push_back(4);
	lst2.push_back(8);
	lst2.push_back(0);



	//Ҫ�󱻺ϲ���������, �ϲ���֮�󱻺ϲ�����Ϊ��
	lst2.sort();
	lst.merge(lst2);
	printList(lst);
	printList(lst2);


	lst.reverse();
	printList(lst);

}



int main() {
	//test();
	//test2();
	//test3();
	//test4();
	//test5();
	//test6();
	//test7();
	//test8();
	test9();


	return 0;
}