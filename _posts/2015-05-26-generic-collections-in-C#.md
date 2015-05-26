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

1. 基于Linq Lambda表达式的排序

entityInfos = entityInfos.OrderByDescending(o => o.Value.df).ToDictionary(o => o.Key, p => p.Value);


2. HashSet


3. SortedSet

Dictionary<SortedSet<string>, int> testDict = new Dictionary<SortedSet<string>, int>();
            SortedSet<string> s1 = new SortedSet<string>() {"a", "ab", "b", "a"};
            SortedSet<string> s2 = new SortedSet<string>() { "ab", "b" , "a"};
            if (s1.SetEquals(s2))
                Console.WriteLine(true);
            for (int i = 0; i < s1.Count; ++i )
                Console.WriteLine(s1.ElementAt(i));

            testDict[s1] = 1;
            testDict[s2] = 100;

参考文献

* http://developer.51cto.com/art/200909/152323.htm