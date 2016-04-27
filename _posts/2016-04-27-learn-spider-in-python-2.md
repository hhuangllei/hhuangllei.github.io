---
layout: post
title: 小白学习Python爬虫(2)：urllib2的使用细节及糗事百科爬取实例
categories: [coding]
modify_date: 2016-04-27 15:00:00 +0800
---

继续小白学习Python爬虫，进一步掌握urllib2的使用细节，并通过爬取糗事百科的笑话来进行实战。

## 1. urllib2的使用细节

### 1.1 异常处理

* URLError

  通常在没有网络连接或者服器不存在的情况下产生。
这种情况下，异常会带有`reason`属性，包含一个错误号和一个错误信息。

* HTTPError

  服务器上每一个HTTP应答对象response包含一个数字“状态码”。有时状态码指出服务器无法完成请求。默认的处理器会为你处理一部分这种应答。

  HTTPError实例产生后会有一个整型'code'属性，是服务器发送的相关错误号。默认的处理器处理了重定向(300以外号码)，并且100-299范围的号码指示成功，所以你只能看到400-599的错误号码。

  HTTP状态码通常分为5种类型，分别以1~5五个数字开头，由三位整数组成：

  1. 200：请求成功      处理方式：获得响应的内容，进行处理
  2. 201：请求完成，结果是创建了新资源。新创建资源的URI可在响应的实体中得到    处理方式：爬虫中不会遇到
  3. 202：请求被接受，但处理尚未完成    处理方式：阻塞等待
  4. 204：服务器端已经实现了请求，但是没有返回新的信 息。如果客户是用户代理，则无须为此更新自身的文档视图。    处理方式：丢弃
  5. 300：该状态码不被HTTP/1.0的应用程序直接使用， 只是作为3XX类型回应的默认解释。存在多个可用的被请求资源。    处理方式：若程序中能够处理，则进行进一步处理，如果程序中不能处理，则丢弃
  6. 301：请求到的资源都会分配一个永久的URL，这样就可以在将来通过该URL来访问此资源    处理方式：重定向到分配的URL
  7. 302：请求到的资源在一个不同的URL处临时保存     处理方式：重定向到临时的URL
  8. 304 请求的资源未更新     处理方式：丢弃
  9. 400 非法请求     处理方式：丢弃
  10. 401 未授权     处理方式：丢弃
  11. 403 禁止     处理方式：丢弃
  12. 404 没有找到     处理方式：丢弃
  13. 5XX 回应代码以“5”开头的状态码表示服务器端发现自己出现错误，不能继续执行请求    处理方式：丢弃

### 1.2 Proxy代理设置
urllib2默认使用环境变量http_proxy来设置HTTP Proxy，也可以手动在程序中设置Proxy。

``` Python
enable_proxy = True
proxy_hander = urllib2.ProxyHandler({"http" : 'http://some-proxy.com:8080'})
null_proxy_hander = urllib2.ProxyHandler({})

if enable_proxy:
    opener = urllib2.build_opener(proxy_hander)
else:
    opener = urllib2.build_opener(null_proxy_hander)

urllib2.install_opener(opener)
```

使用SOCKS5代理，需要使用[SocksiPy](https://sourceforge.net/projects/socksipy/)，可以使用`pip install PySocks`安装。

``` Python
socks.setdefaultproxy(socks.PROXY_TYPE_SOCKS5, '127.0.0.1', 1080)
socket.socket = socks.socksocket
response = urllib2.urlopen(url)
```

### 1.3 Redirect设置
urllib2 默认情况下会针对 HTTP 3XX 返回码自动进行 redirect 动作，无需人工配置。要检测是否发生了 redirect 动作，只要检查一下 Response 的 URL 和 Request 的 URL 是否一致就可以了。

``` Python
my_url = 'http://xuxian.me'
response = urllib2.urlopen(my_url)
new_url = response.geturl()
redirected = new_url == my_url
if ~redirected:
    print '%s -> %s' % (my_url, new_url)
else:
    print 'No Redirect'
```

### 1.4 Cookie处理
urllib2 对 Cookie 的处理也是自动的。可以使用`cookielib`的`CookieJar`来得到Cookie的值。

``` Python
cookie = cookielib.CookieJar()
opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cookie))
response = opener.open('http://www.baidu.com')
for item in cookie:
    print 'Name = ' + item.name,
    print 'Value = ' + item.value
```

### 1.5 Debug Log设置
使用 urllib2 时，可以通过下面的方法把 debug Log 打开，这样收发包的内容就会在屏幕上打印出来，方便调试，有时可以省去抓包的工作。

``` Python
httpHandler = urllib2.HTTPHandler(debuglevel = 1)
httpsHanler = urllib2.HTTPSHandler(debuglevel = 1)
opener = urllib2.build_opener(httpHandler, httpsHanler)
urllib2.install_opener(opener)
reponse = urllib2.urlopen('http://www.baidu.com')
```

## 2. Python正则表达式
[Python正则表达式指南](http://www.cnblogs.com/huxi/archive/2010/07/04/1771073.html)

## 3. 实例爬虫-爬取糗事百科
糗事百科爬虫主要是爬取糗事百科的热点笑话，本地展示。代码是在原来的baike_spider基础上修改，还是使用的urllib2，并且未涉及到新建进程。

问题记录：

* urllib2直接urlopen返回空，需要伪造浏览器。

打开debug log，得到的信息：
```
send: 'GET / HTTP/1.1\r\nAccept-Encoding: identity\r\nHost: www.qiushibaike.com\r\nConnection: close\r\nUser-Agent: Python-urllib/2.7\r\n\r\n'
reply: ''
```

添加header，伪造浏览器：
``` Python
request = urllib2.Request(url);
request.add_header('user-agent', 'Mozilla/5.0')
response = urllib2.urlopen(request)
```
结果展示：
```
user_name = 放开她，一起来, article_id = qiushi_tag_116130960:  

想当年咱上小学的时候，班里流行开锁，人手一把锁，一根铁丝，对付一般的锁简直手到擒来，后来校长通报批评，再后来，校长室钥匙丢了，俺们班长给他开的锁。。。。。


user_name = 没名字不起了, article_id = qiushi_tag_116131122:  

自从跟儿子借了五块钱去买彩票后，每天早上儿子都从他的钱罐里拿两块钱放我手里，爸爸，拿去买彩票去！儿子，爸不能再糟蹋你的钱了，爸连5块钱都没中过啊！


user_name = 三年月, article_id = qiushi_tag_116131132:  

有个同学特别喜欢看恐怖片，有一次晚上和他妈一起回家，电梯里就他们俩人，同学又想起电影里各种灵异镜头，突然发神经回头问他妈：妈，如果我头突然掉下来，你会害怕吗？他老妈看了他一眼，面无表情很冷淡的回：你以为我是你妈？
```

参考资料：

* [Python爬虫入门教程](http://blog.csdn.net/column/details/why-bug.html)
* [Python正则表达式指南](http://www.cnblogs.com/huxi/archive/2010/07/04/1771073.html)
* [How can I use a SOCKS 4/5 proxy with urllib2?](http://stackoverflow.com/questions/2317849/how-can-i-use-a-socks-4-5-proxy-with-urllib2)
