#include<iostream>
#include<list>

using namespace std;

	//list: 带头双向循环链表
	//里面有两个指针和一个val


void test() {
	//构造函数
	list<int> lst;
	list<int> lst2(5, 10);  //5个10
	list<int> lst3(lst2.begin(), lst2.end());

	//拷贝构造
	list<int> copy(lst3);


	//迭代器
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

	//头插
	lst.push_front(0);
	lst.emplace_front(-1);

	//尾插
	lst.push_back(1);
	lst.emplace_back(2);
	printList(lst);


	int arr[] = { 1, 2, 3 };

	list<int> lst2;
	//assign: 赋值
	lst2.assign(arr, arr + 3);
	printList(lst2);

	lst2.assign(3, 5); //3个5
	printList(lst2);

}


void test5() {
	list<int> lst;

	//插入insert, 在迭代器位置的前面插入
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
	//list插入操作不会导致迭代器失效, 只要不删除它, 这个迭代器就一直指向这


	lst.erase(it); //7 9 0 2 5 5 5 1
	//删除左闭右开区间的元素
	lst.erase(++lst.begin(), --lst.end()); // 7 1
	//删除会导致迭代器失效, 因为链表删除时被删除元素的空间被释放了
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

	//拼接, 会修改传入的list本身的内容
	//直接把lis2拼接到lst中, lst2就没了
	lst.splice(lst.begin(), lst2); //lst: 4 5 1 2 3  lst2: 空
	printList(lst);
	printList(lst2);

	//lst2: 4   lst: 5 1 2 3
	lst2.splice(lst2.end(), lst, lst.begin());
	
	//lst2: 4 1 2   lst: 5 3
	lst2.splice(lst2.end(), lst, ++lst.begin(), --lst.end());


	printList(lst2);
	//remove 删除值, 如果没有则不作操作
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

	//去重
	//要求元素有序, 才能完成去重的作用 (不然代价太大)
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



	//要求被合并对象有序, 合并完之后被合并对象为空
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