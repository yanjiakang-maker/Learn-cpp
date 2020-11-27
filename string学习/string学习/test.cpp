#include<iostream>
#include<string>

using namespace std;


//构造函数
void test() {

	string str1;
	string str2(str1);

	string str3("123456");
	string str4 = "12345678"; //单参构造的隐式类型转换

	string str5(str4, 3);   //45678
	string str6(str4, 3, 2); //45

	string str7("1234567989", 5); // 12345

	string str8(10, 'a'); //aaaaaaaaaa
}


//容量相关
void test2() {
	string str1 = "1234";
	const string str2 = "12345";

	//size: 有效字符的个数 --->  和 '\0' 有区别
	int size = str1.size();
	int size2 = str2.size();

	char str[] = { '1', '\0', '\0', '\0' };
	int len = strlen(str);
	string str3(str);
	int size3 = str3.size();


	string str4("1234");
	//resize(n): 修改有效字符的个数
	// n > string对象中内容的长度, 则新增加的位置补'\0'
	str4.resize(10);
	const char* strarr = str4.c_str();

	int size4 = str4.size();
	int len2 = strlen(strarr);
	cout << str4 << "end" << endl;
	cout << strarr << "end" << endl;

}
/*
		resize(n) : 让size变为n, 且新增的位置用'\0'补充
		resize(n, c) : 让size变为n, 且新增的位置用字符c补充
			resize只会填充新增加的位置的内容, 不会修改已有内容

			resize可以使size变大变小
				修改之后size > 原始容量, 则string会增容
				减小size时, 只会截断原有内容, 不改变capacity
*/
void test3() {
	string str = "1234";
	str.resize(6, 'a'); // 1234aa
	int size = str.size();
	//capacity: string对象存放字符的最大个数
	int cap = str.capacity();

	//修改之后的size大于cap, 则修改有效字符的个数, 并增加容量
	str.resize(20, 'b');
	size = str.size();
	cap = str.capacity();

	//resize 减小size时, 只会截断内容, capacity不会变
	str.resize(2, 'c');
	size = str.size();
	cap = str.capacity();
}

void test4() {
	string str = "12345";
	int size = str.size();
	//length: 与size一毛一样,  为了和之后容易保持一致, 加了个size
	size = str.length();
}

void test5() {
	string s;
	s.resize(10);
	cout << "size: " << s.size() << endl;
	cout << "capacity: " << s.capacity() << endl;

	//reserve: 只会修改容量capacity , 不修改实际元素个数size
	//因为增容要释放原有空间, 开辟新的空间, 代价较大
	//所以reserve一般用于:  知道字符串长度, 提前使用reserve开好空间, 减小后续增代价
	s.reserve(60);
	cout << "size: " << s.size() << endl;
	cout << "capacity: " << s.capacity() << endl;

	s.reserve(10);
	cout << "size: " << s.size() << endl;
	cout << "capacity: " << s.capacity() << endl;

	
	//reserve如果要减小容量, 实际的容量大小会依据string对象内容, 进行适当优化(直到容量必须满足字符需要的空间)
	//说人话就是: 按情况减小容量, 不能比当前size还小
	string s2 = "12345";
	s2.reserve(4);
	cout << "size: " << s2.size() << endl;
	cout << "capacity: " << s2.capacity() << endl;
}

void print_capacity() {
	string s;
	int cap = s.capacity();
	cout << "capacity: " << cap << endl;

	//增容: 第一次2倍, 后面都是1.5倍 (大概)
	for (int i = 0; i < 1000; i++) {
		s.push_back(i);
		if (cap != s.capacity()) {
			cap = s.capacity();
			cout << "capacity: " << cap << endl;
		}
	}
}

void test6() {
	string s = "123456789";
	cout << "size: " << s.size() << endl;
	cout << "cap: " << s.capacity() << endl;

	//clear: size清0, cap不变
	s.clear();
	cout << "size: " << s.size() << endl;
	cout << "cap: " << s.capacity() << endl;


	s = "123456";
	s.reserve(15); // n > size :  n <= 15 cap始终为15
	cout << "size: " << s.size() << endl;
	cout << "cap: " << s.capacity() << endl;

	//shrink_to_fit :  在满足 > size的情况下, 把容量减小到合适的大小 
	s.reserve(1000);
	s.shrink_to_fit();
	cout << "size: " << s.size() << endl;
	cout << "cap: " << s.capacity() << endl;
}


//访问相关
void test7() {
	string s = "1234";

	//front: 获取第一个字符 (可读可写)  
	s.front() = 'a'; // a234
	cout << s << endl;

	//获取最后一个字符  (可读可写)
	s.back() = 'b'; // a23b
	cout << s << endl;

	//const string 时接口为  const front/back 为只读接口, 不能修改
	const string s2 = "1234";
	//s2.front() = 'a';
	//s2.back() = 'b';


	s = "1234";
	s.at(0) = 'a';
	s.at(1) = 'b';
	//位置越界, 抛异常
	s.at(5) = 'e';

	//const接口, 只读
	//s2.at(0) = 'a';


	s = "1234";
	//[] 访问, 是 []的运算符重载函数
	//s[]  <--->  s.operator[]
	s[0] = 'a';
	s[1] = 'b';
	s.operator[](2) = 'c';//完整形式

	// []越界访问, Debug版本报assert错误, Release版本不报错(危)
	char c = s[10];


	//const接口
	//s2[3] = 'd';
}


//3种遍历方式  ([], 迭代器, 范围for)
void test8() {
	cout << "operator[]" << endl;
	string s = "12345";

	for (int i = 0; i < s.size(); i++) {
		cout << s[i] << " ";
	}
	cout << endl;

/*
	迭代器: 一种元素的通用访问机制, 是一种设计模式
	begin迭代器: 指向容器中第一个元素的位置
	end迭代器: 指向容器中最后一个元素的下一个位置
	表示范围: 左闭右开 --> [begin, end)

	使用方式: 类似于指针
		操作: 解引用, ++
*/
	cout << "iterator: " << endl;
	//可读可写迭代器, 可以修改内容
	string::iterator it = s.begin();
	while (it != s.end()) {
		//迭代器解引用
		cout << *it << " ";
		//通过迭代器修改内容
		*it = 'a';
		//迭代器++, 移动到下一个元素的位置
		++it;
	}
	cout << endl;

	it = s.begin();
	while (it != s.end()) {
		cout << *it << " ";
		++it;
	}
	cout << endl;

	/*
		begin 和 end 都有两种接口, 非const和const接口
		非const对象: 调用 begin 和 end 会返回 非const迭代器(可读可写)
		const对象: 调用 begin 和 end 会返回 const迭代器 (只读)

		cbegin 和 cend 是const接口, 返回const迭代器
		const和非const对象: 都能调用这俩接口, 返回只读迭代器
	*/

	cout << "const_iterator: " << endl;
	s = "12345";
	//const迭代器
	string::const_iterator cit = s.cbegin();
	while (cit != s.cend()) {
		cout << *cit << " ";
		//const迭代器是只读迭代器, 不能通过解引用修改内容
		//*cit = 'a';
		++cit;
	}
	cout << endl;

	/*
		反向迭代器:  
			rbegin: 指向最后一个元素的位置 
			rend: 指向第一个元素的前一个位置

		从后往前遍历,  ++操作: 移动到前一个元素的位置
	*/

	cout << "reverse_iterator: " << endl;
	s = "12345";
	string::reverse_iterator rit = s.rbegin();
	while (rit != s.rend()) {
		cout << *rit << " ";
		//移动到前一个位置
		++rit;
	}
	cout << endl;

	//注意: end, rend, cend, crend: 返回的迭代器都是有效元素之外的位置, 不能接引用(非法访问)

	/*
		rbegin, rend: 返回的都是可读可写迭代器
		crbegin, crend: 返回的都是只读迭代器
	*/
	cout << "const_reverse_iterator: " << endl;
	string::const_reverse_iterator crit = s.crbegin();
	while (crit != s.crend()) {
		cout << *crit << " ";
		++crit;
	}
	cout << endl;


	//范围for
	cout << "范围for: " << endl;
	s = "12345";
	//for(当前要查看的变量: 需要遍历的容器)   可读可写
	//底层实现就是迭代器
	for (auto& ch : s) {
		cout << ch << " ";
		//修改内容, 必须用引用类型接收, 不然修改的是拷贝的值, 原来的值没有被修改
		ch = 'a';
	}
	cout << endl;

	//只读, 效率最高      auto --> 自动类型推导
	for (const auto& ch : s) {
		cout << ch << " ";
	}
	cout << endl;

	/*
		常见的范围for书写形式:
			1. 只读: for(const auto& 变量 : 容器)
			2. 可读可写: for(auto& 变量 : 容器)
	*/
}


//插入删除相关
void test9() {
	string s;
	//尾插
	s.push_back('1');
	s.push_back('2');
	s.push_back('3');
	s.push_back('4');

	string s2 = "abc";

	//追加插入
	s.append(s2); // 1234abc
	s.append(s2, 2, 1); //1234abcc
	s.append("xyz");  //1234abccxyz
	s.append("opq", 2);  //1234abccop
	s.append(3, '1');  //1234abccop111
	s.append(s2.begin(), s2.end()); //1234abccop111abc
	char arr[] = "56789";
	s.append(arr, arr + 4);//1234abccop111abc5678


	//string +=运算符重载函数: operator+=  --> 完成字符串换的拼接 (最常用)
	s = "";
	s2 = "789";

	s += '1';
	s += "abc";
	s += s2;


	//insert: 在任意位置插入
	s = "";
	s2 = "123";
	//在pos的前面插入
	s.insert(0, s2); //123      头插s2
	s.insert(1, s2); //112323   在s[1]前面插入s2

	string s3 = "abc";
	s.insert(2, s3, 1, 2); //11bc2323	在s[2]前插入s3对象从位置[1]开始的两个字符

	s.insert(4, "def"); //11bcdef2323	在位置[4]前插入字符串
	s.insert(5, "ghi", 1); //11bcdgef2323	在位置[5]前插入字符串"ghi"的1个字符
	s.insert(9, 3, 'f'); //11bcdgef2fff323		在位置[9]前插入3个字符'f'
	s.insert(s.begin(), 2, '0'); //0011bcdgef2fff323	头插2个'0'
	s.insert(s.end(), 3, 'g'); //0011bcdgef2fff323ggg	尾插3个'g'
	s.insert(s.begin() + 1, 'a'); //0a011bcdgef2fff323ggg	在位置[1]前插入一个'a'

	s.insert(s.end() - 1, s2.begin(), s2.end()); //0a011bcdgef2fff323gg789g		在倒数第二个位置前插入s2


	s = "abc";
	s2 = "123";

	//assign 赋值, 等价于operator= (所以用=就可)
	s.assign(s2); //123
	s.assign(s2, 1, 2); //23
	s.assign("789"); //789
	s.assign("abcdefg", 5); // abcde
	s.assign(5, '1'); //11111
	s.assign(s2.begin() + 1, s2.end() - 1);// 2


	s = "123456789";
	//尾删
	s.pop_back(); //12345678

	s.erase(0, 1); // 2345678
	s.erase(3, 2); // 23478
	s.erase(s.size() - 1, 1); //尾删 2347

	s.erase(s.end() - 1);//尾删 234
	s.erase(s.begin()); //头删 34
	s.erase(s.begin(), s.end());//全删 ""
}



void testa() {
	string s = "123";
	string s2 = "abc";
	
	//替换
	s.replace(1, 1, s2); //1abc3   s从位置[1]开始的1个字符, 用s2替换

	s = "123";
	s.replace(1, 2, s2); //1abc


	s = "123";
	s2 = "abc";

	//交换 (成员函数)
	s.swap(s2);

	//非成员函数  等价于上面
	swap(s, s2);
}


void testb() {
	string s = "123";
	cout << s << endl;
	cout << s.c_str() << endl;
	//c_str 返回const char*
	const char* ptr = s.c_str();
	//和上面一样
	ptr = s.data();


	//copy: 把string对象的内容拷贝到s指向的数组中
	char arr[100];
	s.copy(arr, 3);
}


void testc() {
	string s = "1234561234abc123a123456789";
	string s2 = "123456798";

	size_t pos = s.find(s2);
	pos = s.find("123");
	pos = s.find("abcxyz", 0, 3);
	pos = s.find('a');

	pos = s.find("000"); // 找不到返回-1  因为是size_t 无符号 ---> 4G的大小


	//找   cplusplus.com
	//substr: 截取字符串
	s = "http://cplusplus.com/reference/stringstring//substr/";
	pos = s.find("://");
	if (pos != string::npos) {
		size_t pos2 = s.find("/", pos + 3);
		if (pos2 != string::npos) {
			pos += 3;
			string sub = s.substr(pos, pos2 - pos);
			cout << sub << endl;
		}
	}


	// rfind: 反向查找  
	//查看文件格式
	s = "test.txt.tar.gz.cpp";
	pos = s.rfind(".");
	if (pos != string::npos) {
		cout << s.substr(pos + 1) << endl;
	}

}


void testd() {
	//比较规则: 从前像后, 按照每一个字符的ASCII码值比较
	int ret = strcmp("1", "12");  //-1
	ret = strcmp("345", "92");	  //-1


	//逻辑运算符重载
	string s = "1";
	string s2 = "12";
	string s3 = "345";
	string s4 = "93";

	ret = s > s2;
	ret = s3 >= s4;
}


void teste() {
	string s;
	
	//cin: 不能读入带空格的字符串
	cin >> s;
	operator>>(cin, s);  //完整形式

	getline(cin, s);
	getline(cin, s, ','); //遇到 , 结束  不写第三个参数默认遇到 \n 结束
}


void Test() {
	string str("Hello Bit.");

	str.reserve(50);
	str.reserve(111);
	str.resize(5);
	str.reserve(50);
	str.reserve(10);
	cout << str.size() << ":" << str.capacity() << endl;
}

void Test2() {
	string s = "123456789";
	string::iterator it = s.begin();
	reverse(it, it + 3);
	cout << s << endl;
}


int main() {
	//test();
	//test2();
	//test3();
	//test4();
	//test5();
	//print_capacity();
	test6();
	//test7();
	//test8();
	//test9();
	//testa();
	//testb();
	//testc();
	//testd();
	//Test();

	return 0;
}