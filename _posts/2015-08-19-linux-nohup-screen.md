---
layout: post
title: Linux后台运行程序的那些事儿
categories: [coding]
modify_date: 2015-08-19 17:00:00 +0800
---

平时主要是在Windows平台下工作，但偶尔会使用Linux，一般就是使用putty连接linux来使用。有时就会遇到想要跑多份程序，但只开了一个putty，如何让程序在后台运行的问题？

主要是两个方法，但screen使用起来更顺手：

* ###使用`&`把程序放后台运行###

主要命令：

{% highlight bat %}
# jobs      //查看任务，返回任务编号n和进程号
# bg  %n   //将编号为n的任务转后台运行
# fg  %n   //将编号为n的任务转前台运行
# ctrl+z    //挂起当前任务
# ctrl+c    //结束当前任务
{% endhighlight %}

一般涉及的程序都会有屏幕输出结果，则后台运行时可以重定向到文件，如`# a > a.out &`

值得注意得是，如果使用终端如putty起的多个后台程序，在该终端被关闭后，会发送SIGHUP挂起信号给所有子进程，子进程收到SIGHUP以后也会退出。所以，为了让终端关闭后，后台程序也能继续运行，所以需要使用`nohup`指令，可以让指定程序忽略所有挂断（SIGHUP）信号。此时，终端关闭后，后台的程序也能够继续执行，直到程序终止。

{% highlight bat %}
# nohup <command> [argument…] &
{% endhighlight %}


* ###使用`screen`把程序放到screen会话中运行###

主要命令：

{% highlight bat %}
# screen -S yourname -> 新建一个叫yourname的session
# screen -ls -> 列出当前所有的session
# screen -r yourname -> 回到yourname这个session
# screen -d yourname -> 远程detach某个session
# screen -d -r yourname -> 结束当前session并回到yourname这个session
{% endhighlight %}

在每个screen session 下，所有命令都以 ctrl+a(C-a) 开始:

{% highlight bat %}
C-a ? -> 显示所有键绑定信息
C-a c -> 创建一个新的运行shell的窗口并切换到该窗口
C-a n -> Next，切换到下一个 window 
C-a p -> Previous，切换到前一个 window 
C-a 0..9 -> 切换到第 0..9 个 window
Ctrl+a [Space] -> 由视窗0循序切换到视窗9
C-a C-a -> 在两个最近使用的 window 间切换 
C-a x -> 锁住当前的 window，需用用户密码解锁
C-a d -> detach，暂时离开当前session 
C-a z -> 把当前session放到后台执行，用 shell 的 fg 命令则可回去。
C-a w -> 显示所有窗口列表
C-a t -> Time，显示当前时间，和系统的 load 
C-a k -> kill window，强行关闭当前的 window
{% endhighlight %}


参考文献：

* http://www.cnblogs.com/xianghang123/archive/2011/08/02/2125511.html

* http://www.ibm.com/developerworks/cn/linux/l-cn-screen/

* http://www.cnblogs.com/mchina/archive/2013/01/30/2880680.html
