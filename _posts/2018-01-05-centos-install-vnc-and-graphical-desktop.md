---
layout: post
title: CentOS安装VNC，配置远程桌面
categories: [coding, linux, vnc]
modify_date: 2018-01-06 10:00:00 +0800
---

一直是使用windows，熟悉IDE图形化操作调试程序（实际是不太会命令行），但最近遇到了一个jna调用so的bug。这windows没法解决，idea的IDE派不上用场了，但在linux的服器上又不会调试。最后只能曲线救国，先搞定VNC，给服器配置远程桌面，安装IDE，再来调试。  

折腾了一上午，踩了一些坑，主要是CentOS版本问题，先网上查资料没注意对应，瞎折腾 。  

## Server
### 1. 添加CentOS的repo
CentOS 7:  

```
wget -O /etc/yum.repos.d/CentOS-Base.repo http://mirrors.aliyun.com/repo/Centos-7.repo
```

CentOS 6:

```
wget -O /etc/yum.repos.d/CentOS-Base.repo http://mirrors.aliyun.com/repo/Centos-6.repo
```

### 2. 安装Gnome桌面
CentOS 7:

```
yum groupinstall -y "Desktop Platform"
```

CentOS 6:

```
yum groupinstall -y "X Window System" "Desktop Platform" Desktop
```

选装字体、管理工具等

```
yum groupinstall -y "General Purpose Desktop" "Graphical Administration Tools" "Graphics Creation Tools"
```

### 3. 安装配置vncserver

```
yum -y install tigervnc-server
```
#### 3.1 系统服务启动
  - 配置服务  

  > CentOS 7  
修改`/etc/systemd/system/vncserver@:1.service`，填写`<USER>`，配置运行ExeStart的服务运行参数

  ``` bash
  cp /lib/systemd/system/vncserver@.service /etc/systemd/system/vncserver@:1.service
  vi /etc/systemd/system/vncserver@:1.service
  ```

  ``` bash
  [Unit]
  Description=Remote desktop service (VNC)
  After=syslog.target network.target

  [Service]
  Type=forking
  User=<USER>

  # Clean any existing files in /tmp/.X11-unix environment
  ExecStartPre=-/usr/bin/vncserver -kill %i
  ExecStart=/usr/bin/vncserver -geometry 1920x1080 -nolisten %i
  PIDFile=/home/<USER>/.vnc/%H%i.pid
  ExecStop=-/usr/bin/vncserver -kill %i

  [Install]
  WantedBy=multi-user.target
  ```

  > CentOS 6  
  修改`/etc/sysconfig/vncserver`，添加display配置信息

   ```
  VNCSERVERS="1:user"
  VNCSERVERARGS[1]="-geometry 1280x800 -nolisten tcp"
  ```


  - 启动服务  

  ```
systemctl start vncserver@:1.service # 启动服务
systemctl status vncserver@:1.service # 查看服务
systemctl stop vncserver@:1.service # 关闭服务
```

#### 3.2 终端命令行启动

```
vncpasswd 123456 # 设置当前用户vnc连接密码
vncserver -geometry 1920x1080 -nolisten tcp :1 #启动服务
vncserver -list #查看服务
vncserver -kill :1 #关闭服务
```

## Client  
1. 安装vnc client  
windows用户推荐安装[VNC Viewer](https://www.realvnc.com/en/connect/download/viewer/)

2. 远程连接  
输入ip:id，输入密码，远程桌面登录，又可以继续IDE丝滑顺畅Debug

References:
* [centos7.2部署vnc服务记录](https://www.cnblogs.com/kevingrace/p/5821450.html)  ​
* [在Alios测试开发机上安装Gnome图形界面](https://www.atatech.org/articles/68622)  
* [CentOS 中 YUM 安装桌面环境](https://cnzhx.net/blog/centos-yum-install-desktop/)  
