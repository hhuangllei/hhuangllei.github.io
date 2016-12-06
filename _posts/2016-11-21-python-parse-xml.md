---
layout: post
title: Python解析XML
categories: [coding]
modify_date: 2016-11-21 11:00:00 +0800
---

在使用Python进行XML解析时，首选使用ET模块

[XML特殊字符的转义处理](https://wiki.python.org/moin/EscapingXml)  
` xml.sax.saxutils`模块中的`escape()`和`quoteattr()`

```
from xml.sax.saxutils import escape
from xml.sax.saxutils import quoteattr
```

* `escape()`处理特殊字符`<, &, >`

```
>>> from xml.sax.saxutils import escape
>>>
>>> escape("< & >")
'&lt; &amp; &gt;'
```

`unescape()`反转义  

```
>>> from xml.sax.saxutils import unescape
>>>
>>> unescape("&lt; &amp; &gt;")
'< & >'
```

* `quoteattr()`支持更多的特殊字符  
注意：该函数会自动添加适合的单引号或者双引号包含字符串，所以不需要手动添加单引号或者双引号去包含字符串。

* [深入解读Python解析XML的几种方式](http://kb.cnblogs.com/page/549886/)  
* [用Python解析XML的几种常见方法的介绍](http://www.jb51.net/article/63780.htm)  
* [ET模块的使用](http://www.cnblogs.com/hongten/p/hongten_python_xml_etree_elementtree.html)  