---
layout: post
title: Python使用with进行便捷文件操作 
categories: [coding, Python]
modify_date: 2016-12-06 11:00:00 +0800
---

with 语句是在 Python 2.5 版本引入的，从 2.6 版本开始成为缺省的功能。
with 语句作为`try/finally`编码范式的一种替代，用于对资源访问进行控制的场合。

Python 对一些内建对象进行改进，加入了对上下文管理器的支持，可以用于 with 语句中，比如可以自动关闭文件、线程锁的自动获取和释放等。

with语句能很好地简化文件操作，原来文件操作一般是使用`try/finally`保证无论是否出现异常都关闭文件：

```Python
somefile = open(r'somefileName')
    try:
        for line in somefile:
            print line
            # ...more code
    finally:
        somefile.close()
```

若使用with语句操作文件对象：

```Python
with open(r'somefileName') as somefile:
        for line in somefile:
            print line
            # ...more code
```

* [浅谈 Python 的 with 语句](http://www.ibm.com/developerworks/cn/opensource/os-cn-pythonwith/)  
* [使用Python进行稳定可靠的文件操作](http://blog.csdn.net/dreamthen/article/details/17263259)  
* [python with statement 进行文件操作指南](http://www.jb51.net/article/54162.htm)  