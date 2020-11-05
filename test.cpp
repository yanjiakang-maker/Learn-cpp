#include<iostream>

using namespace std;

void primeNum() {
	cout << 2 << " ";
	for (int num = 3; num < 100; num++) {
		int i = 2;
		for (; i < num; i++) {
			if (num % i == 0) {
				//不是质数
				break;
			}
		}
		if (i == num) {
			cout << num << " ";
		}
	}
	cout << endl;
}



int main() {
	primeNum();

	return 0;
}