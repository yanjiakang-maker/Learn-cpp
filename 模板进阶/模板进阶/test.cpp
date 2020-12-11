#include<iostream>

using namespace std;

//���n���Ƿ�����ģ�����   ---> ֻ�ܽ�����������������
template <class T, int n = 10>
class array {

private:
	T _arr[n];
};


void test() {
	//������ģ�����ֻ�ܽ�����������������
	array<int> arr;			//���10��Ԫ�ص�����
	array<int, 100> arr;	//���100��Ԫ��
	array<int, 'a'> arr;	//���97��Ԫ��
}



template <class T>
bool isEqual(T& left, T& right) {
	return left == right;
}


//�ַ������͵��ػ�  --> ����, ������, ֱ��дһ����ͨ����������?
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
	��ģ���ȫ�ػ�
		����Ҫ��һ����ͨ����ģ��
	
	���ػ�
		1. �ػ��������� (λ�ò���)
		2. ��ģ���������һ��������

	��ƥ���ػ�, ��û�вŻ�ƥ����ͨģ��
*/

/*
	ģ�岻֧�ַ������: �����Ͷ��嶼д��ͷ�ļ���  (.h �� .hpp)
*/


int main() {
	test();

	return 0;
}
