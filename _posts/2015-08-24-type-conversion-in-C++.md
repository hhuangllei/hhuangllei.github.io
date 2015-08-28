---
layout: post
title: C++中的类型转换
categories: [coding, job]
modify_date: 2015-08-28 11:30:00 +0800
---

在C/C++中，关于类型转换，主要涉及**隐式类型转换**和**显式类型转换**。

### 隐式类型转换

隐式类型转换，转换规则由编译器自动执行，无需程序员介入——有时甚至不需要程序员了解。

比如：`int ival = 0;`随后执行`ival = 3.14 + 3`，首先为防止精度损失，先将3从int转换为double，计算得到6.14，再截尾转换为int。

隐式类型转换编译器自动执行，所以不是本文的重点。

### 显式类型转换

显式类型转换，也称为强制类型转换（cast）。包括C++风格的命名强制类型转换和C风格的旧式强制类型转换。

* C++风格的命名强制类型转换（Named Casts）

包含static_cast, dynamic_cast, const_cast, reinterpret_cast命名的强制类型转换符号的一般形式如下：

cast-name<type>(expression);

1. static_cast

	编译器隐式执行的任何类型转换都可以由static_cast显式完成。允许执行任意的隐式转换和相反转换动作（即使它是不允许隐式的）。例如：应用到类的指针上，意思是说它允许子类类型的指针转换为父类类型的指针（这是一个有效的隐式转换），同时，也能够执行相反动作：转换父类为它的子类。

	注意：**使用static_cast将父类转换为子类时，不检查是否有效，不管是否能完整转换，这是与dynamic_cast的主要区别**。
  
2. dynamic_cast

	支持运行时识别指针或引用所指向的对象。**只用于对象的指针和引用**，当用于**多态类型**时，它允许任意的隐式类型转换以及相反过程。
  
	注意在隐式转化的相反过程（父类 -> 子类），dynamic_cast会检查操作是否有效。也就是说，它会检查转换是否会返回一个被请求的有效的完整对象。检测在运行时进行。 如果被转换的指针不是一个被请求的有效完整的对象指针，返回值为NULL。对于引用类型，会抛出bad_cast异常。

3. const_cast

	操纵传递对象的const属性，或者是设置或者是移除。
	
	注意：**只有使用const_cast才能将const性质转换掉**。在这种情况下，试图使用其他三种形式的强制转换都会导致编译时的错误。类似地，除了添加或删除const特性，用const_cast符来执行其他任何类型转换，都会引起编译错误。
  
4. reinterpret_cast

	转换一个指针为其它类型的指针。它也允许从一个指针转换为整数类型，反之亦然。这个操作符能够在非相关的类型之间转换。操作结果只是简单的从一个指针到别的指针的值的二进制拷贝。在类型之间指向的内容不做任何类型的检查和转换。

	通常为操作数的位模式提供较低层次的重新解释。本质上依赖于机器。为了安全地使用reinterpret_cast，要求程序员完全理解所涉及的数据类型，以及编译器实现强制类型转换的细节。

	
给出代码示例：

{% highlight C++ %}
#include <iostream>

using namespace std;

class Base
{
public:
	int a;
	
	Base(): a(0){}
	Base(int a): a(a){}
	virtual void Print() const
	{
		cout << this->a << endl;
	}
};
class Derive: public Base
{
public:
	int b;
	Derive(): Base(0), b(0){}
	Derive(int a, int b): Base(a), b(b){}
	void Print() const
	{
		cout << this->a << "\t" << this->b << endl;
	}
};
int main()
{
	Base *p = new Base();
	const Base *const_p = new Base();
	
	cout << "test const\nbefore: " << endl;
	p->Print();
	const_p->Print();
	
	p->a = 1;
	//const_p->a = 2; // 编译失败
	
	Base *t = const_cast<Base *>(const_p); // C++风格强制类型转换
	//Base *t = (Base *)const_p; // C风格强制类型转换
	//Base *t = static_cast<Base *>(const_p); // 编译失败
	//Base *t = reinterpret_cast<Base *>(const_p); // 编译失败
	//Base *t = dynamic_cast<Base *>(const_p); // 编译失败
	t->a = 2;
	
	cout << "after: " << endl;
	p->Print();
	const_p->Print();
	
	
	///////////////////////////////////////////////
	Base *b1 = new Base(1);
	Base *b2 = new Derive(1, 2);
	Derive *d1 = NULL;
	Derive *d2 = NULL;
	
	cout << "<<<<<<<<<<<<<<\n\ntest Base -> Derive\nbefore: " << endl;
	b1->Print();
	b2->Print();
	
	// Base -> Derive，不检查是否有效
	d1 = static_cast<Derive *>(b1);
	d2 = static_cast<Derive *>(b2);
	
	cout << "after: " << endl;
	if (d1)
		d1->Print();
	else
		cout << "NULL" <<endl;	
	d2->Print();
	
	// dynamic_cast Base->Derive要求多态，必须在Base的函数加virtual修饰
	// 否则编译失败，提示"source type is not polymorphic"
	d1 = dynamic_cast<Derive *>(b1); // 要检查是否有效，无效即不能完整转换，返回NULL
	d2 = dynamic_cast<Derive *>(b2);
	
	cout  << endl;
	if (d1)
		d1->Print();
	else
		cout << "NULL" <<endl;	
	d2->Print();
	
	
	//////////////////////////////////////////////////
	d1 = new Derive(3, 4);
	cout << "<<<<<<<<<<<<<<\n\ntest Derive -> Base\nbefore: " << endl;
	d1->Print();
	
	
	// Base -> Derive，不检查是否有效
	b1 = static_cast<Base *>(d1);	
	
	cout << "after: " << endl;
	if (b1)
		b1->Print();
	else
		cout << "NULL" <<endl;		
	
	// dynamic_cast Derive->Base不要求多态
	b1 = dynamic_cast<Base *>(d1); // 要检查是否有效，无效即不能完整转换，返回NULL	
	
	cout  << endl;
	if (b1)
		b1->Print();
	else
		cout << "NULL" <<endl;	
	
	return 0;
}
{% endhighlight %}

运行结果如下：

{% highlight bat %}
test const
before:
0
0
after:
1
2
<<<<<<<<<<<<<<

test Base -> Derive
before:
1
1       2
after:
1
1       2

NULL
1       2
<<<<<<<<<<<<<<

test Derive -> Base
before:
3       4
after:
3       4

3       4
{% endhighlight %}

* C风格的旧式强制类型转换（Old-Style Casts）

有两种形式：

type (expr); // Function-style cast notation

(type) expr; // C-language-style cast notation

旧式强制转换依赖于所涉及的数据类型，具有与const_cast、static_cast和reinterpret_cast一样的行为。在合法使用static_cast或const_cast的地方，旧式强制转换提供了与各自对应的命名强制转换一样的功能。如果这两种强制转换均不合法，则旧式强制转换执行reinterpret_cast功能。给出示例如下：

{% highlight C++ %}
int ival; double dval;
ival += int (dval);         // static_cast: converts double to int
const char* pc_str;
string_copy((char*)pc_str); // const_cast: casts away const
int *ip;
char *pc = (char*)ip;       // reinterpret_cast: treats int* as char*
{% endhighlight %}


标准C++为了加强类型转换的可视性，引入命名的强制转换操作符，为程序员在必须使用强制转换时提供了更好的工具。例如，非指针的static_cast和const_cast要比reinterpret_cast更安全。结果使程序员（以及读者和操纵程序的工具）可清楚地辨别代码中每个显式的强制转换潜在的风险级别。


参考文献：

* http://www.cnblogs.com/CBDoctor/archive/2011/12/06/2277918.html

* http://blog.chinaunix.net/uid-26548237-id-3954104.html
