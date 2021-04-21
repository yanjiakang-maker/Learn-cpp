#include <iostream>
#include <vector>

using namespace std;


vector<int> changeArr(vector<int>& v) {
	//创建两个vector分别保存正数和负数
	vector<int> plus;
	vector<int> minus;
	//遍历给定数组, 将数字插入对应的数组
	for (auto& e : v) {
		if (e >= 0)
			plus.push_back(e);
		else
			minus.push_back(e);
	}

	vector<int> result;
	//遍历正负数组, 交替插入结果集
	int i(0), j(0);
	while (i < plus.size() && j < minus.size()) {
		result.push_back(plus[i]);
		i++;
		result.push_back(minus[j]);
		j++;
	}
	//当有一个数组遍历结束了就退出循环, 把后边的补上即可
	if (i == plus.size()) {
		//说明正数数组遍历结束, 将负数数组后边的都插入结果
		for (; j < minus.size(); j++)
			result.push_back(minus[j]);
	}
	else {
		//说明负数数组遍历结束, 将正数数组后边的都插入结果
		for (; i < plus.size(); i++)
			result.push_back(plus[i]);
	}
	return result;
}

int main() {
	vector<int> v = { -2, -2, -3, 3, 6, -9, 7 };
	vector<int> result = changeArr(v);
	for (auto& e : result)
		cout << e << " ";
	cout << endl;

	return 0;
}
