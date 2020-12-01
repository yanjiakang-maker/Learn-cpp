#include<iostream>
#include<string>

using namespace std;


//�򵥵�ʵ��.
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

	//ȫȱʡ�Ĺ��캯��
	String(const char* ptr = "")
		:_ptr(new char[strlen(ptr) + 1])
	{
		strcpy(_ptr, ptr);
	}


	//ϵͳĬ�ϵĿ�������
	//ǳ����, ���������ʱ�����ͷŵ�����
	//String(const String& str)
	//	:_ptr(strcpy(_ptr, str._ptr))
	//{}

	//��ʽ����Ŀ�������, ������: ������������� + ��Դ
	String(const String& str)
		:_ptr(new char[strlen(str._ptr) + 1])
	{
		//���: ���Լ��Ŀռ�, ����str������
		strcpy(_ptr, str._ptr);
	}

	/*
		//��������  �ִ�д��

		//����һ��Ҫ��ʼ��_ptr, ��Ϊ���Ǹ���������, ��û�пռ��,
		//����ʼ���Ļ������ֵ, ֮�󽻻����ͷŵ�ʱ����������ֵ��g��
		String(const String& str)
			:_ptr(nullptr)  
		{
			//����һ���ֲ�����: ���ù��캯�� --> ���ռ� + ���ݿ���
			String tmp(str._ptr);
			//������һ��ָ��, ��nullptr���˾ֲ�����tmp, ����������ֲ������������nullptr�ͱ�������
			//�ⲧ --> ɱ������
			swap(_ptr, tmp._ptr);
		}
	*/

	//��ֵ��������غ���
	String& operator=(const String& str) {
		if (this != &str) {
			//���ռ�   ��Ϊԭ�����ݲ�����, Ϊ�˱�֤�ռ��㹻, ����Ҫ�¿��ռ�
			char* tmp = new char[strlen(str._ptr) + 1];
			//������Դ
			strcpy(tmp, str._ptr);
			//�ͷ�ԭ�пռ�
			delete[] _ptr;
			//ָ���µĿռ�
			_ptr = tmp;
		}
		return *this;
	}

	/*
		//��ֵ���������  �ִ�д��
		String& operator=(String tmp) {
			//���ε�ʱ����ÿ������촴����һ���ֲ�����tmp, ���ռ�+�����Ѿ����
			//��������ʱ str���ͷ�,   �Ϲ�������
			//Ȼ��ֱ��һ������, ֱ����ȡ�Ͷ��ɹ�, �밡
			swap(_ptr, tmp._ptr);
			return *this;
		}
	*/

	//����C�����ַ��� (ָ��)
	const char* c_str() const {
		return _ptr;
	}


	//����
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
	//��������
	String s2 = s;
	//��ֵ
	s = s2;
}


int main() {
	test();

	return 0;
}