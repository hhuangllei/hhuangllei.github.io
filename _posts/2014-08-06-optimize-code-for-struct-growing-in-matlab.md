---
layout: post
title: 关于matlab中struct增长的优化
---

在平时编写matlab代码进行实验，偶然间发现matlab结构进行行增长或者列增长速度差异较大，选择列增长能够很大程度上提速。
为了进一步验证，就写了一段demo程序测试：
{% highlight matlab %}
n = 100000;

fprintf('row grow ... \n');
tic;
temp = struct;
for i = 1 : n
    temp(i, 1).Str = 'aaaa';
    temp(i, 1).Count = i;
end
toc;

fprintf('column grow ... \n');
tic;
temp = struct;
for i = 1 : n
    temp(i).Str = 'aaaa'; % temp(1, i).Str = 'aaaa';
    temp(i).Count = i; % temp(1, i).Count = i;
end
toc;
{% endhighlight %}

机器配置就是普通台式机，运行结果如下所示，运行时间相差100+倍：
{% highlight matlab %}
row grow ... 
Elapsed time is 34.328403 seconds.
column grow ... 
Elapsed time is 0.292414 seconds.
{% endhighlight %}
在上面的demo代码中，你可以发现，struct里有两个field，这是因为我在测试速度时发现，**如果struct只有一个field，行增长和列增长速度上并不会相差很多，但是当有两个及以上的field，差别就体现出来了**。

另外，对于上面的demo代码，并不是struct的两个域非得一个是string，一个是double，如果修改成下面的代码依然可以得出相似的结果：

两个域都是string
{% highlight matlab %}
temp(i, 1).Str = 'aaaa';
temp(i, 1).Str2 = 'bbbb';
{% endhighlight %}

两个域都是double
{% highlight matlab %}
temp(i, 1).Count = i;
temp(i, 1).Count2 = i;
{% endhighlight %}

关于为啥会出现这种现象，个人觉得应该是matlab内存申请机制导致的吧，具体是什么机制，没深入研究，有兴趣的可以去倒腾。