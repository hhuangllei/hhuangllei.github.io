---
layout: post
title: 使用自定义比较函数的sort
categories: [coding]
modify_date: 2015-09-14 20:00:00 +0800
---

sort排序函数，在C/C++, C#等不同编程语言中，都经常使用。在排序结构体、类等情况下，需要自定义比较函数，因为不同编程语言关于比较函数的定义存在一些差异，总是搞混而不得不重新查阅。所以这次就总结下，sort的自定义比较函数。

### C/C++中的sort

经常用到的有

* <cstdlib> qsort

{% highlight C++ %}
void qsort (void* base, size_t num, size_t size,
            int (*compar)(const void*,const void*));
{% endhighlight %}

关于`int compar (const void* p1, const void* p2);`，注意函数参数类型为`const void *`，此外返回值说明如下：

return <0, *p1 goes before *p2

return =0, *p1 equivalent to *p2

return >0, *p1 goes after *p2

* <algorithm> sort

{% highlight C++ %}
template <class RandomAccessIterator>
  void sort (RandomAccessIterator first, RandomAccessIterator last);

template <class RandomAccessIterator, class Compare>
  void sort (RandomAccessIterator first, RandomAccessIterator last, Compare comp);
{% endhighlight %}

关于`Compare comp`，返回值为bool，说明如下：

return true, first argument is considered to go before the second

return false, other conditions

* <list> sort


测试代码：

{% highlight C++ %}
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

class Unit
{
public:
	int m_index;
	int m_val;

	Unit(): m_index(), m_val() {}
	Unit(int index, int val) : m_index(index), m_val(val){}

	void Print()
	{
		cout << '(' << m_index << ", " << m_val << ")";
	}
};
bool Comp(const Unit &a, const Unit &b)
{
	return a.m_val < b.m_val; // 不能为<=，否则因不能判断元素顺序而出错
}
int CompInt(const void *a, const void *b)
{	
	return (*(int*)a - *(int*)b);
}

int main()
{
	vector<Unit> vec;
	int arr[] = { 3, 1, 2, 4 };
	for (int i = 0; i < 4; ++i)
	{
		vec.push_back(Unit(i + 1, arr[i]));
	}
	
	sort(vec.begin(), vec.end(), Comp);
	
	for (int i = 0; i < vec.size(); ++i)
	{
		vec[i].Print();
		cout << endl;
	}

	// C qsort
	cout << "before: ";
	for (int i = 0; i < 4; ++i)
		cout << arr[i] << " ";
	cout << endl;
	qsort(arr, 4, sizeof(int), CompInt);
	cout << "after: ";
	for (int i = 0; i < 4; ++i)
		cout << arr[i] << " ";
	cout << endl;

	getchar();
	return 0;
}
{% endhighlight %}

运行结果：

{% highlight bat %}
(2, 1)
(3, 2)
(1, 3)
(4, 4)
before: 3 1 2 4
after: 1 2 3 4
{% endhighlight %}

### C#中的sort

List中的sort为例，sort有4种参数形式：

* Sort()

默认比较的类型实现`IComparer<T>`接口。

* Sort(Comparison<T>)

与C中的qsort定义的比较函数类似，在C#中则叫做委托，具体定义如下：

{% highlight C# %}
public delegate int Comparison<in T>(
	T x,
	T y
)
{% endhighlight%}

因此比较函数可以是自定义的非匿名函数，可以是Lambda表达式定义的匿名函数，也可以是delegate委托定义的匿名函数。

* Sort(IComparer<T>)

{% highlight C# %}
public interface IComparer<in T>

int Compare(
	T x,
	T y
)

{% endhighlight%}

`IComparer`接口，需要实现`Compare`函数。有两种形式：一种是直接在定义class自定类型时实现该接口，之后就可以直接调用`Sort()`；另一种是专门定义一个实现该接口的类，调用`Sort(IComparer<T>)`来排序。

注意`Compare`为`public int`。

* Sort(Int32, Int32, IComparer<T>)


测试代码：

{% highlight C# %}
namespace Test
{
    class Comparer : IComparer<int>
    {
        public int Compare(int a, int b)
        {
            return a - b;
        }
    }
    class Example
    {
        private static int Comp(int a, int b)
        {
            return a - b;
        }
        static void Main()
        {
            List<int> list = new List<int>() { 3, 4, 1, 2 };

            Console.WriteLine("before: ");
            for (int i = 0; i < list.Count; ++i)
                Console.Write("{0} ", list[i]);
            Console.WriteLine();

            //list.Sort();
            //list.Sort(Comp); // 自定义比较函数
            //list.Sort((a, b) => a - b); // Lambda表达式，匿名函数
            //list.Sort(delegate(int a, int b) { return a - b; }); // 委托，匿名函数
            // list.Sort(new Comparer());
            list.Sort(1, 2, new Comparer());

            Console.WriteLine("before: ");
            for (int i = 0; i < list.Count; ++i)
                Console.Write("{0} ", list[i]);
            Console.WriteLine();


        }
    }
}
{% endhighlight %}

参考文献：

* http://www.cplusplus.com/reference/algorithm/sort/
* https://msdn.microsoft.com/en-us/library/w56d4y5z(v=vs.110).aspx
* https://msdn.microsoft.com/en-us/library/234b841s(v=vs.110).aspx
* http://blog.csdn.net/think_soft/article/details/3446393