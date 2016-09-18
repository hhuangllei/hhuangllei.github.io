---
layout: post
title: Windows和Linux换行符的坑
categories: [coding]
modify_date: 2016-09-04 14:00:00 +0800
---

## 1. 基础知识
首先回顾一下换行符`\r`和回车符`\n`:

|    字符    |         缩写         | 十进制 | 十六进制 |  
| ---------- | -------------------- | ------ | -------- |  
| 换行符 \n |    line feed (LF)    |   10   |    0A    |  
| 回车符 \r | carriage return (CR) |   13   |    0D    |

关于C++编程中，使用更多的是`\n`，输出换行；而对于`\r`，输出中起到的效果是光标移到一行开始，可以达到覆盖的效果。  
给出输出载入或者下载进度百分数提示的例子：  

``` c++
#include <iostream>
#include <windows.h>

int main()
{
	// test printf \r
	for (int i = 1; i <= 100; ++i)
	{
		printf("\r%d%%", i);
		Sleep(1000);
	}

	return 0;
}
```

## 2. 故事回顾
原来也知道换行符在不同系统中不一样：  
* Windows `\r\n`
* Linux `\n`
* Mac `\r`  
但是实际中却忘记了，非得踩一回坑才能印象深刻，为了以后能够更快得定位问题或者避免问题，进行了记录整理。

故事还得从头说起：程序需要从一个filelist中读取文件路径，进而读取文件。先在Windows下写的filelist，随后传到了Linux服器上进行执行（使用sftp直接从Windows向LInux服器传输文件，git设置了`autocrlf = true`会自动处理不同系统下的换行符问题），发现`FILE *fp=fopen(filelist, "r")`得到的文件指针为`NULL`，但是打印出来的提示却显示正常。。。  

``` c++
printf("open file list: %s\n", filelist);
```
当时感到奇怪，filelist路径没错啊，怎么打不开。于是去打印`errno`，看看`fopen`到底是因为啥原因打不开文件啊。  

``` c++
printf("open file %s failed, errno is %d\n", filelist, errno);
```
这时感到更奇怪了，`printf`居然都工作不正常了，居然`open file `都给覆盖了。。。揉了揉眼镜，仔细看了下写的`printf`的这行代码，没有错啊。。。  
主要还是因为原来没有真正了解回车符`\r`的输出效果，没有真正了解不同系统换行符不同带来的问题，导致纠结了一些时间。最后才找到根源，Windows和Linux的换行符不同，导致多出了回车`\r`。  
在Linux下通过`cat -A filelist`可以看到行尾的回车换行符：  
回车符 `^M`  
换行符 `$`

## 3. 解决问题
在Linux下vi打开Windows下编辑的文件，通过设置`:set ff=unix`，则会去掉行尾的回车符`^M`。  

`ff`是vi的环境变量，代表fileformat (file format used for file I/O)，常见设置如下：  
* 使用unix换行符 `:set ff=unix`  
* 使用dos换行符 `:set ff=dos`
