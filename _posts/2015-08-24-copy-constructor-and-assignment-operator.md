---
layout: post
title: 拷贝构造函数与赋值函数
categories: [coding, job]
modify_date: 2015-08-24 20:30:00 +0800
---

C++类默认产生4个成员函数：**默认构造函数，析构函数，拷贝构造函数，赋值函数**，前两面两种还比较熟悉，但关于**拷贝构造函数**和**赋值函数**就有些遗忘了，后两个主要是用作**深拷贝**。当类成员分配内存、指针等，就需要深拷贝来解决内存问题。

* 拷贝（复制）构造函数

`A(const A &a)`

注意两点：一是构造函数无返回值；二是参数为const的类引用，如果参数是const A a，不是引用，编译失败。

关于调用问题，容易与赋值函数混淆，当类不存在时就调用拷贝构造函数（前面有声明）。

A a; // 默认构造函数

A b = a; // 拷贝构造函数，等价于A b(a);

* 赋值函数（赋值操作符重载）

`A &operator =(const A &a)`

注意两点：一是返回值为引用，左值；二是参数为const的类引用。

如果参数不是引用，即`A &operator =(const A a)`，会在函数开始时拷贝构造一个临时变量，函数结束时再进行析构

如果返回值为类，即`A operator =(const A &a)`，会在函数结束返回时拷贝构造一个临时变量，函数结束时再进行析构

测试代码：

{% highlight C++ %}
#include <iostream>

using namespace std;

class A
{
public:
	// 构造函数
	A()
	{
		m_i = ++i;
		cout << "constructor 构造函数 A() " << m_i << endl;
	}
	
	A(int m)
	{
		m_i = ++i;
		cout << "constructor 构造函数 A(i) " << m_i << endl;
	}
	
	A(const A &a)
	{
		m_i = ++i;
		cout << "copy constructor 拷贝构造函数 " << m_i << endl;
	}
	
	// 标准的赋值操作符重载应该返回引用，否则在函数结束返回时拷贝构造一个临时变量，函数结束时再进行析构
	// 参数应该为const引用，如果不使用引用，在函数开始时拷贝构造一个临时变量，函数结束时再进行析构
	A &operator =(const A &a) 
	{
		cout << "assignment operator 赋值操作符 " << m_i << endl;
		
		if (this == &a)
			return *this;
		return *this;
	}
	
	~A()
	{
		cout << "destructor 析构函数 " << m_i << endl;
	}
	
private:
	static int i;
	int m_i;
};

int A::i = 0;

int main()
{
	A a; // 默认无参构造函数不要加括号，A a();, 这会和函数声明混淆。
	A b;	
	A c = a; // A c(a);
	c = b;	
	
	A d = 1; // A d(1);
	
	return 0;
}
{% endhighlight %}

在VS2013和G++测试下，输出结果：

{% highlight bat %}
constructor 构造函数 A() 1
constructor 构造函数 A() 2
copy constructor 拷贝构造函数 3
assignment operator 赋值操作符 3
constructor 构造函数 A(i) 4
destructor 析构函数 4
destructor 析构函数 3
destructor 析构函数 2
destructor 析构函数 1
{% endhighlight %}

参考文献：

* http://www.cnblogs.com/GODYCA/archive/2013/01/16/2862885.html
