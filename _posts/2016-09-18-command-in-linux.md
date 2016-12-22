---
layout: post
title: Linux实用命令学习
categories: [coding]
modify_date: 2016-10-07 16:00:00 +0800
---

Windows用户的我，一直觉得Linux用户的熟练使用各种命令行才是程序猿的炫酷技能。现在使用每天使用服器，但也只会使用一些简单的`cd pwd ls ps mkdir cp mv rm`等命令，遇到稍微复杂一点的功能就必须得查查资料，确实会影响工作效率。  
所以开始记录下使用到的一些实用命令，总结汇总，争取能熟练使用。  

## 1. 统计目录下文件或者目录数目

组合使用`ls`、`grep`、`wc`三个指令来实现该功能：

* ls  
  list directory contents 查看目录中的内容  
  `ls -l` 显示文件和目录的详细信息，其中每行开始的文件属性字符串可以判断是文件还是目录：  
    * `-rw-r--r--` 第一位为`-`，文件  
    * `drwxr-xr-x` 第一位为`d`，目录  

 `ls -lR` 递归显示文件和目录的详细信息，用于统计当前目录及其子目录下所有文件或者目录信息
* grep  
  global search regular expression(RE) and print out the line 全局搜索正则表达式并打印匹配行  
  根据先前的`ls`指令，可以通过`grep "^-"`或者`grep "^d"`分别打印文件或者目录的信息行
* wc  
  word(line, byte) count 统计文件内容中的单词、行或者字节的数目并输出  
  `wc -w` 统计单词数目  
  `wc -c` 统计字节数目  
  `wc -m` 统计字母数目  
  `wc -l` 统计行数目  

通过使用`ls`和`wc`以及管道，再使用`wc -l`便可以实现统计文件或者目录的数目的功能。

### 1.1 统计当前目录下文件的数目

```bash
ls -l | grep "^-" | wc -l
```

### 1.2 统计当前目录下目录的数目

```bash
ls -l |grep "^d"|wc -l
```

### 1.3 统计当前目录以及子目录下文件的数目

```bash
ls -lR | grep "^-" | wc -l
```

### 1.4 统计当前目录以及子目录下目录的数目

```bash
ls -lR | grep "^d" | wc -l
```

## 2. 文件路径列表
在编程过程中，经常会用到文件路径列表，原来一般是写一个小程序来生成文件路径列表，实际可以直接试使用shell命令实现，简单快捷。  
`sed`命令，stream editor for filter and transforming text，即一种流编辑器，能够配合正则表示式使用。  
`sed`的正则表达式需要使用单引号或者双引号指出，如果其中还有用重音符指出执行命令时则需要使用双引号，在正则表示式中的定界符可以为斜线`/`、冒号`:`、竖线`|`(定界符若跟替换内容有冲突则进行转义)。  
最终得到以下命令：  

```bash
ls | sed "s:^:`pwd`/:"
ls | sed "s|^|`pwd`/|"
```
这两条命令效果一样，使用当前路径`pwd`添加在`ls`文件名前面，拼成绝对路径。

另外，实际还可以直接`ls`命令后使用绝对路径和正则匹配来实现绝对路径输出：  

```bash
ls /home/xxx/*.txt
```

## 3. 程序调试  

* ps  
  process 报告当前进程状态  
  使用 `ps [option]`  
  该命令可支持三种格式风格的选项，分别是UNIX选项（破折号`-`开始），BSD选项（无破折号开始），GNUxuanxiang（双破折号`--`开始），并且选项又多又复杂，介绍常用的选项。  
  * `u` 面向用户格式的输出  
  * `x` 显示所有属于你的进程  
  * `f` ASCII字符树表示程序间的层级依赖关系  
  * `w` 宽格式输出，使用两次该选项则设置为无限制宽度可换行输出  

  所以得到查看程序以及运行命令的查看命令为`ps uxfww`。

* pstack  
  print a stack trace of a running process，打印进程的栈跟踪。  
  使用 `pstack pid`，通过`ps`获取pid，则使用`pstack`来进行栈跟踪。  

* top  
  display Linux tasks，实时动态查看系统整体运行情况  
  `top -p pid` 指定进程监测

* valgrind  
Valgrind是一款用于内存调试、内存泄漏检测以及性能分析的软件开发工具。  
常用的是内存泄漏检测工具，具体使用如下：  

```bash
$ gcc -Wall -o memleak memleak.c
$ valgrind --tool=memcheck ./memleak
```

参考资料：  
* [Linux下统计当前文件夹下的文件个数、目录个数](http://www.jb51.net/article/56474.htm)  
* [ls关于输出绝对路径的使用技巧](http://blog.chinaunix.net/uid-25266990-id-3268759.html)  
* [Valgrind官网](http://valgrind.org/)  
* [Linux命令大全](http://man.linuxde.net/)  
* [Valgrind简单用法](http://www.cnblogs.com/sunyubo/archive/2010/05/05/2282170.html)  
