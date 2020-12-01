#include<iostream>
#include<string>

using namespace std;


//简单的实现.
class String {
public:
	//String()
	//	:_ptr(new char[1])
	//{
	//	*_ptr = '\0';
	//}

	//String(char* ptr)
	//	:_ptr(new char[strlen(ptr) + 1])
	//{
	//	strcpy(_ptr, ptr);
	//}

	//全缺省的构造函数
	String(const char* ptr = "")
		:_ptr(new char[strlen(ptr) + 1])
	{
		strcpy(_ptr, ptr);
	}


	//系统默认的拷贝构造
	//浅拷贝, 会造成析构时二次释放的问题
	//String(const String& str)
	//	:_ptr(strcpy(_ptr, str._ptr))
	//{}

	//显式定义的拷贝构造, 完成深拷贝: 拷贝对象的内容 + 资源
	String(const String& str)
		:_ptr(new char[strlen(str._ptr) + 1])
	{
		//深拷贝: 开自己的空间, 拷贝str的内容
		strcpy(_ptr, str._ptr);
	}

	/*
		//拷贝构造  现代写法

		//这里一定要初始化_ptr, 因为这是个拷贝构造, 是没有空间的,
		//不初始化的话是随机值, 之后交换完释放的时候如果是随机值就g了
		String(const String& str)
			:_ptr(nullptr)  
		{
			//创建一个局部对象: 调用构造函数 --> 开空间 + 内容拷贝
			String tmp(str._ptr);
			//交换了一下指针, 把nullptr给了局部对象tmp, 函数结束后局部对象带着他的nullptr就被销毁了
			//这钵 --> 杀人诛心
			swap(_ptr, tmp._ptr);
		}
	*/

	//赋值运算符重载函数
	String& operator=(const String& str) {
		if (this != &str) {
			//开空间   因为原来内容不用了, 为了保证空间足够, 所以要新开空间
			char* tmp = new char[strlen(str._ptr) + 1];
			//拷贝资源
			strcpy(tmp, str._ptr);
			//释放原有空间
			delete[] _ptr;
			//指向新的空间
			_ptr = tmp;
		}
		return *this;
	}

	/*
		//赋值运算符重载  现代写法
		String& operator=(String tmp) {
			//传参的时候调用拷贝构造创建了一个局部对象tmp, 开空间+拷贝已经完成
			//函数结束时 str被释放,   老工具人了
			//然后直接一波交换, 直接窃取劳动成果, 秒啊
			swap(_ptr, tmp._ptr);
			return *this;
		}
	*/

	//返回C风格的字符串 (指针)
	const char* c_str() const {
		return _ptr;
	}


	//析构
	~String() {
		if (_ptr) {
			delete[] _ptr;
			_ptr = nullptr;
		}
	}


private:
	char* _ptr;
};



void test() {
	string s;
	const char* p = s.c_str();

	String s2;
	const char* p2 = s2.c_str();
}


void test2() {
	String s = "123";
	//拷贝构造
	String s2 = s;
	//赋值
	s = s2;
}


int main() {
	test();

	return 0;
}