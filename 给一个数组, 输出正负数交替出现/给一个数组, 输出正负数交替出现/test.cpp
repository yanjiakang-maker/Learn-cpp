#include <iostream>
#include <vector>

using namespace std;


vector<int> changeArr(vector<int>& v) {
	//��������vector�ֱ𱣴������͸���
	vector<int> plus;
	vector<int> minus;
	//������������, �����ֲ����Ӧ������
	for (auto& e : v) {
		if (e >= 0)
			plus.push_back(e);
		else
			minus.push_back(e);
	}

	vector<int> result;
	//������������, �����������
	int i(0), j(0);
	while (i < plus.size() && j < minus.size()) {
		result.push_back(plus[i]);
		i++;
		result.push_back(minus[j]);
		j++;
	}
	//����һ��������������˾��˳�ѭ��, �Ѻ�ߵĲ��ϼ���
	if (i == plus.size()) {
		//˵�����������������, �����������ߵĶ�������
		for (; j < minus.size(); j++)
			result.push_back(minus[j]);
	}
	else {
		//˵�����������������, �����������ߵĶ�������
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
