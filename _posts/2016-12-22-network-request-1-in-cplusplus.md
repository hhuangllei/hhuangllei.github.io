---
layout: post
title: C++中的网络请求——初探C++网络访问库
categories: [coding, C++]
modify_date: 2016-12-22 17:00:00 +0800
---

最近开发C++ SDK，涉及到一些联网功能，没点网络编程技能的我便开始了刷副本升级，一开始肯定是网上搜索各种攻略，花些时间进行汇总。

#### 1 系统底层的socket  
Windows `Winsock2.h`  
Linux `sys/socket.h`  
操作繁琐，好像只在本科上网络课的时候用过，然后就没有然后了。。。

#### 2 Asio  

[官网地址](http://think-async.com/Asio)，支持跨平台使用，已加入到Boost库，但也可以单独使用。代码放在hpp文件，方便集成使用。  

注意：  
* 宏定义 `ASIO_STANDALONE`，取消依赖Boost  
* 代码实现在hpp文件，不要把hpp文件包括在h文件，应该放在cpp文件  
* gcc版本要求4.6以上，`-std=c++11`  

#### 3 cpprestsdk  

微软出品，`Casablanca`，[官网地址](http://casablanca.codeplex.com/)，[Github地址](https://github.com/Microsoft/cpprestsdk)。  
支持跨平台，但代码体积较大。

#### 4 cpp-netlib  

[官网地址](http://cpp-netlib.org/index.html)，依赖Boost库，不便于集成未尝试使用。

#### 5 tinyhttpd  

[官网地址](http://tinyhttpd.sourceforge.net/)，UNIX下的小巧http访问库，有空可以研究。  

* [A Cheat Sheet for HTTP Libraries in C++](http://kukuruku.co/hub/cpp/a-cheat-sheet-for-http-libraries-in-c)  
* [GET、POST网络请求boost.asio实现](http://blog.csdn.net/duzixi/article/details/48195071)  
* [TinyHTTPd--超轻量型Http Server源码分析](http://blog.csdn.net/wenqian1991/article/details/46011357)  
