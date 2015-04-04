---
layout: post
title: learn to write blog
modify_date: 2015-04-04 22:00:00
---

原来创建这个博客就是想记录下自己平时遇到的问题，以及所思所想，但因为各种原因，真的是all things fXXk up(最近才知道这是foo的命名起源-_-||)啊，又给断了几个月，终于想起了这个人博客啊，真的是我一个人记录、阅读的博客。

最近这段时间，为了秋招找工作开始看一些算法面试题，这次准备谈一谈涉及动态规划（DP）的几个看似很相似的问题：最大子段和（Maximum Subarray），最长公共子串(Longest Common Substring)，最长公共子序列（Longest Common Subsequence），最长递增子序列（Longest Increasing Subsequence），字符串编辑距离。

注意：最长公共子串和最长公共子序列，简称都是LCS，但求解有差别。

1. 最大字段和

	对n个整数，a[1], a[2], ..., a[n]，找出一个字段使得和最大。该问题有DP、分治等方法，这里只讨论DP方法。
	http://en.wikipedia.org/wiki/Maximum_subarray_problem
	http://baike.baidu.com/view/14174787.htm

	记`F[i]`为以第i个数结尾的最大字段和，则动态转移方程：`F[i] = F[i-1]>0 ? F[i-1]+a[i] : a[i]`。
	时间复杂度为`O(n)`。

{% highlight C++ %}
int MaxSub(int a[], int n)
{ 
	if (n <= 0)
		return 0;

	int *F = new int[n], maxSum = 0;
	F[0] = a[0];
	maxSum = a[0];

	for (int i = 1; i < n; ++i)
	{
		F[i] = F[i - 1] > 0 ? F[i - 1] + a[i] : a[i];
		if (maxSum < F[i])
			maxSum = F[i];
	}

	delete []F;
	return maxSum;
}
{% endhighlight %}

2. 最长公共子串

	从两个字符串中找出最长的**子串**，这个子串**要求在源字符串中是连续**。
	http://en.wikipedia.org/wiki/Longest_common_substring_problem

	两个子串`str1`和`str2`，长度分别为`m`和`n`，记`F[i][j]`为以`str1[i]`和`str2[j]`结尾的最长公共子串长度，则动态转移方程为：`F[i][j] = str1[i]==str2[j] ? F[i-1][j-1]+1 ： 0`。
	时间复杂度为`O(mn)`。

{% highlight C++ %}
int LongestCommonSubstring(string str1, string str2)
{
	int m = str1.length(), n = str2.length();
	if (m == 0 || n == 0)
		return 0;

	int maxLen = 0;
	vector<vector<int> > F(m+1, vector<int>(n+1));
	for (int i = 1; i <= m; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			F[i][j] = str1[i - 1] == str2[j - 1] ? F[i - 1][j - 1] + 1 : 0;
			if (maxLen < F[i][j])
				maxLen = F[i][j];
		}
	}

	return maxLen;
}
{% endhighlight %}

3. 最长公共子序列
	
	从两个字符串中找出最长的**子序列**，这个子序列**不要求在源字符串中连续**。
	http://en.wikipedia.org/wiki/Longest_common_subsequence_problem
	http://baike.baidu.com/view/2020307.htm

	两个子串`str1`和`str2`，长度分别为`m`和`n`，记`F[i][j]`为在`str1[i]`和`str2[j]`之前的最长公共子序列长度，则动态转移方程为：`F[i][j] = str1[i]==str[2] ? F[i-1][j-1]+1 : (max(F[i][j-1], F[i-1][j]))`。
	时间复杂度为`O(mn)`。

4. 最长递增子序列

5. 编辑距离
	
	http://en.wikipedia.org/wiki/Edit_distance

参考文献：
http://www.cnblogs.com/zhangchaoyang/articles/2012070.html
http://en.wikipedia.org/wiki/Category:Dynamic_programming
http://baike.baidu.com/view/2020307.htm
http://baike.baidu.com/view/14174787.htm
