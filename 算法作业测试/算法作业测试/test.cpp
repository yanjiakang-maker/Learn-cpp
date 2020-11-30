#include<iostream>
#include<string>
#include<algorithm>

using namespace std;


void milk() {

}


void beat() {
	int T = 0;
	cin >> T;

	int i = 0;
	while (i < T) {
		int* arr = new int[10000];
		cin >> arr[0];
		int n = arr[0];

		for (int j =1; j <= n; j++)
			cin >> arr[j];

		//sort������ҿ�
		sort(arr + 1, arr + n + 1);

		if (arr[n / 2 + 1] % 2 == 0)
			cout << "Alice" << endl;
		else
			cout << "Bob" << endl;

		i++;
	}
}



void print(int num) {
	if (num == 1) {
		cout << "*" << endl;
		return;
	}

	int row = 1;
	while (row <= num) {
		for (int i = 0; i < num - row; i++)
			cout << " ";

		for (int i = 0; i < 2 * row - 1; i++)
			cout << "*";

		cout << endl;
		row++;
	}
}


string multiply(string num1, string num2) {
	int len1 = num1.size();
	int len2 = num2.size();

	//���������, �˻���λ�����ᳬ������������λ��֮��
	//����һ���������Ķ���,����Ϊlen1+len2, ��ʼ��Ϊȫ'0'
	string ret(len1 + len2, '0');

	//�Ӹ�λ��ʼ, ѭ��������
	for (int i = len1 - 1; i >= 0; i--) {
		for (int j = len2 - 1; j >= 0; j--) {
			//���̱Ƚϳ���, ���黭��ͼ���Ź�����һ��, �������
			int cur = (ret[i + j + 1] - '0') + (num1[i] - '0') * (num2[j] - '0');
			ret[i + j + 1] = cur % 10 + '0';
			ret[i + j] += cur / 10;
		}
	}

	//���ǰ���Ƿ���0, �еĻ��ض�
	for (int i = 0; i < len1 + len2; i++) {
		if (ret[i] != '0') {
			//�ӵ�һ����Ϊ0�����ֿ�ʼ�ص����һ������, �����Ľ��
			return ret.substr(i);
		}
	}
	//ѭ��������û�����Ļ�˵����ȫ'0'
	return "0";
}



int main() {

	//int arr[258329];

	//while (1) {
	//	int num = 0;
	//	cin >> num;

	//	if (num == 0)
	//		break;
	//	print(num);
	//}

	//beat();

	string s1 = "123";
	string s2 = "456";
	string ret = multiply(s1, s2);
	cout << ret << endl;

	//string s = "123456789";
	////s.substr(2); ������ô��, ��Ϊ����ֵ��������, Ҫ�´�����������
	//cout << s.substr(1) << endl;



	return 0;
}
