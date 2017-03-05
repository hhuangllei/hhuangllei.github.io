---
layout: post
title: Python常用module使用记录
categories: [coding, Python]
modify_date: 2017-03-05 22:00:00 +0800
---

最近一段时间，写Python代码比较多，也越来越觉得Python写起来很方便，有很多现成模块，但却因为不熟悉使用这些模块而影响coding效率。因此，记录下使用过的常用模块，方便以后查阅使用。

## 1 argparse  

命令行解析模块，不需要自己不专业的写命令行参数解析。 
2.7之后python不再对optparse模块进行扩展（已经过时），python标准库推荐使用*argparse模块*对命令行进行解析。  

``` Python
def parse_args():
	parser = argparse.ArgumentParser(description='Select odps log for asr.')
	parser.add_argument("-o", "--output",
					action="store", dest="output",
					help="specify log file to output")
	parser.add_argument("-k", "--appkey",
					action="store", dest="appkey",
					help="specify appkey to select")
	parser.add_argument("-s", "--start",
					action="store", dest="start_date",
					help="specify start date to select, such as 20170101")
	parser.add_argument("-e", "--end",
					action="store", dest="end_date",
					help="specify end date to select, such as 20170223")
	parser.add_argument("-p", "--province",
					action="store", dest="province",
					help=u"specify client province to select, such as 浙江")
	parser.add_argument("-w", "--keyword",
					action="store", dest="keyword",
					help=u"specify keywords to select, use comma to separate, such as 天猫,支付宝")
	return vars(parser.parse_args()) #  class argparse.Namespace -> dict
```

* https://docs.python.org/2/library/argparse.html  
* https://docs.python.org/2/howto/argparse.html#id1  
* [optparse](http://blog.csdn.net/hansel/article/details/8944777)  
* [argparse](http://www.tuicool.com/articles/ZF3y6b)  
* [argparse](http://www.cnblogs.com/jianboqi/archive/2013/01/10/2854726.html)  
* [Why use argparse rather than optparse?](http://stackoverflow.com/questions/3217673/why-use-argparse-rather-than-optparse)  

## 2 time  

#### 2.1 时间戳
时间间隔是以秒为单位的浮点小数，每个时间戳都以自从1970年1月1日午夜（历元）经过了多长时间来表示。

``` Python
import time
time.time() # 当前时间戳
```

#### 2.2 时间元组 struct_time (9-tuple)  


``` Python
time.localtime() # time.localtime(time.time())
```

#### 2.3 时间的格式化输出  


``` Python
time.strftime("%Y%m%d %H:%M:%S", time.localtime())
```

#### 2.4 时间和时间戳之间的转换  

time.strftime() # struct_time -> str  
time.strptime() # str -> struct_time  
time.localtime() # float -> struct_time  
time.mktime() # struct_time -> float  

* 时间戳 -> 时间  


``` Python
timestamp = 1488722400.0
t = time.localtime(timestamp)
time_str = time.strftime("%Y%m%d %H:%M:%S", t)
```

* 时间 -> 时间戳  


``` Python
time_str = "2017-03-05 22:00:00"
t = time.strptime(time_str, "%Y-%m-%d %H:%M:%S")
timestamp = time.mktime(t)
```

* [time — Time access and conversions](https://docs.python.org/2/library/time.html)  
* [日期和时间](http://www.runoob.com/python/python-date-time.html)  

## 3 datetime

#### 3.1 类型转换

datetime.datetime.fromtimestamp( float ) # float --> datetime  
datetime.strftime(format, datetime) # datetime --> str  
datetime.strptime(str, format) # str --> datetime  
datetime.timetuple( datetime ) # datetime --> struct_time  

#### 3.2 日期加减运算  

``` Python
import datetime
today = datetime.date.today()
yesterday = today - datetime.timedelta(days=1)
```

* [datetime — Basic date and time types](https://docs.python.org/2/library/datetime.html)  

## 4 tempfile

#### 4.1 tempfile.TemporaryFile  
<open file '<fdopen>', mode 'w+b' at 0x1004486f0>  
类文件对象，Linux下有坑  

#### 4.2 tempfile.NamedTemporaryFile 
当指定delete=True时，和TemporaryFile一样

* [Python tempfile模块学习笔记](http://www.jb51.net/article/50374.htm)  


* [subprocess — Subprocess management](https://docs.python.org/2/library/subprocess.html#module-subprocess)  