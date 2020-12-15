#include<iostream>
#include<string>

using namespace std;


class Person {
public:
	void print() {
		cout << "name:" << _name << endl;
		cout << "age:" << _age << endl;
	}


	void func() {
		cout << "Person::func()" << endl;
	}

protected:
	string _name = "monster"; // 姓名
	int _age = 18; // 年龄

//private:
	int _id = 0; // 父类作用域
};


//学生类 : 公有继承Person
class Student : public Person {
public:
	void setID() {
		//基类的私有成员在子类中不可见. 但是确实被子类继承下来了
		_id = 10;

		//设置子类中的id, 
		//同名隐藏 :  父类中继承的同名id被隐藏
		_id = 100;

		//通过父类作用域来访问父类中的同名变量
		Person::_id = 200;
	}

	/*
		同名隐藏 : 函数也会同名隐藏, 只要函数名相同就会隐藏, 不管参数有没有
		不是函数重载, 因为函数重载的前提是在同一作用域下
		(同样可以通过父类作用域访问父类的同名函数)
		不过一般不要写同名的成员, 给自己挖坑不好哇
	*/
	void func(int a) {
		cout << "Student::func()" << endl;
	}


	void setName() {
		//基类的保护成员在子类可见, 在类外不可见
		_name = "123456";
	}

//protected:
	int _stuid = 2018; // 学号   
	int _id = 5; //子类作用域
};


class Teacher : public Person {
protected:
	int _jobid = 2022; // 工号
};

void Test() {
	Student s;
	s.func(10);
	s.Person::func();
}


void test() {
	cout << sizeof(Person) << endl;
	cout << sizeof(Student) << endl;

	Person p;
	Student s;
}


void test2() {
	int a = 2.5; //隐式类型转换

	Person p;
	Student s;
	s.setName();
	//"切片"操作 :  子类 --> 父类   (向上转型)  给的东西是多的, 切一下正好
	//用子类给父类赋值, 把子类中属于父类的内容切过去
	p = s;		
	Person* ptr = &s;  
	Person& ref = s;   


	
	//父类对象不能转为子类对象  (向下转型, 给的东西少了, 多出来的内容赋哪去?)
	//s = p;
	//s = (Student)p;


	//父类指针/引用不能转换为子类的指针/引用
	//强转可以转, 但不安全, 访问不到子类中新增的成员
	//Student* ptr2 = &p;
	Student* ptr2 = (Student*)&p;
	//Student& ref2 = p;
	Student& ref2 = (Student&)p;
	
	//越界访问, 虽然没报错, 但已经越界了
	ptr2->_stuid = 2;
	ref2._stuid = 10;
}




class A {
public:
	A() {
		cout << "A()" << endl;
	}

	A(int a)
		: _a(a) {
		cout << "A()" << endl;
	}

	A(const A& a) {
		cout << "A(const A& a)" << endl;
	}

	A& operator=(const A& a) {
		cout << "operator=(const A& a)" << endl;
		return *this;
	}
	
	~A() {
		cout << "~A()" << endl;
	}

private:
	int _a;
};


class B : public A {
public:
	/*
		父类构造在子类构造初始化列表处自动调用
		先执行父类的构造函数, 再执行子类的构造函数
		如果父类没有默认构造, 则需要显式指定  (在初始化列表中指定)
	 */
	B() 
		:A(5) {
		cout << "B()" << endl;
	}

	//继承自父类的成员必须调动父类构造完成初始化
	//不能在子类构造中进行初始化
	B(int a, int b)
		:A(a)
		, _b(b) {
		cout << "B(int, int)" << endl;
	}

	//错误代码: 
	//B(int a, int b)
	//	:_a(a) {}

	/*
	*	没有显式定义子类的拷贝构造:
	*		调用父类的拷贝构造
	* 
	*	显式定义子类的拷贝构造:
			默认先调用父类的构造函数, 然后再调用子类的拷贝构造
			显式指定调用父类的拷贝构造, 则会先调用父类的构造函数, 然后再调用子类的拷贝构造
	*/
	B(const B& b) 
		: A(b) {
		cout << "B(const B& b)" << endl;
	}

	/*
		没有显式定义子类的赋值: 
			默认调用父类的赋值

		显式定义子类的赋值: 
			默认调用子类的赋值, 不会调用父类的赋值

		与父类的赋值运算符构成同名隐藏
		如果要调用父类的赋值, 要加父类的作用域
	 */
	B& operator=(const B& b) {
		A::operator=(b);
		cout << "operator=(const B& b)" << endl;
		return *this;
	}

	/*
		调用顺序和构造相反
			先调用子类的析构, 再调父类析构

		底层编译之后子类析构和父类析构函数名相同, 构成同名隐藏
		想调用父类析构要加父类作用域

		编译器在任何情况下都会自动调用父类的析构
			不需要在子类析构函数中显式调用父类析构, 否则会导致父类析构被调用两次, 造成二次释放
	*/
	~B() {
		cout << "~B()" << endl;
	}

private:
	int _b = 0;
};


void test3() {
	//创建子类对象的时候, 会自动调动父类的默认构造
	//B b;
	//B b2 = b;

	//B b(1, 2);
	//B b2(3, 4);
	//b = b2;

	B b;
	//B b1;
}


/*
	友元关系不能继承, 基类的友元不能访问子类的成员
		我不认识我父母的朋友..很正常嘛
*/

/*
	基类定义的静态成员, 则整个继承体系中只有这一个静态成员
	无论派生了多少类, 这些类都共享一个静态成员
*/
class C {
public:
	static int _i;
};
int C::_i = 0;

class D : public C {

};

class E : public D {

};

void test4() {
	C c;
	D d;
	E e;
	cout << &c._i << endl;
	cout << &d._i << endl;
	cout << &e._i << endl;
}


//菱形继承
class AA {
public:
	int _aa;
};

class BB : virtual public AA {   //AA::_aa
public:
	int _bb;
};

class CC : virtual public AA {   //AA::_aa
public:
	int _cc;
};

class DD : public BB, public CC {   //BB::_a   CC::_a
public:
	int _dd;
};

void test5() {
	DD d;
	//内存按照继承顺序排列 :  先存放继承的父类(按顺序), 然后存放自己的成员

	//菱形继承: 公共的基类成员会存在两份, 数据冗余, 且使用时要加作用域, 比较麻烦 
	d.BB::_aa = 1;
	d._bb = 2;
	d.CC::_aa = 5;
	d._cc = 3;
	d._dd = 4;

	/*
	*	解决菱形继承数据冗余和二义性的问题
		虚拟继承 : 在具有公共基类的两个父类的继承方式前 加上virtual
			虚基表的概念
	*/
	d._aa = 8;


	//组合, 继承
}


int main() {
	//test();
	//test2();
	//test3();
	//test4();
	test5();
	//Test();

	return 0;
}