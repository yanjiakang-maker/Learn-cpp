#include<iostream>

using namespace std;

class Date {
public:
	//���캯��
	Date(int year = 2000, int month = 9, int day = 28) {
		//�ж������Ƿ�Ϸ�
		if (year > 0 && month > 0 && month <= 12
			&& day > 0 && day <= getMonthDay(year, month)) {

			_year = year;
			_month = month;
			_day = day;
		}
		else {
			cout << "���ڲ��Ϸ�: " << year << "-" << month << "-" << day << endl;
			cout << "����ΪĬ��ֵ: 2000-1-1";
			_year = 2000;
			_month = 1;
			_day = 1;
		}
	}

	//��ȡĳ���µ�����
	int getMonthDay(int year, int month) {
		static int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		int day = days[month];

		//�����2����Ϊ����, +1
		if (month == 2
			&& (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
			++day;

		return day;
	}

	// ���� += ����
	Date& operator+=(int day) {
		//a += -b --> a -= b
		if (day < 0) {
			return *this -= day;
		}
		//2020.5.1 + 20  --> 2020.5.21
		//2020.5.21 + 20  --> 2020.5.41  --> ��λ --> -31 -->�·ݽ�λ --> 2020.6.10
		//2020.12.6 + 90 --> 2020.12.96 --> ��λ --> -31 -->�·ݽ�λ --> 2020.13.65
		//				--> ��ݽ�λ --> 2021.1.65 --> -31 -->2021.2.34 --> -28 --> 2021.3.6
		
		_day += day; 

		//�ж������Ƿ����
		while (_day > getMonthDay(_year, _month)) {
			//��ȥ���µ�����, �·ݽ�λ
			_day -= getMonthDay(_year, _month);
			++_month;
			//�ж��·��Ƿ����
			if (_month == 13) {
				//��λ����һ���1��
				_month = 1;
				_year++;
			}
		}

		return *this;
	}

	//ǰ��++ :   ++d    	��++, ����++֮���ֵ
	Date& operator++() {
		*this += 1;
		return *this;
	}

	//����++ :  d++   ����++, ����++֮ǰ��ֵ
	//ǰ�ú���++���ǵ�Ŀ�����
	//���Ϊ��Ա����, �����ϲ���Ҫ��ʽ����, ���������Զ�����thisָ��
	//int: ����ββ�����һ�������Ĳ���, ֻ��һ����ǲ���, ���������������Ķ���,ͨ���﷨������, ���Խ���Ϊ����++ 
	Date operator++(int) {
		//����++֮ǰ��ֵ
		Date ret(*this);
		//++
		*this += 1;
		//����++֮ǰ��ֵ
		return ret;
	}


	void print() {
		cout << _year << "-" << _month << "-" << _day << endl;
	}

	//���� -= ����
	Date& operator-=(int day) {
		//a -= -b  -->  a += b
		if (day < 0) {
			return *this += (-day);
		}
		
		_day -= day;	
		//2020.5.24 - 30 --> 2020.5.-6 --> +30 --> �·���λ --> 2020.4.24

		//�ж�_day�Ƿ��Ǹ�ֵ
		while (_day <= 0) {
			//�·���λ, �ټӵ��µ�����
			_month--;
			//�ж��·��Ƿ���0
			if (_month == 0) {
				_month = 12;
				//�����λ
				_year--;
			}
			//����ټ�, ��Ϊ�·ݺ������ʱ��ȷ��
			_day += getMonthDay(_year, _month);
		}

		return *this;
	}

	//ǰ��--:  --d
	Date& operator--() {
		*this -= 1;
		return *this;
	}

	//����--:  d--
	Date operator--(int) {
		Date ret(*this);
		*this -= 1;
		return ret;
	}

	//���� + ����
	//�����ǲ��ܱ��, ���ص�����ӵĽ��
	//+ - �����: �����޸Ĳ�����������
	Date operator+(int day) {
		Date ret(*this);
		ret += day;
		return ret;
	}

	//���� - ����
	Date operator-(int day) {
		Date ret(*this);
		ret -= day;
		return ret;
	}
	
	//�߼������
	bool operator==(const Date& date) {
		return _year == date._year
			&& _month == date._month
			&& _day == date._day;
	}

	bool operator>(const Date& date) {
		if (_year > date._year)
			return true;
		else if (_year == date._year) {
			if (_month > date._month)
				return true;
			else if (_month == date._month) {
				if (_day > date._day)
					return true;
			}
		}
		return false;
	}

	//���븴��, ���ܼ򻯴���, �������ά��Ч��
	bool operator>=(const Date& date) {
		return (*this > date) || (*this == date);
	}

	bool operator<(const Date& date) {
		return !(*this >= date);
	}

	bool operator<=(const Date& date) {
		return !(*this > date);
	}

	bool operator!=(const Date& date) {
		return !(*this == date);
	}

	//����Date�������
	int operator-(Date& date) {
		Date d1(*this);
		Date d2(date); 

		int num = 0;
		if (d1 > d2) {
			while (d1 > d2) {
				d1--;
				num++;
			}
			return num;
		}
		else {
			//d1 <= d2
			while (d1 < d2) {
				d1++;
				num++;
			}
			return -num;
		}
	}

//private:
	int _year;
	int _month;
	int _day;
};

ostream& operator<<(ostream& _cout, const Date& date)
{
	_cout << date._year << " " << date._month << " " << date._day << endl;
	return _cout;
}


void test() {
	//���� +=
	Date d(2020, 5, 1);
	d.print();
	d += 20;
	d.print();
	d += 20;
	d.print();

	Date d2(2020, 12, 6);
	d2.print();
	d2 += 90;
	d2.print();
	d2 += 3650;
	d2.print();

	//����++
	//ǰ��++
	++d2;
	d2.operator++();
	d2.print();
	//����++
	d2.operator++(0);
	d2.print();
	d2++;
	d2.print();
}

void test2() {
	//����ǰ�úͺ���++������
	Date d(2020, 5, 20);
	d.print();
	cout << "ǰ��++ " << endl;
	cout << (++d) << endl;
	d.print();
	cout << "����++ " << endl;
	cout << (d++) << endl;
	d.print();
}


void test3() {
	//����--
	Date d(2020, 5, 24);
	d.print();
	d -= 30;
	d.print();
	d -= -30;
	d.print();
	d -= 3650;
	d.print();

}


void test4() {
	//�����߼������
	Date d1(2020, 5, 25);
	Date d2(2020, 5, 25);
	Date d3(2020, 5, 26);
	Date d4(2020, 5, 23);

	cout << (d1 > d4) << endl;
	cout << (d1 >= d4) << endl;
	cout << (d1 < d4) << endl;
	cout << (d1 <= d4) << endl;
	cout << (d3 > d1) << endl;
	cout << (d1 > d4) << endl;
	cout << (d1 == d2) << endl;
	cout << (d1 == d4) << endl;

}


void test5() {
	//�������ڲ������
	Date d1(2020, 5, 25);
	Date d2 = d1 + 3650;

	cout << (d1 - d2) << endl;
	cout << (d2 - d1) << endl;

	Date d3 = d2 + 200;
	cout << (d3 - d2) << endl;
	cout << (d2 - d3) << endl;
}


int main() {
	//test();
	//test2();
	//test3();
	//test4();
	test5();

	return 0;
}