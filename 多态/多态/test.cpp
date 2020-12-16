#include<iostream>

using namespace std;


class AA { };

class BB : public AA { };



/*
*	实现多态 (前提: 继承)

	调用函数产生多态的行为 :
		1. 函数必须为虚函数  virtual 函数
		2. 虚函数需要在子类中重写
		3. 调用虚函数时, 必须用指针或者引用调用
*/

class Person {
public:
	virtual void buyTicket() {
		cout << "普通票 -- 全价" << endl;
	}

	//virtual AA* buyTicket() {
	//	cout << "普通票 -- 全价" << endl;
	//	return &AA();
	//}

};

class Student : public Person {
public:
	/*
		子类进行虚函数的重写
		子类重新定义一个和父类接口完全相同的函数 (函数名, 参数, 返回值都相同)

		只有一种特例 :  协变  (返回值可以不同)
			但返回值必须是构成父子继承关系的指针/引用
			一般不要写特殊, 别搞
	*/
	virtual void buyTicket() {
		cout << "学生票 -- 半价" << endl;
	}

	//virtual BB* buyTicket() {
	//	cout << "学生票 -- 半价" << endl;
	//	return &BB();
	//}

	~Student() {

	}
};


void func(Person* p) {
	p->buyTicket();
}

void func(Person p) {
	p.buyTicket();
}

void test() {
	Person p;
	Student s;

	Person* pp = &p;
	Student* ps = &s;

	//这就是用指针调了一下对应的函数而已, 不是多态
	pp->buyTicket();
	ps->buyTicket();
	cout << endl;

	// 多态 : 看对象
	func(&p); 
	func(&s);
	cout << endl;

	// 非多态 : 看类型
	func(p);
	func(s);
	cout << endl;
}



class A {
public:
	//析构尽量写成虚函数
	virtual ~A() {
		cout << "~A()" << endl;
	}

	//花里胡哨写法 :  父类加virtual, 子类不加, 子类构成多态
	//               父类不加virtual, 子类加了, 这时子类不构成多态 
	//      所以一般是虚函数都加上virtual, 别给自己添麻烦


	//final关键字 : 修饰的虚函数, 在子类中不能再被重写  (体现了实现继承,  我继承下来直接用, 不必重写)
	virtual void func() final {
		cout << "A::func()" << endl;
	}

	virtual void func2() {
		cout << "A::func2()" << endl;
	}


	//纯虚函数   (没有函数体)
	//抽象类 :  包含纯虚函数的类
	//抽象类不能实例化 :  成员不完整
	//子类继承了抽象类, 必须实现纯虚函数, 如果不实现, 也是一个抽象类, 不能实例化

	//virtual void func4() = 0;

};

class B : public A {
public:
	//重写父类的析构函数 :  因为底层的函数名是相同的, 接口完全一致  (这么设计就是为了实现多态)
	virtual ~B() {
		cout << "~B()" << endl;
	}

	//override :  强制子类的函数必须重写父类的一个虚函数  (体现了接口继承, 我只用你的接口, 不用你的逻辑)
	//一般用于重写函数, 加一个以便自己区分是隐藏还是重写
	virtual void func2() override {
		cout << "B::func2()" << endl;
	}


	//重写父类中的纯虚函数
	virtual void func4() {
		cout << "B::func4()" << endl;
	}
};


void test2() {
	A* pa = new A;
	B* pb = new B;
	delete pa;
	delete pb;

	//切片 :  有内存泄漏的风险 (析构不是多态)
	//多态 :  看对象  --> 子类对象  -->  子类析构
	//用父类指针/引用 指向继承体系中的对象
	A* pc = new B;
	delete pc;   //只调用父类析构, 如果子类中有资源, 会造成内存泄漏, 子类的资源不会被释放
				 // 如果父类析构写成虚函数, 就解决了问题 ()
}



//class Base {
//public:
//	//使用虚函数后, 会在对象中存放一个虚表指针  
//	//(虚表 : 存放虚函数的地址, 是虚函数的指针数组)
//	//虚表指针指向虚表的首地址, 是二级指针  
//	virtual void func1() {
//		cout << "func1()" << endl;
//	}
//
//	virtual void func2() {
//		cout << "func2()" << endl;
//	}
//
//private:
//	int _a = 1;
//};
//
//void test3() {
//	cout << sizeof(Base) << endl;
//
//	//大致验证虚表指针存在哪
//
//	//数据段
//	static int si = 3;
//	//栈
//	int stackval = 2;
//	//堆
//	int* heapval = new int;
//	//代码段
//	const char* p = "123";
//
//	Base b;
//	//虚表指针 : 对象头4/8字节
//	int addr = *((int*) &b);  //获取对象头4个字节的内容
//	cout << "虚表指针: ";
//	printf("%p\n", addr);
//
//	printf("代码段: %p\n", p);	
//	printf("数据段: %p\n", &si);	
//	printf("堆: %p\n", &heapval);
//	printf("栈: %p\n", &stackval);
//
//	//大致可以证明在VS中, 虚表存在代码段
//		/*
//			虚表指针: 对象中   (存放虚表的首地址)
//			虚表: 代码段  (存放虚函数的首地址)
//			虚函数: 代码段
//		*/
//}



/*
	多态 : 看对象
		虚函数的行为 : 虚表中存放的实际地址决定

	多态过程 : 
		1. 首先通过指针/引用定位到实际的对象
		2. 从对象中获取实际虚表的首地址 (虚表指针)
		3. 从虚表中找到函数的实际地址
		最后执行
*/

class Base {
public:
	virtual void func1() { cout << "Base::func1" << endl; }
	virtual void func2() { cout << "Base::func2" << endl; }
private:
	int a;
};

class Derive : public Base {
public:
	virtual void func1() { cout << "Derive::func1" << endl; }
	virtual void func3() { cout << "Derive::func3" << endl; }
	virtual void func4() { cout << "Derive::func4" << endl; }
private:
	int b;
};

typedef void (*pfun)();

void printVfptr(pfun* vftable) {
	cout << "虚表地址: " << vftable << endl;

	for (; vftable != nullptr; ++vftable) {
		cout << "函数地址: " << *vftable << " ";
		(*vftable)();
		cout << endl;
	}
}


void test4() {
	Base b;
	pfun* vftable = (pfun*)*((int*)&b);
	(*vftable)();
	(*(vftable + 1))();

	Derive d;
	pfun* vftable2 = (pfun*)*((int*)&d);
	(*vftable2)();
	(*(vftable2 + 1))();
	(*(vftable2 + 2))();
	(*(vftable2 + 3))();


}



int main() {
	//test();
	//test2();
	//test3();
	test4();

	return 0;
}