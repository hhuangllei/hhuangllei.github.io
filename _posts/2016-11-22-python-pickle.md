---
layout: post
title: Python使用pickle持久化对象
categories: [coding]
modify_date: 2016-11-22 20:00:00 +0800
---

pickle模块是Python中实现对象序列化和反序列化的常用模块。使用pickle可以持久化Python对象，将对象作为文件保存在磁盘，在需要的时候再读取还原。  

### 1. pickle的使用  

* obj -> text  
pickle.dumps(obj[, protocol])  
* text -> obj  
pickle.loads(string)  
* obj -> file  
pickle.dump(obj, file[, protocol])
* file -> obj  
pickle.load(file)
* pickle exception  
pickle.PickleError pickle基础异常  
pickle.PicklingError pickle序列化异常  
pickle.UnpicklingError pickle反序列化异常  

### 2. pickle的细节  
测试环境 Windows 7, Python 2.7.12

* pickle和cPicke  
cPickle加速明显，在2.x版本下尽量使用cPickle

* pickle的压缩选项  
几倍压缩效果，pickle的数据量较大则尽量压缩

* 文件打开方式的影响  
不压缩pickle，使用`w`和`wb`生成的文件大小有些许差别。并且序列化和反序列化`w`和`r`、`wb`和`rb`可不对应，但代码规范要求下应该对应。  
压缩pickle，尽量使用`wb`和`rb`，否则有时可能代码出错，可能与文件内容相关。

Demo代码：

```Python
# -*- coding: utf-8 -*-
 
import cPickle as pickle
import pickle as oripickle
import random
import os
 
import time
 
LENGTH = 1000 * 1000

class Person:
	def __init__(self, name, age):
		self.name = name
		self.age = age

def ClassTest():
	p1 = Person("xiaoming", "7")
	p2 = Person("xiaohua", "6")
	
	pickle.dump([p1, p2], open("cls.dat", "wb"), True)
	(pp1, pp2) = pickle.load(open("cls.dat", "rb"))
	print pp1.name, pp1.age
	print pp2.name, pp2.age
		
def OpenAndCompressTest():
	d = {}
	a = []
	for i in range(LENGTH):
		a.append(random.randint(0, 255))
 
	d["a"] = a
 
	print "dumping..."

	t1 = time.time()
	pickle.dump(d, open("tmp_w_noncompress.dat", "w"), False)
	print "dump_w_noncompress: %.3fs" % (time.time() - t1)
	
	t1 = time.time()
	pickle.dump(d, open("tmp_wb_noncompress.dat", "wb"), False)
	print "dump_wb_noncompress: %.3fs" % (time.time() - t1)
	
	'''
	t1 = time.time()
	pickle.dump(d, open("tmp_w_compress.dat", "w"), True)
	print "dump_w_compress: %.3fs" % (time.time() - t1)
	'''
	
	t1 = time.time()
	pickle.dump(d, open("tmp_wb_compress.dat", "wb"), True)
	print "dump_wb_compress: %.3fs" % (time.time() - t1)
	
	t1 = time.time()
	oripickle.dump(d, open("tmp_ori_wb_compress.dat", "wb"), True)
	print "dump_ori_wb_compress: %.3fs" % (time.time() - t1)
	
	s_w_noncompress = os.stat("tmp_w_noncompress.dat").st_size
	s_wb_noncompress = os.stat("tmp_wb_noncompress.dat").st_size
	s_wb_compress = os.stat("tmp_wb_compress.dat").st_size
 
	print "%.2fKB, %.2fKB, %.2fKB" % (s_w_noncompress / 1024.0, s_wb_noncompress / 1024.0, s_wb_compress / 1024.0)
 
	print "loading..."
 
	t1 = time.time()
	obj1 = pickle.load(open("tmp_w_noncompress.dat", "r"))
	print "load_w_noncompress: %.3fs, num %d" % (time.time() - t1, len(obj1["a"]))
	
	t1 = time.time()
	obj2 = pickle.load(open("tmp_wb_noncompress.dat", "rb"))
	print "load_wb_noncompress: %.3fs, num %d" % (time.time() - t1, len(obj2["a"]))
	
	'''
	t1 = time.time()
	obj3 = pickle.load(open("tmp_w_compress.dat", "rb"))
	print "load_w_compress: %.3fs, num %d" % (time.time() - t1, len(obj3["a"]))
	'''
	
	t1 = time.time()
	obj4 = pickle.load(open("tmp_wb_compress.dat", "rb"))
	print "load_wb_compress: %.3fs, num %d" % (time.time() - t1, len(obj4["a"]))
	

def main():
	OpenAndCompressTest()
	ClassTest()
 
if __name__ == "__main__":
	main()
```

运行结果:

```bash
dumping...
dump_w_noncompress: 0.439s
dump_wb_noncompress: 0.416s
dump_wb_compress: 0.104s
dump_ori_wb_compress: 2.673s
6415.29KB, 5438.72KB, 1955.09KB
loading...
load_w_noncompress: 0.769s, num 1000000
load_wb_noncompress: 0.742s, num 1000000
load_wb_compress: 0.216s, num 1000000
xiaoming 7
xiaohua 6
```

### 3. pickle与Python其他模块  
* cPickle  
使用C写的加速版本，在Python 2.x中可引入，但在Python 3.x中移除。  

```
import cPickle as pickle
```
* marshal  
更底层的Python序列化模块，不支持用户自定义类的序列化。
* json  
JSON是文本序列化格式，输出unicode（常为utf-8）；pickle是二进制序列化格式  
JSON是人类可读的  
JSON是通用格式；pickle是python专有  
JSON默认是不支持用户自定义类的序列化  


* [官方文档Python3.5.2 pickle — Python object serialization](http://www.cnblogs.com/fnng/p/3518202.html)  
* [官方文档Python2.7.12 pickle — Python object serialization](https://docs.python.org/2/library/pickle.html)  
* [Python cPickle模块用法](http://blog.csdn.net/yucan1001/article/details/8478755)  
* [Python中使用pickle持久化对象](http://oldj.net/article/python-pickle/)  