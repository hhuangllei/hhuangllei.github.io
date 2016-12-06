---
layout: post
title: Java网络请求http，https
categories: [coding, Java, Android]
modify_date: 2016-12-06 12:00:00 +0800
---


安卓不能把网络请求放主线程，防止阻塞  
android.os.NetworkOnMainThreadException  
使用Thread的join()方法，join()方法会阻塞主线程继续向下执行  


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
* [Java实现主线程等待子线程](http://blog.csdn.net/nms312/article/details/30115055)  
* [Java时间和时间戳的相互转换](http://www.cnblogs.com/mstk/p/5511057.html)  
* [SimpleDateFormat使用详解](http://blog.csdn.net/gubaohua/article/details/575488)  