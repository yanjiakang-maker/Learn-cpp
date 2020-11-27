#include<iostream>
#include<string>

using namespace std;


//���캯��
void test() {

	string str1;
	string str2(str1);

	string str3("123456");
	string str4 = "12345678"; //���ι������ʽ����ת��

	string str5(str4, 3);   //45678
	string str6(str4, 3, 2); //45

	string str7("1234567989", 5); // 12345

	string str8(10, 'a'); //aaaaaaaaaa
}


//�������
void test2() {
	string str1 = "1234";
	const string str2 = "12345";

	//size: ��Ч�ַ��ĸ��� --->  �� '\0' ������
	int size = str1.size();
	int size2 = str2.size();

	char str[] = { '1', '\0', '\0', '\0' };
	int len = strlen(str);
	string str3(str);
	int size3 = str3.size();


	string str4("1234");
	//resize(n): �޸���Ч�ַ��ĸ���
	// n > string���������ݵĳ���, �������ӵ�λ�ò�'\0'
	str4.resize(10);
	const char* strarr = str4.c_str();

	int size4 = str4.size();
	int len2 = strlen(strarr);
	cout << str4 << "end" << endl;
	cout << strarr << "end" << endl;

}
/*
		resize(n) : ��size��Ϊn, ��������λ����'\0'����
		resize(n, c) : ��size��Ϊn, ��������λ�����ַ�c����
			resizeֻ����������ӵ�λ�õ�����, �����޸���������

			resize����ʹsize����С
				�޸�֮��size > ԭʼ����, ��string������
				��Сsizeʱ, ֻ��ض�ԭ������, ���ı�capacity
*/
void test3() {
	string str = "1234";
	str.resize(6, 'a'); // 1234aa
	int size = str.size();
	//capacity: string�������ַ���������
	int cap = str.capacity();

	//�޸�֮���size����cap, ���޸���Ч�ַ��ĸ���, ����������
	str.resize(20, 'b');
	size = str.size();
	cap = str.capacity();

	//resize ��Сsizeʱ, ֻ��ض�����, capacity�����
	str.resize(2, 'c');
	size = str.size();
	cap = str.capacity();
}

void test4() {
	string str = "12345";
	int size = str.size();
	//length: ��sizeһëһ��,  Ϊ�˺�֮�����ױ���һ��, ���˸�size
	size = str.length();
}

void test5() {
	string s;
	s.resize(10);
	cout << "size: " << s.size() << endl;
	cout << "capacity: " << s.capacity() << endl;

	//reserve: ֻ���޸�����capacity , ���޸�ʵ��Ԫ�ظ���size
	//��Ϊ����Ҫ�ͷ�ԭ�пռ�, �����µĿռ�, ���۽ϴ�
	//����reserveһ������:  ֪���ַ�������, ��ǰʹ��reserve���ÿռ�, ��С����������
	s.reserve(60);
	cout << "size: " << s.size() << endl;
	cout << "capacity: " << s.capacity() << endl;

	s.reserve(10);
	cout << "size: " << s.size() << endl;
	cout << "capacity: " << s.capacity() << endl;

	
	//reserve���Ҫ��С����, ʵ�ʵ�������С������string��������, �����ʵ��Ż�(ֱ���������������ַ���Ҫ�Ŀռ�)
	//˵�˻�����: �������С����, ���ܱȵ�ǰsize��С
	string s2 = "12345";
	s2.reserve(4);
	cout << "size: " << s2.size() << endl;
	cout << "capacity: " << s2.capacity() << endl;
}

void print_capacity() {
	string s;
	int cap = s.capacity();
	cout << "capacity: " << cap << endl;

	//����: ��һ��2��, ���涼��1.5�� (���)
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

	//clear: size��0, cap����
	s.clear();
	cout << "size: " << s.size() << endl;
	cout << "cap: " << s.capacity() << endl;


	s = "123456";
	s.reserve(15); // n > size :  n <= 15 capʼ��Ϊ15
	cout << "size: " << s.size() << endl;
	cout << "cap: " << s.capacity() << endl;

	//shrink_to_fit :  ������ > size�������, ��������С�����ʵĴ�С 
	s.reserve(1000);
	s.shrink_to_fit();
	cout << "size: " << s.size() << endl;
	cout << "cap: " << s.capacity() << endl;
}


//�������
void test7() {
	string s = "1234";

	//front: ��ȡ��һ���ַ� (�ɶ���д)  
	s.front() = 'a'; // a234
	cout << s << endl;

	//��ȡ���һ���ַ�  (�ɶ���д)
	s.back() = 'b'; // a23b
	cout << s << endl;

	//const string ʱ�ӿ�Ϊ  const front/back Ϊֻ���ӿ�, �����޸�
	const string s2 = "1234";
	//s2.front() = 'a';
	//s2.back() = 'b';


	s = "1234";
	s.at(0) = 'a';
	s.at(1) = 'b';
	//λ��Խ��, ���쳣
	s.at(5) = 'e';

	//const�ӿ�, ֻ��
	//s2.at(0) = 'a';


	s = "1234";
	//[] ����, �� []����������غ���
	//s[]  <--->  s.operator[]
	s[0] = 'a';
	s[1] = 'b';
	s.operator[](2) = 'c';//������ʽ

	// []Խ�����, Debug�汾��assert����, Release�汾������(Σ)
	char c = s[10];


	//const�ӿ�
	//s2[3] = 'd';
}


//3�ֱ�����ʽ  ([], ������, ��Χfor)
void test8() {
	cout << "operator[]" << endl;
	string s = "12345";

	for (int i = 0; i < s.size(); i++) {
		cout << s[i] << " ";
	}
	cout << endl;

/*
	������: һ��Ԫ�ص�ͨ�÷��ʻ���, ��һ�����ģʽ
	begin������: ָ�������е�һ��Ԫ�ص�λ��
	end������: ָ�����������һ��Ԫ�ص���һ��λ��
	��ʾ��Χ: ����ҿ� --> [begin, end)

	ʹ�÷�ʽ: ������ָ��
		����: ������, ++
*/
	cout << "iterator: " << endl;
	//�ɶ���д������, �����޸�����
	string::iterator it = s.begin();
	while (it != s.end()) {
		//������������
		cout << *it << " ";
		//ͨ���������޸�����
		*it = 'a';
		//������++, �ƶ�����һ��Ԫ�ص�λ��
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
		begin �� end �������ֽӿ�, ��const��const�ӿ�
		��const����: ���� begin �� end �᷵�� ��const������(�ɶ���д)
		const����: ���� begin �� end �᷵�� const������ (ֻ��)

		cbegin �� cend ��const�ӿ�, ����const������
		const�ͷ�const����: ���ܵ��������ӿ�, ����ֻ��������
	*/

	cout << "const_iterator: " << endl;
	s = "12345";
	//const������
	string::const_iterator cit = s.cbegin();
	while (cit != s.cend()) {
		cout << *cit << " ";
		//const��������ֻ��������, ����ͨ���������޸�����
		//*cit = 'a';
		++cit;
	}
	cout << endl;

	/*
		���������:  
			rbegin: ָ�����һ��Ԫ�ص�λ�� 
			rend: ָ���һ��Ԫ�ص�ǰһ��λ��

		�Ӻ���ǰ����,  ++����: �ƶ���ǰһ��Ԫ�ص�λ��
	*/

	cout << "reverse_iterator: " << endl;
	s = "12345";
	string::reverse_iterator rit = s.rbegin();
	while (rit != s.rend()) {
		cout << *rit << " ";
		//�ƶ���ǰһ��λ��
		++rit;
	}
	cout << endl;

	//ע��: end, rend, cend, crend: ���صĵ�����������ЧԪ��֮���λ��, ���ܽ�����(�Ƿ�����)

	/*
		rbegin, rend: ���صĶ��ǿɶ���д������
		crbegin, crend: ���صĶ���ֻ��������
	*/
	cout << "const_reverse_iterator: " << endl;
	string::const_reverse_iterator crit = s.crbegin();
	while (crit != s.crend()) {
		cout << *crit << " ";
		++crit;
	}
	cout << endl;


	//��Χfor
	cout << "��Χfor: " << endl;
	s = "12345";
	//for(��ǰҪ�鿴�ı���: ��Ҫ����������)   �ɶ���д
	//�ײ�ʵ�־��ǵ�����
	for (auto& ch : s) {
		cout << ch << " ";
		//�޸�����, �������������ͽ���, ��Ȼ�޸ĵ��ǿ�����ֵ, ԭ����ֵû�б��޸�
		ch = 'a';
	}
	cout << endl;

	//ֻ��, Ч�����      auto --> �Զ������Ƶ�
	for (const auto& ch : s) {
		cout << ch << " ";
	}
	cout << endl;

	/*
		�����ķ�Χfor��д��ʽ:
			1. ֻ��: for(const auto& ���� : ����)
			2. �ɶ���д: for(auto& ���� : ����)
	*/
}


//����ɾ�����
void test9() {
	string s;
	//β��
	s.push_back('1');
	s.push_back('2');
	s.push_back('3');
	s.push_back('4');

	string s2 = "abc";

	//׷�Ӳ���
	s.append(s2); // 1234abc
	s.append(s2, 2, 1); //1234abcc
	s.append("xyz");  //1234abccxyz
	s.append("opq", 2);  //1234abccop
	s.append(3, '1');  //1234abccop111
	s.append(s2.begin(), s2.end()); //1234abccop111abc
	char arr[] = "56789";
	s.append(arr, arr + 4);//1234abccop111abc5678


	//string +=��������غ���: operator+=  --> ����ַ�������ƴ�� (���)
	s = "";
	s2 = "789";

	s += '1';
	s += "abc";
	s += s2;


	//insert: ������λ�ò���
	s = "";
	s2 = "123";
	//��pos��ǰ�����
	s.insert(0, s2); //123      ͷ��s2
	s.insert(1, s2); //112323   ��s[1]ǰ�����s2

	string s3 = "abc";
	s.insert(2, s3, 1, 2); //11bc2323	��s[2]ǰ����s3�����λ��[1]��ʼ�������ַ�

	s.insert(4, "def"); //11bcdef2323	��λ��[4]ǰ�����ַ���
	s.insert(5, "ghi", 1); //11bcdgef2323	��λ��[5]ǰ�����ַ���"ghi"��1���ַ�
	s.insert(9, 3, 'f'); //11bcdgef2fff323		��λ��[9]ǰ����3���ַ�'f'
	s.insert(s.begin(), 2, '0'); //0011bcdgef2fff323	ͷ��2��'0'
	s.insert(s.end(), 3, 'g'); //0011bcdgef2fff323ggg	β��3��'g'
	s.insert(s.begin() + 1, 'a'); //0a011bcdgef2fff323ggg	��λ��[1]ǰ����һ��'a'

	s.insert(s.end() - 1, s2.begin(), s2.end()); //0a011bcdgef2fff323gg789g		�ڵ����ڶ���λ��ǰ����s2


	s = "abc";
	s2 = "123";

	//assign ��ֵ, �ȼ���operator= (������=�Ϳ�)
	s.assign(s2); //123
	s.assign(s2, 1, 2); //23
	s.assign("789"); //789
	s.assign("abcdefg", 5); // abcde
	s.assign(5, '1'); //11111
	s.assign(s2.begin() + 1, s2.end() - 1);// 2


	s = "123456789";
	//βɾ
	s.pop_back(); //12345678

	s.erase(0, 1); // 2345678
	s.erase(3, 2); // 23478
	s.erase(s.size() - 1, 1); //βɾ 2347

	s.erase(s.end() - 1);//βɾ 234
	s.erase(s.begin()); //ͷɾ 34
	s.erase(s.begin(), s.end());//ȫɾ ""
}



void testa() {
	string s = "123";
	string s2 = "abc";
	
	//�滻
	s.replace(1, 1, s2); //1abc3   s��λ��[1]��ʼ��1���ַ�, ��s2�滻

	s = "123";
	s.replace(1, 2, s2); //1abc


	s = "123";
	s2 = "abc";

	//���� (��Ա����)
	s.swap(s2);

	//�ǳ�Ա����  �ȼ�������
	swap(s, s2);
}


void testb() {
	string s = "123";
	cout << s << endl;
	cout << s.c_str() << endl;
	//c_str ����const char*
	const char* ptr = s.c_str();
	//������һ��
	ptr = s.data();


	//copy: ��string��������ݿ�����sָ���������
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

	pos = s.find("000"); // �Ҳ�������-1  ��Ϊ��size_t �޷��� ---> 4G�Ĵ�С


	//��   cplusplus.com
	//substr: ��ȡ�ַ���
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


	// rfind: �������  
	//�鿴�ļ���ʽ
	s = "test.txt.tar.gz.cpp";
	pos = s.rfind(".");
	if (pos != string::npos) {
		cout << s.substr(pos + 1) << endl;
	}

}


void testd() {
	//�ȽϹ���: ��ǰ���, ����ÿһ���ַ���ASCII��ֵ�Ƚ�
	int ret = strcmp("1", "12");  //-1
	ret = strcmp("345", "92");	  //-1


	//�߼����������
	string s = "1";
	string s2 = "12";
	string s3 = "345";
	string s4 = "93";

	ret = s > s2;
	ret = s3 >= s4;
}


void teste() {
	string s;
	
	//cin: ���ܶ�����ո���ַ���
	cin >> s;
	operator>>(cin, s);  //������ʽ

	getline(cin, s);
	getline(cin, s, ','); //���� , ����  ��д����������Ĭ������ \n ����
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