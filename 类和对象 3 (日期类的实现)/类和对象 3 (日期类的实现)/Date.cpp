#include<iostream>

using namespace std;

class Date {
public:
	//构造函数
	Date(int year = 2000, int month = 9, int day = 28) {
		//判断日期是否合法
		if (year > 0 && month > 0 && month <= 12
			&& day > 0 && day <= getMonthDay(year, month)) {

			_year = year;
			_month = month;
			_day = day;
		}
		else {
			cout << "日期不合法: " << year << "-" << month << "-" << day << endl;
			cout << "重置为默认值: 2000-1-1";
			_year = 2000;
			_month = 1;
			_day = 1;
		}
	}

	//获取某个月的天数
	int getMonthDay(int year, int month) {
		static int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		int day = days[month];

		//如果是2月且为闰年, +1
		if (month == 2
			&& (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
			++day;

		return day;
	}

	// 日期 += 天数
	Date& operator+=(int day) {
		//a += -b --> a -= b
		if (day < 0) {
			return *this -= day;
		}
		//2020.5.1 + 20  --> 2020.5.21
		//2020.5.21 + 20  --> 2020.5.41  --> 进位 --> -31 -->月份进位 --> 2020.6.10
		//2020.12.6 + 90 --> 2020.12.96 --> 进位 --> -31 -->月份进位 --> 2020.13.65
		//				--> 年份进位 --> 2021.1.65 --> -31 -->2021.2.34 --> -28 --> 2021.3.6
		
		_day += day; 

		//判断日期是否溢出
		while (_day > getMonthDay(_year, _month)) {
			//减去当月的天数, 月份进位
			_day -= getMonthDay(_year, _month);
			++_month;
			//判断月份是否溢出
			if (_month == 13) {
				//进位到下一年的1月
				_month = 1;
				_year++;
			}
		}

		return *this;
	}

	//前置++ :   ++d    	先++, 返回++之后的值
	Date& operator++() {
		*this += 1;
		return *this;
	}

	//后置++ :  d++   本身++, 返回++之前的值
	//前置后置++都是单目运算符
	//如果为成员函数, 则本质上不需要显式传参, 编译器会自动传入this指针
	//int: 这个形参并不是一个真正的参数, 只是一个标记参数, 编译器看到这样的定义,通过语法树搜索, 可以解释为后置++ 
	Date operator++(int) {
		//保存++之前的值
		Date ret(*this);
		//++
		*this += 1;
		//返回++之前的值
		return ret;
	}


	void print() {
		cout << _year << "-" << _month << "-" << _day << endl;
	}

	//日期 -= 天数
	Date& operator-=(int day) {
		//a -= -b  -->  a += b
		if (day < 0) {
			return *this += (-day);
		}
		
		_day -= day;	
		//2020.5.24 - 30 --> 2020.5.-6 --> +30 --> 月份退位 --> 2020.4.24

		//判断_day是否是负值
		while (_day <= 0) {
			//月份退位, 再加当月的天数
			_month--;
			//判断月份是否是0
			if (_month == 0) {
				_month = 12;
				//年份退位
				_year--;
			}
			//最后再加, 因为月份和年份这时才确定
			_day += getMonthDay(_year, _month);
		}

		return *this;
	}

	//前置--:  --d
	Date& operator--() {
		*this -= 1;
		return *this;
	}

	//后置--:  d--
	Date operator--(int) {
		Date ret(*this);
		*this -= 1;
		return ret;
	}

	//日期 + 天数
	//日期是不能变的, 返回的是相加的结果
	//+ - 运算符: 不能修改操作数的内容
	Date operator+(int day) {
		Date ret(*this);
		ret += day;
		return ret;
	}

	//日期 - 天数
	Date operator-(int day) {
		Date ret(*this);
		ret -= day;
		return ret;
	}
	
	//逻辑运算符
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

	//代码复用, 既能简化代码, 又能提高维护效率
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

	//两个Date差的天数
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
	//测试 +=
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

	//测试++
	//前置++
	++d2;
	d2.operator++();
	d2.print();
	//后置++
	d2.operator++(0);
	d2.print();
	d2++;
	d2.print();
}

void test2() {
	//看看前置和后置++的区别
	Date d(2020, 5, 20);
	d.print();
	cout << "前置++ " << endl;
	cout << (++d) << endl;
	d.print();
	cout << "后置++ " << endl;
	cout << (d++) << endl;
	d.print();
}


void test3() {
	//测试--
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
	//测试逻辑运算符
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
	//测试日期差的天数
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