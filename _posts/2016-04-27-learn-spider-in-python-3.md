---
layout: post
title: 小白学习Python爬虫(3)：Scrapy入门教程
categories: [coding]
modify_date: 2016-04-27 22:00:00 +0800
---

小白学习Python爬虫，开始进阶爬虫框架学习。

Scrapy是目前流行的Python爬虫框架。
首先安装Scrapy，直接`pip install scrapy`，提示错误。开始看安装文档，需要一些其他包的支持。

* [Python](https://www.python.org/) 2.7
* [pip](https://pip.pypa.io/en/latest/installing.html)和[setuptools](https://pypi.python.org/pypi/setuptools)
* [lxml](http://lxml.de/)
* [OpenSSL](https://pypi.python.org/pypi/pyOpenSSL)

一般来说安装Python后都有pip，lxml和OpenSSL，但需要安装[setuptools](https://pypi.python.org/pypi/setuptools)，并更新[lxml](https://pypi.python.org/pypi/lxml)。
但是继续提示错误

```
error: Microsoft Visual C++ 9.0 is required <unable to find vcvarsall.bat>
```

原来是提示编译器问题，VC++ 9.0是VS2008中的编译器，够老的。。。估计是python或者pip版本的问题，所以使用的老版本的编译器？通过修改环境变量可以解决。

* 添加环境变量 `VS90COMNTOOLS`
* 设置变量值为当前已有编译器的变量值，比如现在机器上已有VC++ 12.0，即变量`VS120COMNTOOLS`

随后，安装成功，开始学习教程。

## 1. 创建项目
在命令行输入`scrapy startproject tutorial`，自动创建项目，目录树展示如下：

```
tutorial/
    scrapy.cfg            # deploy configuration file

    tutorial/             # project's Python module, you'll import your code from here
        __init__.py

        items.py          # project items file

        pipelines.py      # project pipelines file

        settings.py       # project settings file

        spiders/          # a directory where you'll later put your spiders
            __init__.py
            ...
```

## 2. 定义容器
Item是装载爬取数据的容器，类似先前实现简易爬虫代码中的Python字典。在`.\turorial\items.py`中定义Iterm的域。

``` Python
import scrapy

class DmozItem(scrapy.Item):
    title = scrapy.Field()
    link = scrapy.Field()
    desc = scrapy.Field()
```

## 3. 实现爬虫
Spider是用户定义的让Scrapy使用来爬取网站数据的类。

Spider定义了初始URL列表，如何扩充URL（URL管理器），如何下载并解析内容得到Iterms（下载器，解析器）。

Spider类是scrapy.Spider类的子类，需要用户在`.\tutorial\spiders`目录下创建自己的类，并定义一些属性：name, start_urls, parse()。

创建`.\tutorial\spiders\dmoz_spider.py`，示例如下：	

``` Python
import scrapy

class DmozSpider(scrapy.Spider):
    name = "dmoz"
    allowed_domains = ["dmoz.org"]
    start_urls = [
        "http://www.dmoz.org/Computers/Programming/Languages/Python/Books/",
        "http://www.dmoz.org/Computers/Programming/Languages/Python/Resources/"
    ]

    def parse(self, response):
        filename = response.url.split("/")[-2] + '.html'
        with open(filename, 'wb') as f:
            f.write(response.body)
```

## 4.  爬取数据

基本工作已经完成，在项目目录下执行

`scrapy crawl dmoz`

使用dmoz的爬虫（我们自己定义的名字）来爬取数据，但此时提示错误：

`ImportError: No module named win32api`

通过`pip install pypiwin32`安装相应的包，重新执行刚才的命令，在项目目录下爬取得到两个网页。

Scrapy框架对`start_urls`中URL创建`scrapy.Request`对象来进行请求访问，并执行`parse`方法进行解析。

进一步，使用先前定义的容器来保存数据：

``` Python
import scrapy

from tutorial.items import DmozItem

class DmozSpider(scrapy.Spider):
    name = "dmoz"
    allowed_domains = ["dmoz.org"]
    start_urls = [
        "http://www.dmoz.org/Computers/Programming/Languages/Python/Books/",
        "http://www.dmoz.org/Computers/Programming/Languages/Python/Resources/"
    ]

    def parse(self, response):
        for sel in response.xpath('//ul[@class="directory-url"]/li'):
            item = DmozItem()
            item['title'] = sel.xpath('a/text()').extract()
            item['link'] = sel.xpath('a/@href').extract()
            item['desc'] = sel.xpath('text()').extract()
            yield item
```

运行`scrapy crawl dmoz -o items.json`，爬取数据并存储到iterms.json文件。scrapy默认是追加文件内容，即若存在文件不覆盖。

目前为止，完成3篇小白学习Python爬虫系列文章，指导小组已经返回论文意见，必须得把精力转回到论文修改的毕业大事，后续再继续小白进阶。

参考资料：

* [Python Pip install Error: Unable to find vcvarsall.bat.](http://stackoverflow.com/questions/27670365/python-pip-install-error-unable-to-find-vcvarsall-bat-tried-all-solutions)
* [Scrapy Tutorial](http://doc.scrapy.org/en/latest/intro/tutorial.html)