---
layout: post
title: 最短路径算法
categories: [coding]
modify_date: 2015-09-05 20:00:00 +0800
---

最短路径算法，最经典的就是Dijkstra算法和Floyd算法，为了处理负权边，又有扩展Bellman-Ford算法和SPFA算法。

### Dijkstra算法

单源点最短路径算法，时间复杂度`O(n^2)`

贪心思想，实际也可算作动态规划思想（最优子结果性质）（看到网上有说贪心可以算作是特殊的动态规划？）。已求出最短路径的顶点集合S，尚未确定最短路径的顶点结合U，每次从U中选出距离最小的顶点k，加入S中，然后更新到U中顶点的距离。

编程中一般会使用dist数组记录从v0到经过S到U中顶点的最小距离，使用pre数组记录路径。

注意：**不支持负权边**

### Floyd算法

多源最短路径算法，时间复杂度`O(n^3)`

动态规划思想，基本思想是从顶点A到顶点B的最短路径不外乎2种可能，1是直接从A到B，2是从A经过若干个节点到B，即`dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j])`，其中`i<k<j`。

更进一步准确的理解是，记状态`A(i, j, k)`表示从i到j经过的中间顶点最大不超过k的最短路径，则动态转移方程为`A(i, j, k)=min{A(i, j, k-1), A(i, k, k-1)+A(k, j, k-1)}`。若直接编程，则空间复杂度是`O(n^3)`，实际中可以优化空间，k,i,j按序枚举，在原来空间上进行迭代（k的位置上的元素本轮迭代中不会改变，十字交叉法），空间复杂度降为'O(n^2)'

编程中，**k的枚举放在最外面循环**；手算中，主要Floyd算法过程矩阵的计算,**十字交叉法**

注意：**不支持负权边**,可以检测**[负权环](https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm#Behavior_with_negative_cycles)**

{% highlight C++ %}
for(k=0;k<n;k++)
{ 
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(A[i][j]>(A[i][k]+A[k][j]))
            {
                A[i][j]=A[i][k]+A[k][j];
                path[i][j]=k;
             } 
}
{% endhighlight %}

### Bellman-Ford算法

单源点最短路径算法，**可处理负权边，检测负权回路**。

> Dijkstra's algorithm greedily selects the minimum-weight node that has not yet been processed, and performs this relaxation process on all of its outgoing edges; by contrast, the Bellman–Ford algorithm simply relaxes all the edges, and does this V-1 times, where V is the number of vertices in the graph.

### SPFA算法

Bellman-Ford算法的队列优化版本。

参考文献：

* https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm#Dynamic_programming_perspective
* https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm
* https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm
* https://en.wikipedia.org/wiki/Shortest_Path_Faster_Algorithm
* http://baike.baidu.com/view/4700690.htm
* http://www.cnblogs.com/biyeymyhjob/archive/2012/07/31/2615833.html
* http://www.cnblogs.com/hxsyl/p/3270401.html
* http://blog.chinaunix.net/uid-27164517-id-3287891.html
