---
layout: post
title: set, hash_set, map, hash_map的区别
categories: [job, coding]
modify_date: 2015-08-10 22:30:00 +0800
---

最近复习面试题，在数据结构和大数据部分，提到了**set， hash_set, map, hash_map**。
关于这4种数据结构需要重点掌握，set和map是使用RB树（红黑树，一种平衡二叉树）实现，所以插入、查找、删除的时间复杂度都是O(logn)；而hash_set和hash_map是使用hash表实现，所以插入、查找、删除的时间复杂度都是O(1)。

简单看来好像hash_set和hash_map优势大，set和map好像不值得使用。实际上，因为set和map是使用红黑树实现，所以其中的元素是排好序的，方便查找最大值和最小值（时间复杂度O(logn)）。因而，要根据具体情况选用合适的数据结构。

在C++中，set和map分别对应STL中set和map，hash_set和hash_map分别对应STL中unordered_set和unordered_map（C++11标准引入）。
还是给出一个示例代码，展示区别：


{% highlight C++ %}
#include <iostream>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

template <typename T>
void PrintSet(T begin, T end)
{
	T i = begin;
	while (i != end)
	{
		cout << *i++ << " ";
	}
	cout << endl;
}
template <typename T>
void PrintMap(T begin, T end)
{
	T i = begin;
	while (i != end)
	{
		cout << "(" << i->first << ", " << i->second << ") ";
		++i;
	}
	cout << endl;
}
int main()
{
	// test set and unordered_set
	int arr[] = { 2, 1, 3 };
	set<int> set1(arr, arr + 3);
	unordered_set<int> set2(arr, arr + 3);

	cout << "set: ";
	PrintSet(set1.begin(), set1.end());
	cout << "unordered_set: ";
	PrintSet(set2.begin(), set2.end());

	// test map and unordered_map
	vector<pair<int, string>> pairs;
	pairs.push_back(make_pair(2, "ab"));
	pairs.push_back(make_pair(1, "aa"));
	pairs.push_back(make_pair(3, "ac"));

	map<int, string> map1(pairs.begin(), pairs.end());	
	unordered_map<int, string> map2(pairs.begin(), pairs.end());

	cout << "map: ";
	PrintMap(map1.begin(), map1.end());
	cout << "unordered_map: ";
	PrintMap(map2.begin(), map2.end());

	getchar();
	return 0;
}
{% endhighlight %}

输出结果为：

		set: 1 2 3
		unordered_set: 2 1 3
		map: (1, aa) (2, ab) (3, ac)
		unordered_map: (2, ab) (1, aa) (3, ac)