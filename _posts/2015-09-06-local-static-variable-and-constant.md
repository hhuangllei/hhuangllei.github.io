---
layout: post
title: 局部静态变量与字符串常量
categories: [coding, job]
modify_date: 2015-09-06 10:00:00 +0800
---

在C/C++中，内存分为：堆、栈、自由存储区（存在争议，有说是malloc对应的内存区域，但堆内存区域new底层一般也是使用malloc，个人更倾向于自由存储区等价于堆）、全局/静态存储区和常量存储区（称为文字常量区更好，不是指用const修饰的变量，而是"abc"这种字符串常量，文字常量，Character String Literals，字符串字面值）。
局部静态变量，存储在全局/静态存储区；常量，存储在常量存储区。这两个概念经常出现在笔试题中，如果没有掌握这些知识点，就很容易出错。

### 局部静态变量

局部静态变量，主要是考察初始化和作用域。**静态局部变量是在编译时进行初始化，即只赋初值一次**，只在第一次进入时进行初始化，以后每次调用函数时不再重新赋初值而只是保留上次函数调用结束时的值。而为自由变量赋初值，不是在编译时进行的，而是在函数调用时进行，每调用一次函数重新给一次初值，相当于执行一次赋值语句。

测试代码：

{% highlight C++ %}
#include <iostream>
#include <cstdio>

using namespace std;

void fun()
{
	int a = 0; // 局部自由变量
	static int b = 0; // 局部静态变量，只在第一次进入时执行
	static int *p = new int[10]; // 局部静态变量，只在第一次进入时执行
	
	++a, ++b;
	printf("a = %d\n", a);
	printf("b = %d\n", b);
	printf("p = %x\n", p);
}

int main()
{
	for (int i=0; i<2; ++i)
	{
		cout << "turn " << i << endl;
		fun();
	}

	return 0;
}
{% endhighlight %}

运行结果：

{% highlight bat %}
turn 0
a = 1
b = 1
p = 640e70
turn 1
a = 1
b = 2
p = 640e70
{% endhighlight %}

### 字符串常量

字符串常量，也有叫做文字常量、字符串字面值，如"abc"，主要是考察字符串常量不能修改和常量指针地址。

测试代码：

{% highlight C++ %}
#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
	const char *str = "test";
	const char *str2 = "test";
	const char *str3 = "test1";
	char buf[] = "test";
	char *p = "test";
	
	// p[1] = 'T'; // 运行报错
	
	printf("%x\t%x\t%x\t%x\t%x\n", str, str2, str3, buf, p);
	
	cout << (str == "test") << endl;
	cout << ("test" == "test") << endl;

	return 0;
}
{% endhighlight %}

运行结果：

{% highlight bat %}
405064  405064  405069  28febb  405064
1
1
{% endhighlight %}

参考文献：

* http://www.cnblogs.com/GODYCA/archive/2013/01/16/2862885.html
