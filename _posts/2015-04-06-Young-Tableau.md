---
layout: post
title: 杨氏矩阵的查找
categories: [algorithm]
modify_date: 2015-04-12 20:00:00 +0800
---

杨氏矩阵（Young tableau），每行元素向右是递增的，每列元素向下也是递增的，即`a[i][j]<a[i+1][j] && a[i][j]<a[i][j+1]`。（一般杨表都是往左上角变小，往右下角增大，但也存在一些差异，比如中文wiki页面给出的示例）

杨表的填写涉及到勾长公式。
首先定义杨氏矩阵的勾长`hook(x)`为大于或者等于该格子值的格子数目，即该格子左边和下边并加上自己的格子数目。
勾长公式描述如下：对于给定形状，不同的杨氏矩阵的个数为：`n！`除以每个格子的勾长的连乘。给出[poj实例](http://poj.org/problem?id=1825)。


杨氏矩阵的查找，记该矩阵`m * n`，两种方法：左下角到右上角查找`O(m+n)`，四分矩阵查找`O(n^lg3)`。关于四分矩阵查找，注意时间复杂度，部分资料上给出的是`O((m+n)log(mn))`，个人觉得应该是错误的。

给出左下角到右上角的查找的样例代码。
{% highlight C++ %}
#include <iostream>

#define N 3

using namespace std;

bool FindYoungTableau(int matrix[][N], int m, int n, int val)
{
	if (matrix == NULL || m <= 0 || n <= 0)
		return false;
	int row = m - 1, column = 0;
	while (row >= 0 && column < n)
	{
		if (matrix[row][column] == val)
			return true;
		else if (matrix[row][column] > val)
			--row;
		else
			++column;		
	}
	return false;
}
int main()
{
	int matrix[][N] = { { 1, 4, 7 }, { 2, 5, 8 }, { 3, 6, 9 } };
	
	cout << FindYoungTableau(matrix, 3, 3, 4) << endl;
	
	return 0;
}
{% endhighlight %}

参考文献：

* http://en.wikipedia.org/wiki/Young_tableau
* http://articles.leetcode.com/2010/10/searching-2d-sorted-matrix-part-ii.html
* http://blog.csdn.net/sgbfblog/article/details/7745450
* http://blog.csdn.net/acdreamers/article/details/14549077

