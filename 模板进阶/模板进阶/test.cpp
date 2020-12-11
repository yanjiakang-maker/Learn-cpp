#include<iostream>

using namespace std;

//这个n就是非类型模板参数   ---> 只能接收整数或者类整数
template <class T, int n = 10>
class array {

private:
	T _arr[n];
};


void test() {
	//非类型模板参数只能接收整数或者类整数
	array<int> arr;			//存放10个元素的数组
	array<int, 100> arr;	//存放100个元素
	array<int, 'a'> arr;	//存放97个元素
}



template <class T>
bool isEqual(T& left, T& right) {
	return left == right;
}


//字符串类型的特化  --> 垃圾, 不好用, 直接写一个普通函数不香吗?
template<>
bool isEqual<char*>(char*& left, char*& right) {
	if (strcmp(left, right) == 0)
		return true;
	return false;
}



void test2() {
	int a = 1, b = 2;
	char c = 'c', d = 'd';
	
	bool ret = isEqual(a, b);
	ret = isEqual(c, d);

	const char* str1 = "123";
	const char* str2 = "123";
	ret = isEqual(str1, str2);


	char str3[] = "123";
	char str4[] = "123";
	ret = isEqual(str3, str4);

}


/*
	类模板的全特化
		必须要有一个普通的类模板
	
	半特化
		1. 特化部分类型 (位置不限)
		2. 对模板参数做进一步的限制

	先匹配特化, 都没有才会匹配普通模板
*/

/*
	模板不支持分离编译: 声明和定义都写在头文件里  (.h 或 .hpp)
*/


int main() {
	test();

	return 0;
}
