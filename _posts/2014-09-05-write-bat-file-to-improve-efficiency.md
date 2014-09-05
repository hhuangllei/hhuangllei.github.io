---
layout: post
title: 学习使用bat文件提高效率
---

平时经常遇到调用一个传参的exe程序，因为数据量大，需要拆分并行执行，所以一般是开N个cmd窗口，再分别在每个窗口输入命令，或者提前写好简单的bat文件（实际里面可能就只有一行命令），再一个一个点击运行。

如果当N大于10，先开好每个cmd窗口，运行后再一个一个检查，生怕任务没分配好、命令敲错了，操作还是挺繁琐的，更主要的是这样显得不专业啊，没有程序员的样子。

因此为了提高一点逼格，简单学了下bat文件的编写，不多说了，直接贴上代码task.bat：
{% highlight bat %}
@echo off
set n=24
set exe=test.exe
set param=param

for /l %%i in (1,1,%n%) do (
start "%%i" %exe% %param% %%i %n% 
)

pause
{% endhighlight %}

上面这段代码就是开24个进程传入不同参数拆分任务执行test.exe程序，写好上面的代码后双击就自动开24个进程传入指定的参数执行程序，方便快捷。

实际上面的bat主要是涉及`set`, `for`和`start`这两个命令，下面简单介绍下，感兴趣的可以去cmd查看help。

1. `set`

	声明变量

2. `for`

	`FOR /L %variable IN (start,step,end) DO command [command-parameters]`

	该集表示以增量形式从开始到结束的一个数字序列。因此，(1,1,5)将产生序列
    1 2 3 4 5，(5,-1,1)将产生序列(5 4 3 2 1)

2. `start`

	`START ["title"] [command/program] [parameters]`
	
	其中“title”是在在窗口标题栏中显示的标题。

再说一说如果要在循环中改变变量并使用该变量，就要看看`for`关于[延迟变量](http://blog.sina.com.cn/s/blog_625651900100jzyj.html)的使用。

延迟环境变量，顾名思义，延迟读取了环境变量。当我们开启延迟环境变量之后，命令解释器就不再是运行命令前先将环境变量读取出来再执行，而是当我们用到延迟环境变量的时候再去从环境变量中读取出来，这就延迟了环境变量读取的时间。

1. 未使用延迟变量
{% highlight bat %}
@echo off
set var=1
for /l %%i in (1,1,5) do (
set /a var+=%%i
echo %var%
)
pause
{% endhighlight %}
上述代码未使用延迟变量，输出全是1，并不是我们想要的var的累加。

2. 使用延迟变量
{% highlight bat %}
@echo off
setlocal enabledelayedexpansion
set var=1
for /l %%i in (1,1,5) do (
set /a var+=%%i
echo !var!
)
pause
{% endhighlight %}

上述代码使用了延迟变量，输出`2 4 7 11 16`的累加，得到我们想要的结果。

最后再简单解释下上述代码:

`setlocal enabledelayedexpansion`　　开启延迟变量

`set /a var+=%%i`　　`set /a`变量支持数学运算

`!var!`　　取延迟变量