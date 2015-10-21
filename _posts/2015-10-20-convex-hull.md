---
layout: post
title: 凸包问题
categories: [job, algorithm]
modify_date: 2015-10-21 11:00:00 +0800
---

最近做笔试机试，遇到了**凸包问题**，对于未接触过凸包的我来说，确实有些难，但弄懂后就会发现，这类题可以算作模板题。

**凸包（Convex Hull）**是一个计算几何（图形学）中的概念。点集Q的凸包（convex hull）是指一个**最小凸多边形**，满足Q中的点或者在多边形边上或者在其内。

关于**凸包**求解，主要有两种算法：

* Graham scan (Graham扫描法)，时间复杂度`O(nlogn)`
* Gift wrapping (Jarvis march，Jarvis步进法)，时间复杂度`O(nh)`

最常用的是Graham scan方法，主要步骤如下：

1. 找左下点（先找x最小，x相同则y最小）为基准点，此时以该点为起点，到其他点的角度为[90, -90)。如果找的是下左点，角度为(180, 0]。
2. 以基准点为起点，对其他点进行夹角从小到大排序，如果夹角相等，则距离近的排前面。计算夹角，可以使用**叉积**来判断（计算方便，乘法没精度损失），也可以使用**余弦**。
3. 根据**左转**或者**右转**判断当前点是否在凸包上。使用**栈**，判断`s[top] s[top] v[i]`情况, 叉积为正则左转，在凸包上；叉积为负则右转，不在凸包上；叉积为零，根据具体情况，考虑是否保留。**当不在凸包上时，需要循环弹出栈，直到满足左转。**

[POJ 1113](http://poj.org/problem?id=1113)

这个题是求最大围墙长度，抽象出来就是 `minLen = convex hull perimeter + one full circle perimeter (radius = d)`。

{% highlight C++ %}
#include <iostream>
#include <climits>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

#define PI 3.141592654

class Point
{
public:
	int x, y;
	Point() :x(0), y(0){}
	Point(int x, int y) :x(x), y(y){}
};

vector<Point> vertex;
vector<int> s(1000, 0);
int top = 0;

// 行列式
int Det(int x1, int y1, int x2, int y2)
{
	return x1 * y2 - x2 * y1;
}
// 向量叉积 P0P1 X P0P2，判断极角大小
int CrossProduct(Point p1, Point p2, Point p3, Point p4)
{
	return Det(p2.x - p1.x, p2.y - p1.y, p4.x - p3.x, p4.y - p3.y);
}
int Dist(Point p1, Point p2)
{
	return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}
bool Cmp(const Point &p1, const Point &p2)//排序判断条件
{
	if (CrossProduct(vertex[0], p1, vertex[0], p2) > 0)
		return true;
	else if (CrossProduct(vertex[0], p1, vertex[0], p2) == 0
		&& Dist(p1, vertex[0]) < Dist(p2, vertex[0]))
		return true;
	else
		return false;
}
void Graham(int n)
{
	top = 1;
	for (int i = 0; i < 2; ++i)
		s[i] = i;

	for (int i = 2; i < n; ++i)
	{
		int t = CrossProduct(vertex[s[top - 1]], vertex[s[top]], vertex[s[top]], vertex[i]);
		while (top && CrossProduct(vertex[s[top - 1]], vertex[s[top]], vertex[s[top]], vertex[i]) <= 0)
			--top;
		s[++top] = i;
	}
}
int GenMinLen(int l)
{
	double minLen = sqrt(Dist(vertex[s[0]], vertex[s[top]]));
	for (int i = 0; i < top; ++i)
		minLen += sqrt(Dist(vertex[s[i]], vertex[s[i + 1]]));
	minLen = minLen + PI * 2 * l;
	return int(minLen + 0.5);
}
int main()
{
	int n, l, i, minInd;
	Point minPoint;
	while (cin >> n >> l)
	{
		vertex.clear();
		vertex = vector<Point>(n, Point());
		minPoint.x = minPoint.y = INT_MAX;
		for (minInd = i = 0; i<n; i++)
		{
			cin >> vertex[i].x >> vertex[i].y;
			if (minPoint.x > vertex[i].x)
			{
				minPoint = vertex[i];
				minInd = i;
			}
			else if (minPoint.x == vertex[i].x && minPoint.y > vertex[i].y)
			{
				minPoint = vertex[i];
				minInd = i;
			}
		}
		vertex[minInd] = vertex[0]; vertex[0] = minPoint;
		sort(vertex.begin() + 1, vertex.begin() + n, Cmp);

		Graham(n);
		cout << GenMinLen(l) << endl;
	}
	return 0;
}
{% endhighlight %}

[POJ 3348](http://poj.org/problem?id=3348)

这个题是求围成的牧场最多能养多少头奶牛，抽象出来就是**先求凸包，再求围成的多边形面积**。

关于多边形面积，就是先把多边形分成小三角形，利用**叉积**求出这些小三角形的面积，累加起来便是多边形的面积。

![image]({{site.url}}/assets/img/PolygonArea.jpg)


{% highlight C++ %}
#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

class Point
{
public:
	int x, y;
	Point() :x(0), y(0){}
	Point(int x, int y) :x(x), y(y){}
};

vector<Point> vertex;
vector<int> s(10000, 0);
int top = 0;

// 行列式
int Det(int x1, int y1, int x2, int y2)
{
	return x1 * y2 - x2 * y1;
}
// 向量叉积 P0P1 X P0P2，判断极角大小
int CrossProduct(Point p1, Point p2, Point p3, Point p4)
{
	return Det(p2.x - p1.x, p2.y - p1.y, p4.x - p3.x, p4.y - p3.y);
}
int Dist(Point p1, Point p2)
{
	return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}
bool Cmp(const Point &p1, const Point &p2)//排序判断条件
{
	if (CrossProduct(vertex[0], p1, vertex[0], p2) > 0)
		return true;
	else if (CrossProduct(vertex[0], p1, vertex[0], p2) == 0 
		&& Dist(p1, vertex[0]) < Dist(p2, vertex[0]))
		return true;
	else
		return false;
}
void Graham(int n)
{
	top = 1;
	for (int i = 0; i < 2; ++i)
		s[i] = i;
	
	for (int i = 2; i<n; i++)
	{
		int t = CrossProduct(vertex[s[top - 1]], vertex[s[top]], vertex[s[top]], vertex[i]);
		while (top && CrossProduct(vertex[s[top - 1]], vertex[s[top]], vertex[s[top]], vertex[i]) <= 0)
			--top;
		s[++top] = i;
	}
}
double CalcPolygonArea()
{
	double area = 0;
	for (int i = 1; i < top; ++i)
	{
		area += CrossProduct(vertex[0], vertex[s[i]], vertex[0], vertex[s[i+1]]);
	}
	return 0.5 * area / 50;
}
int main()
{
	int n, i, minInd;
	Point minPoint;
	while (cin >> n)
	{
		vertex.clear();
		vertex = vector<Point>(n, Point());
		minPoint.x = minPoint.y = INT_MAX;
		for (minInd = i = 0; i<n; i++)
		{
			cin >> vertex[i].x >> vertex[i].y;
			if (minPoint.x > vertex[i].x)
			{
				minPoint = vertex[i];
				minInd = i;
			}
			else if (minPoint.x == vertex[i].x && minPoint.y>vertex[i].y)
			{
				minPoint = vertex[i];
				minInd = i;
			}
		}
		vertex[minInd] = vertex[0]; vertex[0] = minPoint;
		sort(vertex.begin()+1, vertex.begin() + n, Cmp);

		Graham(n);
		cout << int(CalcPolygonArea()) << endl;
	}
	return 0;
}
{% endhighlight %}



参考文献：

* Convex Hull https://en.wikipedia.org/wiki/Convex_hull
* Graham scan https://en.wikipedia.org/wiki/Graham_scan

* 凸包 http://baike.baidu.com/view/707209.htm
* 叉积 http://baike.baidu.com/view/973423.htm
* 多边形面积 http://blog.csdn.net/hemmingway/article/details/7814494
* POJ1113 http://www.cnblogs.com/yu-chao/archive/2011/11/05/2237018.html
* poj3348 http://blog.csdn.net/zhang20072844/article/details/6795545