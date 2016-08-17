---
layout: post
title: Python使用的一些小tips
categories: [coding, Python]
modify_date: 2016-08-17 23:00:00 +0800
---

很快就一个多月过去了，工作和生活也逐渐走上正轨，也该开始记录总结一些东西。这段时间，主要在写Python代码，实际我只是一个原来在业余时间接触过Python的业余Pythoner，所以会遇到较多问题，记录下Python使用的一些小tips。

## 1. Python修改pip源
`pip`安装软件包是Python中常见的事，毕竟Python如此流行的原因就有丰富的第三方库。  
最近安装一些包，速度慢得有些无法容忍，经常因速度慢而中止安装，严重影响工作效率。但我居然还忍了好几天，才联想到Linux更新软件慢可以更新源，pip速度慢也该换一个更新源啊 T_T

我的环境是Win7 64bit + Python2.7.12 64bit，在自己的用户目录`C:\Users\XXX\`下新建`pip`目录，再创建配置文件`pip.ini`，其中内容如下：
```
[global]
index-url = https://pypi.douban.com/simple
[install]
trusted-host=pypi.doubanio.com
```
`pip`更新源后，速度嗖嗖地上去了。

参考资料：  

* https://www.zhihu.com/question/38341743
* https://pip.pypa.io/en/latest/user_guide/#config-file (官网描述的配置文件路径好像有问题)

## 2. Windows下软件包的安装
修改pip源，速度确实上去了，但下载下来的软件包却不能用啊 T_T  
实际原来也遇到过这问题，主要是Windows的原因，很多的软件包的作者应该还是Linux环境，编译Python软件包估计也用到一些Linxu下的依赖，所以原生的放在`pip`上的软件包一般是用不了，比如`numpy`，`scipy`，`matplotlib`等软件包。

但Windows用户群也多啊，所以肯定有人做了移植，自己去找自己需要的软件包，download下来本地`pip install xxx`。  
[Unofficial Windows Binaries for Python Extension Packages](http://www.lfd.uci.edu/~gohlke/pythonlibs/)

## 3. Python代码理解 —— call graph
实际不管是啥编程语言，程序大了后阅读起来都吃力，各种函数各种类，一层又一层调用，接手代码则是剥洋葱似的一层一层剥洋葱皮，有时还得拿出一个小本子，记录下调用顺序，不然跟进去后就忘记进来的路再哪了。。。

而最近是接手一套Python程序，尽管是脚本语言，但调用多了、层次深了，理解起来又困难啊，所以想起要不要弄一个函数调用关系图来帮助理解。网上一搜，这官方名字叫做call graph，并且还有一些成熟的软件来自动生成。

1. Doxygen  
Doxygen号称支持大多数编程语言，如C，Objective-C，C#，PHP，Java，Python等。但用下来感觉配置更多的是为C++优化设计的，画出来的函数调用关系图也不好看（需要配合Graphviz画图），可能是我用来分析Python的原因。

2. pycallgraph  
pycallpraph专门用来绘制Python的模块调用关系图，看示例图效果不错。
> Python Call Graph is a Python module that creates call graph visualizations for Python applications.

  需要安装`pygraphviz`，并且配置感觉略复杂，稍微试用了下，因为Python程序比较大调用多，导致绘制出来的图很大，实际也不方便查看，但应该可以通过各种配置来进行定制，还未去折腾。

参考资料： 
 
* https://en.wikipedia.org/wiki/Call_graph
* http://blog.csdn.net/solstice/article/details/488865
* [Doxygen](http://www.stack.nl/~dimitri/doxygen/index.html)
* [Doxygen+Graphviz的使用](http://www.360doc.com/content/12/0812/14/7851074_229747305.shtml)
* [pycallgraph](http://pycallgraph.slowchop.com/en/master/)
