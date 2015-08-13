---
layout: post
title: Alibaba实习一面经验总结
categories: [job]
modify_date: 2015-05-04 16:00:00 +0800
---

4月27日，参加了Alibaba校园实习招聘的一面，总体感受是**注重基础，深究细节，手写代码**，在此记录下遇到的问题，总结经验，吸取教训。

1. 面向对象的3个特性

	4个特性：封装，继承，抽象，多态
	
	3个特性：封装，继承，多态

	http://www.cppblog.com/snowball/archive/2008/07/01/55051.html

2. C/C++内存管理机制 堆 栈

	在C++中，内存分为5个区：堆、栈、自由存储区、全局/静态存储区和常量存储区。

	堆和栈的区别：

	* 管理方式不同
	* 空间大小不同
	* 能否产生碎片不同
	* 生长方向不同 
	  
	  堆，向上生长，内存地址增长；栈，向下生长，内存地址减少。
	* 分配方式不同
	* 分配效率不同

	http://www.cnblogs.com/daocaoren/archive/2011/06/29/2092957.html
	http://www.cnblogs.com/hanyonglu/archive/2011/04/12/2014212.html

3. C/C++ static的区别
	
	* 局部静态变量 C/C++

	  扩展生存期
	* 外部静态变量 C/C++
	
	  限定作用域

	  对于外部(全局)变量, 不论是否有static限制, 它的存储区域都是在静态存储区,生存期都是全局的。此时的static只是起作用域限制作用, 限定作用域在本模块(文件)内部。
	* 静态数据成员 C++
	
	  表示属于一个类而不是属于此类的任何特定对象的变量和函数。static既不是扩展生存期, 也不是限定作用域, 而是指示变量/函数在此类中的唯一性。
	
	http://blog.csdn.net/skyereeee/article/details/8000512

4. 进程与线程

	* 概念
	
	  进程作为分配资源的基本单位，线程作为独立运行和独立调度的基本单位。
	  线程只有 3 个基本状态：就绪，执行，阻塞。

	  http://jingyan.baidu.com/article/624e74598efcc834e9ba5a66.html
	  http://www.ruanyifeng.com/blog/2013/04/processes_and_threads.html
	  
	* 区别
	
	  子进程和父进程有不同的代码和数据空间，而多个线程则共享数据空间，每个线程有自己的执行堆栈和程序计数器为其执行上下文。多线程主要是为了节约CPU时间，发挥利用，根据具体情况而定。线程的运行中需要使用计算机的内存资源和CPU。

	* 进程间通信

	  * 管道
	  
		  1. 普通管道PIPE 通常有两种限制，一是单工，只能单向传输；二是只能在父子或者兄弟进程间使用。
		  2. 流管道s_pipe 去除了第一种限制，为半双工，可以双向传输。
		  3. 命名管道name_pipe 去除了第二种限制,可以在许多并不相关的进程之间进行通讯。
	  * 系统IPC(Inter-Process Communication，进程间通信)
	  
		  1. 消息队列
		  2. 信号
		  3. 共享存储
	  * 套接字（SOCKET）
	  
	  http://baike.baidu.com/view/1492468.htm
	  http://blog.csdn.net/yufaw/article/details/7409596

	* 线程间通信
	  * 全局变量方式
	  * 消息传递方式
	  * 参数传递方式
	  * 线程同步法
	  
		  1.  临界区
		  2.  互斥量
		  3.  信号量
		  4.  事件

	  http://blog.csdn.net/cbnotes/article/details/8516703
	  http://blog.csdn.net/minglingji/article/details/7488652

5. 排序算法 时间复杂度 稳定性
	
	[八大排序算法](http://blog.csdn.net/hguisu/article/details/7776068)

	  * 插入排序 直接插入排序，希尔排序
	  * 选择排序 简单选择排序，堆排序
	  * 交换排序 冒泡排序，快速排序
	  * 归并排序
	  * 基数排序

	重点是快排。

6. n个元素中找第k大元素，分析算法时间复杂度

	* 排序后取第k个，O(nlogn)
	* 选择或冒泡，排序出前k个元素，O(n*k)
	* 使用小顶堆，先建k个元素的小顶堆O(klogk)，再遍历后续元素，若大于堆顶元素，则更新小顶堆，最终时间复杂度为O(klogk+(n-k)logk)=O(nlogk)
	* 使用快排中的划分算法，O(n) **时间复杂度的推导没弄清楚**
	
		最坏情况下，T(n) = T(n-1) + n ==> T(n) = O(n^2)
		
		最好情况下，T(n) = T(n/2) + n ==> T(n) = n * (1 + 1/2 + ... + (1/2)^k) = O(n)
		
		平均情况下，需要结合概率推导，比较复杂。
	
	* 使用hash表排序，空间换时间，O(n)

	http://blog.chinaunix.net/uid-20196318-id-189514.html
	http://blog.csdn.net/v_JULY_v/article/details/6370650