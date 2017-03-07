---
layout: post
title: Python常用module使用记录
categories: [coding, Python]
modify_date: 2017-03-07 21:30:00 +0800
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

time.strftime() # struct_time -> 格式化的时间字符串  
time.strptime() # 格式化的时间字符串 -> struct_time  
time.localtime() # 时间戳 -> struct_time  
time.mktime() # struct_time -> 时间戳  

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

float --> datetime: datetime.datetime.fromtimestamp( float )  
datetime --> str: datetime.strftime(format, datetime)  
str --> datetime: datetime.strptime(str, format)  
datetime --> struct time tuple: datetime.timetuple( datetime )  

#### 3.2 日期加减运算  

``` Python
import datetime
today = datetime.date.today()
yesterday = today - datetime.timedelta(days=1)
```

* [datetime — Basic date and time types](https://docs.python.org/2/library/datetime.html)  

## 4 tempfile
临时文件模块，有时需要临时文件进行操作，没必要自己生成临时文件来操作，还得考虑一个临时文件名 uuid.uuid4()。  

* tempfile.TemporaryFile()  
<open file '<fdopen>', mode 'w+b' at 0x1004486f0>  
类文件对象，Linux下有坑  

* tempfile.NamedTemporaryFile() 
当指定delete=True时，和TemporaryFile一样

* [Python tempfile模块学习笔记](http://www.jb51.net/article/50374.htm)  

## 5 logging
日志管理模块，先前为了调试都是不专业的print或者写文件来保存日志，学习使用logging，稍微专业点来操作日志。  
logging是线程安全的，支持多线程下的日志输出。  

#### 5.1 日志级别
日志级别大小关系为：CRITICAL > ERROR > WARNING > INFO > DEBUG > NOTSET  
默认情况下，logging将日志打印到屏幕，日志级别为WARNING。  

#### 5.2 logging handlers

* logging.StreamHandler  
控制台日志输出  
* logging.FileHandler  
  文件日志输出  
* logging.handlers.RotatingFileHandler  
  文件日志输出，根据存储大小转存日志  
  `RotatingFileHandler(filename, mode='a', maxBytes=0, backupCount=0, encoding=None, delay=0)`  

  100M拆分，最多回滚5次日志，示例如下：  
  `RotatingFileHandler('test.log', mode='a', maxBytes=100 * 1024 * 1024, backupCount=5)`

* logging.handlers.TimedRotatingFileHandler  
文件日志输出，根据时间转存日志  
`TimedRotatingFileHandler(filename, when='h', interval=1, backupCount=0, encoding=None, delay=False, utc=False)`  

按天拆分，最多回滚30天日志，示例如下：  
`TimedRotatingFileHandler('test.log', when='D', interval=1, backupCount=30)`

#### 5.3 logging.basicConfig在代码中进行日志配置  
使用`logging.basicConfig`在代码中直接进行日志配置，具体日志格式输出格式可以参考文档。  
如果需要同时输出到屏幕和控制台，可以添加handler进行处理。  

``` Python
import logging

logging.basicConfig(level=logging.DEBUG,
                format='%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',
                datefmt='%a, %d %b %Y %H:%M:%S',
                filename='my.log',
                filemode='a')

#定义一个StreamHandler，将INFO级别或更高的日志信息打印到标准错误，并将其添加到当前的日志处理对象#
console = logging.StreamHandler()
console.setLevel(logging.INFO)
formatter = logging.Formatter('%(name)-12s: %(levelname)-8s %(message)s')
console.setFormatter(formatter)
logging.getLogger('').addHandler(console)

logging.debug('This is debug message')
logging.info('This is info message')
logging.warning('This is warning message')
logging.error('This is error message')
logging.critical('This is critical message')
```

#### 5.4 logging.config在日志文件中进行日志配置
日志配置文件独立于代码，好像又专业了些。  
在日志配置文件中，必须配置root，当`getLogger()`与`qualname`不匹配时，默认使用root配置。  

配置文件示例：  

```
[loggers]
keys=root,simpleExample1,simpleExample2,simpleExample3

[handlers]
keys=consoleHandler,fileHandler,rotatingFileHandler,timedRotatingFileHandler

[formatters]
keys=simpleFormatter,newFormatter

[logger_root]
level=DEBUG
handlers=consoleHandler

[logger_simpleExample1]
level=DEBUG
handlers=consoleHandler,fileHandler
qualname=simpleExample1
propagate=0

[logger_simpleExample2]
level=DEBUG
handlers=consoleHandler,rotatingFileHandler
qualname=simpleExample2
propagate=0

[logger_simpleExample3]
level=DEBUG
handlers=consoleHandler,timedRotatingFileHandler
qualname=simpleExample3
propagate=0

[handler_consoleHandler]
class=StreamHandler
level=DEBUG
formatter=simpleFormatter
args=(sys.stdout,)

[handler_fileHandler]
class=FileHandler
level=DEBUG
formatter=newFormatter
args=('log/file.log', 'a')

[handler_rotatingFileHandler]
class=handlers.RotatingFileHandler
level=DEBUG
formatter=simpleFormatter
#args=('log/rotating_file.log', 'a', 10*1024*1024, 5)
args=('log/rotating_file.log', 'a', 256, 5)

[handler_timedRotatingFileHandler]
class=handlers.TimedRotatingFileHandler
level=DEBUG
formatter=simpleFormatter
args=('log/time_rotating_file.log', 'm', 1, 2)


[formatter_simpleFormatter]
format=%(asctime)s - %(name)s - %(levelname)s - %(message)s
datefmt=

[formatter_newFormatter]
format=%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s
datefmt=%a, %d %b %Y %H:%M:%S
```

测试代码：  

``` Python
import logging
import logging.config

logging.config.fileConfig("simple.conf")
logger = logging.getLogger("simpleExample1")

logger.debug('This is debug message')
logger.info('This is info message')
logger.warning('This is warning message')
```

* [Logging HOWTO](https://docs.python.org/2/howto/logging.html)  
* [logging — Logging facility for Python](https://docs.python.org/2/library/logging.html)  
* [Logging Cookbook](https://docs.python.org/2/howto/logging-cookbook.html)  
* [logging.handlers](https://docs.python.org/2/library/logging.handlers.html)  
* [python 的日志logging模块学习](http://www.cnblogs.com/dkblog/archive/2011/08/26/2155018.html)  

## 6 subprocess
subprocess模块可以生成子进程，支持重定向输入、输出、错误管道，以及获取子进程的返回退出代码。  

#### 6.1 subprocess.Popen
`subprocess.Popen`对象创建后，主程序不会自动等待子进程完成。我们必须调用对象的`wait()`等方法，父进程才会等待 (也就是阻塞block)。  

###### 6.1.1 参数详解  

``` Python
subprocess.Popen(
                args, 
                bufsize=0, 
                executable=None, 
                stdin=None, 
                stdout=None, 
                stderr=None, 
                preexec_fn=None, 
                close_fds=False, 
                shell=False, 
                cwd=None, 
                env=None, 
                universal_newlines=False, 
                startupinfo=None, 
                creationflags=0)
```

* args 可以是字符串或者序列类型（如：list，元组），用于指定进程的可执行文件及其参数  
* stdin, stdout, stderr 分别表示程序的标准输入、输出、错误句柄。可以是`subprocess.PIPE`，文件描述符或文件对象进行管道重定向；也可以设置为None，表示从父进程继承  
* shell 设为true，程序将通过shell来执行  
* cwd 设置子进程的当前目录  
* env 字典类型，用于指定子进程的环境变量。如果env = None，子进程的环境变量将从父进程中继承  

关于`env`的设置，主要是在Linux下设置`LD_LIBRARY_PATH`，示例如下：  

``` Python
cur_env = os.environ
cur_env["LD_LIBRARY_PATH"] = os.path.dirname(os.path.abspath(exe))

kwargs = {'shell':True, 'stdin':subprocess.PIPE, 'stdout':subprocess.PIPE, 'stderr':subprocess.PIPE, 'env':env}
p = subprocess.Popen(cmd, **kwargs)
(child_stdin,child_stdout, child_stderr) = (p.stdin, p.stdout, p.stderr)
```

###### 6.1.2 相关函数  

* `wait()` 等待子进程执行完成  
* `communicate(input=None)`  与子进程进行交互，发送数据到stdin，从stdout获取数据，父进程等待子进程执行完成  

代码示例：  

``` Python
import subprocess
import time

# windows: ping -n 4 www.baidu.com
# linux: ping -c 4 www.baidu.com
child = subprocess.Popen(['ping', '-n', '4', 'www.baidu.com'], stdout=subprocess.PIPE)
#out = child.stdout.read()
(stdout_str, stdin_str) = child.communicate()

print "child outout:"
print stdout_str

print "parent process"
```


#### 6.2 subprocess.call
`subprocess.call`函数是在`subprocess.Popen`上进行了封装，便捷生成子进程执行程序，父进程等待子进程完成，返回退出代码（正常执行返回0）。  

``` Python
# subprocess.call(args, *, stdin=None, stdout=None, stderr=None, shell=False)
>>> subprocess.call("exit 1", shell=True)
1
```

* [subprocess — Subprocess management](https://docs.python.org/2/library/subprocess.html#module-subprocess)  
* [Python subprocess模块学习总结](http://www.jb51.net/article/48086.htm)  