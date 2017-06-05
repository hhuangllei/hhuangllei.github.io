---
layout: post
title: Hello World!
categories: [life]
modify_date: 2017-06-05 20:30:00 +0800
---

This is my first article.

How to install Jekyll on Windows?  
1. install [Ruby v2.0.0](https://rubyinstaller.org/downloads/)  
2. install [DEVELOPMENT KIT](https://dl.bintray.com/oneclick/rubyinstaller/DevKit-mingw64-64-4.7.2-20130224-1432-sfx.exe)  
3. `gem install jekyll`  
  出现的证书问题：  
  下载[cacert.pem](https://curl.haxx.se/ca/cacert.pem)到`C:\Ruby200-x64\lib\ruby\2.0.0\rubygems\ssl_certs`  

```
SSL_connect returned=1 errno=0 state=SSLv3 read server certificate B: certificate verify failed (https://rubygems.global.ssl.fastly.net/quick/Marshal.4.8/sequel-4.4.0.gemspec.rz)
```

参考文献：  
* [Run Jekyll on Windows](http://jekyll-windows.juthilo.com/)  
* [RubyInstaller](https://rubyinstaller.org/downloads/)  
* [gem update fail on windows](https://github.com/rubygems/rubygems/issues/704)  
