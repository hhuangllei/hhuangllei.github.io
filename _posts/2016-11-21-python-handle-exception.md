---
layout: post
title: Python异常处理
categories: [coding, Python]
modify_date: 2016-12-06 9:30:00 +0800
---

异常即是一个事件，该事件会在程序执行过程中发生，影响了程序的正常执行。
在Python中，异常是一个对象，表示一种错误。
当Python脚本发生异常时我们需要捕获处理它，否则程序会终止执行。

异常的抛出机制：  
* 如果在运行时发生异常，解释器会查找相应的处理语句（称为handler）。  
* 要是在当前函数里没有找到，它会将异常传递给上层的调用函数，看看那里能不能处理。  
* 如果在最外层（全局“main”）还是没有找到的话，解释器就会退出，同时打印出traceback以便让用户找到错误产生的原因。  

### 1. 常见标准异常  
* Exception  
常规异常基类  
* IOError  
输入输出异常，如无法打开文件  
* NameError  
未声明/初始化对象  
* ImportError  
导入模块/对象失败，可以用来选择模块导入，当当前环境不存在某模块，可以不导入或者选择其他模块。

### 2. 异常处理  

#### 2.1 捕获异常  

try/except[/else][/final]语句  

```Python
try:
    <statement>        #运行别的代码
except <Exception>：
    <statement>        #如果在try部份引发了'name'异常
except <Exception>, <args>:
    <statement>        #如果引发了'name'异常，获得附加的数据
else:
    <statement>        #如果没有异常发生
finally:
    <statement>        #无论是否异常都会执行的代码，比如文件关闭，资源释放等操作
```
关于except语句，分为三种情况：  
* `except`  
  捕获所有异常，等价于`except Exception`  
* `except <Exception>`  
  捕获指定异常  
* `except <Exception>, <args>`  
  捕获指定异常，并可以根据参数得到具体异常信息  

#### 2.1 触发异常  
raise语句  

```Python
raise [Exception [, args [, traceback]]]
```
如`raise Exception("bad case")`  

### 3. 用户自定义异常  
用户自定义异常，通过继承异常基类`Exception`或其他异常类实现。  

```Python
class MyException(Exception):
    def __init__(self, arg):
        self.args = arg
```

* [Python异常处理](http://www.runoob.com/python/python-exceptions.html)  
* [Python异常处理](http://www.cnblogs.com/fnng/p/3518202.html)  