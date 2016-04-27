---
layout: post
title: 小白学习Python爬虫(1)：Python开发简单爬虫
categories: [coding]
modify_date: 2016-04-27 12:30:00 +0800
---

又是大半年没来打理博客了，惭愧 T_T

刚好这段时间交了论文初稿，有些闲暇时间，对Python爬虫感兴趣，就开始了Python爬虫学习。实际自己只是算作会简单使用Python，也没怎么弄过爬虫，就收集整理了些资料，记录自己的学习之旅。

这篇博客作为小白学习Python爬虫系列的入门篇，主要内容是跟着学习imooc上的一门公开课：[Python开发简单爬虫](http://www.imooc.com/learn/563)。自己动手做了一些笔记，并且把相关学习记录及代码放到了[github](https://github.com/mrknight-cn/imooc-python-simple-crawler/tree/v1.0)。

## 1. 简单爬虫架构

调度器 -> URL管理器 -> 下载器 -> 解析器 -> 应用

### 1.1 URL管理器
管理待抓取URL集合和已抓取URL集合

* 防止重复抓取，防止循环抓取

实现方式：

* 内存 python的set
* 关系数据库 MySQL
* 缓存数据库 redis

### 1.2 网页下载器
将互联网上URL对应的网页下载到本地的工具

* urllib2 Python 官方基础模块
* [requests](http://docs.python-requests.org/en/master/) 第三方（推荐）

urllib2 /test/test_urllib2.py

* 基本方法

{% highlight Python %}
url = 'http://www.baidu.com'
urllib2.urlopen(url)
{% endhighlight %}

* 添加data、http header

{% highlight Python %}
request = urllib2.Request(url)
request.add_header('user-agent', 'Mozilla/5.0')
response2 = urllib2.urlopen(request)
{% endhighlight %}

* 添加特殊情景的处理器

{% highlight Python %}
cj = cookielib.CookieJar()
opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cj))
urllib2.install_opener(opener)
response3 = urllib2.urlopen(url)
{% endhighlight %}

### 1.3 网页解析器
从网页中提取有价值数据的工具

* 正则表达式
* html.parser
* [Beautiful Soup](https://www.crummy.com/software/BeautifulSoup/) 第三方（推荐）
* lxml 第三方

结构化-DOM（Document Object Model）树

BeautifulSoup /test/test_bs4.py

## 2. 实例爬虫

1. 确定目标
2. 分析目标
  * URL格式
  * 数据格式
  * 网页编码
3. 编写代码
4. 执行爬虫

代码布局

* 主函数 spider_main.py
* URL管理器 url_manager.py
* 下载器 html_downloader.py
* 解析器 html_parser.py
* 输出处理 html_outputer.py
