---
layout: post
title: 安卓中的网络请求
categories: [coding, Java, Android]
modify_date: 2016-12-22 16:00:00 +0800
---

新手开发安卓SDK，需要联网验证，那就从最基本的HttpURLConnection用起，顺路收集整理了一些资料，方便以后学习提高。

### 1. 网络访问库使用进阶之路
`HttpClient` -> `HttpURLConnection` -> `Volley` -> `OkHttp` -> `Retrofit`  

* `HttpClient`  
[apache出品](http://hc.apache.org/httpcomponents-client-ga/)，现在Android2.3后已逐渐转向`HttpURLConnection`，具体原因可以参考这篇[博客](http://blog.csdn.net/guolin_blog/article/details/12452307)。  
* `HttpURLConnection`  
系统内置库，`java.net.HttpURLConnection`  
* `Volley`  
[Github地址](https://github.com/mcxiaoke/android-volley)，已停止更新。  
* `OkHttp`  
square出品，[官网地址](http://square.github.io/okhttp/)。  
* `Retrofit`  
square出品，[官网地址](http://square.github.io/retrofit/)，封装`OkHttp`，RestAPI操作。  

推荐使用`HttpURLConnection`，`OkHttp`和`Retrofit`，具体参见[参考文献一](http://www.jianshu.com/p/3141d4e46240)。

### 2. Https网络访问  

涉及证书的https，未编码尝试，网上搜索了一些相关资料，但感觉比较老，很多使用`HttpClient`或者`HttpsURLConnection`。后续涉及使用再花时间整理。

### 3. Android使用网络访问库
安卓不能把网络请求放主线程，防止阻塞  
`android.os.NetworkOnMainThreadException`  
使用Thread的join()方法，join()方法会阻塞主线程继续向下执行  

### 4. Android网络访问的一些杂事  

#### 4.1 网络状态判断  
* 是否有网络链接  
* 是否是wifi  
* 是否是手机网络  

#### 4.2 时间戳  
时间戳以及格式化输出 Date和SimpleDateFormat  

```java
Date date = new Date();
long timestamp = date.getTime();
SimpleDateFormat simpleDateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
String res = simpleDateFormat.format(date);

// 时间转时间戳
String timeStr1 = "2016-12-06 12:00:00";
Date date1 = simpleDateFormat.parse(timeStr1);
long timestamp1 = date1.getTime();

// 时间戳转时间
long timestamp2 = 1480996800000L;
Date date2 = new Date(timestamp2);
String timeStr2 = simpleDateFormat.format(date2);
```

* [Android网络请求心路历程](http://www.jianshu.com/p/3141d4e46240)  
* [Android之NetworkOnMainThreadException异常](http://blog.csdn.net/mad1989/article/details/25964495)  
* [判断网络连接状态](http://www.2cto.com/kf/201501/368943.html)  
* [浅析Android系统中HTTPS通信的实现浅析Android系统中HTTPS通信的实现](http://www.jb51.net/article/70419.htm)  
* [使用HttpsURLConnection发送POST请求](http://www.cnblogs.com/cxjchen/archive/2013/06/24/3152832.html)  
* [https HttpsURLConnection请求的单向认证](https://my.oschina.net/ososchina/blog/500925)  
* [Android Https请求详细demo](http://gjican.iteye.com/blog/2153177)  
* [Java实现主线程等待子线程](http://blog.csdn.net/nms312/article/details/30115055)  
* [Java时间和时间戳的相互转换](http://www.cnblogs.com/mstk/p/5511057.html)  
* [SimpleDateFormat使用详解](http://blog.csdn.net/gubaohua/article/details/575488)  
