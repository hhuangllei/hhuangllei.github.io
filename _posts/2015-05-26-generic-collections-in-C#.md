---
layout: post
title: C#中的常见容器的使用
categories: [coding]
modify_date: 2015-05-26 12:00:00 +0800
---

在C#中，经常会用到**System.Collections.Generic**中的容器，常见容器如下：

* List
* Dictionary
* HashSet
* SortedSet

List和Dictionary平时使用是最多的，而HashSet和SortedSet使用上会相对少一些，下面主要介绍几个知识点：

### 基于LINQ和Lambda表达式的排序

语言集成查询(LINQ)是一组技术的名称，这些技术建立在将查询功能直接集成到C#语言（以及Visual Basic和可能的任何其他.NET语言）的基础上。借助于LINQ，查询现在已是高级语言构造，就如同类、方法、事件等等。

Lambda表达式，作为一种语法糖，是一种可用于创建委托或表达式目录树类型的匿名函数。通过使用Lambda表达式，可以写入可作为参数传递或作为函数调用值返回的本地函数。Lambda表达式对于编写LINQ查询表达式特别有用。
若要创建Lambda表达式，需要在Lambda运算符 => 左侧指定输入参数（如果有），然后在另一侧输入表达式或语句块。例如，Lambda表达式`x => x * x`指定名为`x`的参数并返回`x`的平方值。

下面给出基于LINQ和Lambda表达式对List和Dictionary进行排序的示例：

{% highlight C# %}
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Test
{
    class Program
    {
        static void PrintList(List<int> list)
        {
            Console.WriteLine("In list:");
            foreach (var item in list)
                Console.Write("{0}\t", item);
            Console.WriteLine("\n");
        }

        static void PrintDict(Dictionary<int, int> dict)
        {
            Console.WriteLine("In dict:");
            foreach (var item in dict)
                Console.Write("({0}, {1})\t", item.Key, item.Value);
            Console.WriteLine("\n");
        }

        static void Main(string[] args)
        {            
            // test for List
            int [] array = {1, 3, 2};
            List<int> list = new List<int>(array);
            PrintList(list);
            //list.Sort();
            var query =
                from i in list
                orderby i descending
                select i;
            list = query.ToList();
            PrintList(list);

            // test for Dictionary
            Dictionary<int, int> dict = new Dictionary<int, int>();
            dict.Add(2, 1);
            dict.Add(1, 3);
            dict.Add(3, 2);
            PrintDict(dict);

            // 自带方法排序 + Lambda表达式
            dict = dict.OrderByDescending(o => o.Key).ToDictionary(o => o.Key, o => o.Value);
            PrintDict(dict);

            // LINQ排序 + Lambda表达式转Dictionary
            Dictionary<int, int> dict1 = (from o in dict orderby o.Key select o).ToDictionary(o => o.Key, o => o.Value);
            Dictionary<int, int> dict2 = (from o in dict orderby o.Value select o).ToDictionary(o => o.Key, o => o.Value);
                        
            PrintDict(dict1);
            PrintDict(dict2);            
        }
    }
}

{% endhighlight %}


### Dictionany自定义比较函数IEqualityComparer

Dictionary<TKey, TValue>构造函数 (IEqualityComparer<TKey>)：初始化 Dictionary<TKey, TValue> 类的新实例，该实例为空且具有默认的初始容量，并使用指定的 IEqualityComparer<T>。

给出官方示例代码如下，**但在代码中如果两个变量赋值不同，就不会进入自定义的比较函数**，感觉很奇怪，没搞懂C#字典内部比较机制。比如`Box blueBox = new Box(4, 4, 4);`。

{% highlight C# %}
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Test
{
    class Example
    {
        static void Main()
        {
            try
            {

                BoxEqualityComparer boxEqC = new BoxEqualityComparer();

                Dictionary<Box, String> boxes = new Dictionary<Box,
                                                    string>(boxEqC);

                Box redBox = new Box(4, 3, 4);
                Box blueBox = new Box(4, 3, 4);

                boxes.Add(redBox, "red");
                boxes.Add(blueBox, "blue");

                Console.WriteLine(redBox.GetHashCode());
                Console.WriteLine(blueBox.GetHashCode());
            }
            catch (ArgumentException argEx)
            {

                Console.WriteLine(argEx.Message);
            }
        }
    }

    public class Box
    {
        public Box(int h, int l, int w)
        {
            this.Height = h;
            this.Length = l;
            this.Width = w;
        }
        public int Height { get; set; }
        public int Length { get; set; }
        public int Width { get; set; }
    }


    class BoxEqualityComparer : IEqualityComparer<Box>
    {

        public bool Equals(Box b1, Box b2)
        {
            if (b1.Height == b2.Height & b1.Length == b2.Length
                                & b1.Width == b2.Width)
            {
                return true;
            }
            else
            {
                return false;
            }
        }


        public int GetHashCode(Box bx)
        {
            int hCode = bx.Height ^ bx.Length ^ bx.Width;
            return hCode.GetHashCode();
        }

    }
}
{% endhighlight %}


### HashSet

C#中的HashSet，可以对应C++中Set，用来包含无重复项的无序列表（自动去重）。

### SortedSet

C#中的SortedSet则是在HashSet基础上添加了自动排序功能。

下面给出关于HashSet和SortedSet的示例代码:

{% highlight C# %}
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Test
{
    class Program
    {
        static void PrintSet(IEnumerable<int> set)
        {
            Console.WriteLine("In set:");
            foreach (var i in set)
                Console.Write("{0}\t", i);
            Console.WriteLine("\n");
        }

       
        static void Main(string[] args)
        {            
            HashSet<int> hashSet = new HashSet<int>{ 3, 1, 2, 1 };
            PrintSet(hashSet.AsEnumerable()); // 3, 1, 2

            SortedSet<int> sortedSet = new SortedSet<int>{ 3, 1, 2, 1 };
            PrintSet(sortedSet.AsEnumerable());  // 1, 2, 3
            
            SortedSet<int> sortedSet2 = new SortedSet<int>{ 2, 1, 2, 1, 3 };
            Console.WriteLine(sortedSet.SetEquals(sortedSet2)); // True
        }
    }
}

{% endhighlight %}

参考文献

* LINQ查询表达式
	
	https://msdn.microsoft.com/zh-cn/library/bb397676.aspx
* Lambda表达式
	
	https://msdn.microsoft.com/zh-cn/library/bb397687.aspx
* Dictionary<TKey, TValue> 构造函数 (IEqualityComparer<TKey>)

	https://msdn.microsoft.com/zh-cn/library/vstudio/ms132072(v=vs.100).aspx