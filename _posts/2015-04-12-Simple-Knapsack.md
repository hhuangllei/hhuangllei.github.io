---
layout: post
title: 简单背包问题的递归和非递归实现
categories: [algorithm]
modify_date: 2015-04-12 22:00:00 +0800
---

背包问题有很多变种，这次讨论的是简单背包问题，定义如下：有一个背包，能盛放的物品总重量为S,设有N件物品，其重量分别为w1，w2，…，wn，希看从N件物品中选择若干物品，所选物品的重量之和恰能放进该背包，即所选物品的重量之和即是S。

一般是采用回溯实现，但面试中经常考察其非递归实现，具体代码如下（找出了所有可行解）：
{% highlight C++ %}
#include <iostream>
#include <vector>

using namespace std;

vector<int> temp;
vector<vector<int> > result;
void SimpleKnapsack(vector<int> items, int capacity, int i)
{
	if (capacity == 0)
	{
		result.push_back(temp);
		return;
	}
	else if (i >= items.size() || items[i] > capacity)
		return;

	temp.push_back(items[i]);
	SimpleKnapsack(items, capacity - items[i], i + 1);
	
	temp.pop_back();
	SimpleKnapsack(items, capacity, i + 1);
}
void SimpleKnapsack_stack(vector<int> items, int capacity)
{
	int n = items.size(), sum = 0, i = 0, start = 0;
	vector<int> stack;
	vector<int> visited(n, 0);
	
	while (1)
	{
		for (i = start; i < n; ++i)
		{
			if (!visited[i] && items[i] + sum <= capacity)
			{
				sum += items[i];
				stack.push_back(i);
				temp.push_back(items[i]);
				visited[i] = 1;
				if (sum == capacity)
				{
					result.push_back(temp);
					break;
				}
			}
		}
		
		if (i == n)
		{
			if (stack.empty())
				return;
			int top = stack.back();
			stack.pop_back();
			temp.pop_back();
			visited[top] = 0;
			sum -= items[top];
			start = top + 1;
		}
	}
}
int main()
{
	int w[] = { 2, 3, 5, 7, 8};
	vector<int> items(w, w + 5);

	//SimpleKnapsack(items, 15, 0);
	SimpleKnapsack_stack(items, 15);
}
{% endhighlight %}

参考文献：

* http://blog.csdn.net/zhaom_916/article/details/7426629
* http://blog.csdn.net/htyurencaotang/article/details/11092491
* http://blog.csdn.net/oracle_microsoft/article/details/1604462