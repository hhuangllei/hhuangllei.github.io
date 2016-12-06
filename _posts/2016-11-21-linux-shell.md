---
layout: post
title: Linux shell脚本使用
categories: [coding]
modify_date: 2016-11-21 11:30:00 +0800
---

shell判断文件,目录是否存在或者具有权限的代码

shell获取脚本所在路径  
和pwd结果不同

```bash
script_path=`dirname "$0"`
current_path="$PWD"
current_path2=`pwd` # ?
```

shell中涉及的常见Linux命令  
* date  
生成时间戳  

```bash
date +%s
```

* awk  

* crontab  

* [shell获取脚本所在路径](http://blog.csdn.net/johnyuan1988/article/details/8800164)  
* [shell判断文件,目录是否存在或者具有权限的代码](http://www.jb51.net/article/38277.htm)  
* [用shell将时间字符串与时间戳互转](http://www.cnblogs.com/xd502djj/p/4087949.html)  
* [linux awk命令详解](http://www.cnblogs.com/ggjucheng/archive/2013/01/13/2858470.html)  
* [linux定时执行脚本](http://www.cnblogs.com/kaituorensheng/p/4494321.html)  
* [linux下定时执行任务的方法](http://www.cnblogs.com/zhengah/p/4952311.html)  