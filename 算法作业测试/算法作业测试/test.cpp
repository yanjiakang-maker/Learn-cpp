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

		//sort是左闭右开
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

	//两个数相乘, 乘机的位数不会超过这两个数的位数之和
	//创建一个保存结果的对象,长度为len1+len2, 初始化为全'0'
	string ret(len1 + len2, '0');

	//从个位开始, 循环相乘相加
	for (int i = len1 - 1; i >= 0; i--) {
		for (int j = len2 - 1; j >= 0; j--) {
			//过程比较抽象, 建议画个图跟着过程走一遍, 会很清晰
			int cur = (ret[i + j + 1] - '0') + (num1[i] - '0') * (num2[j] - '0');
			ret[i + j + 1] = cur % 10 + '0';
			ret[i + j] += cur / 10;
		}
	}

	//检查前面是否有0, 有的话截断
	for (int i = 0; i < len1 + len2; i++) {
		if (ret[i] != '0') {
			//从第一个不为0的数字开始截到最后一个数字, 即最后的结果
			return ret.substr(i);
		}
	}
	//循环结束还没结束的话说明是全'0'
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
	////s.substr(2); 不能这么用, 因为返回值不是引用, 要新创建变量接收
	//cout << s.substr(1) << endl;



	return 0;
}
