---
layout: post
title: 博客中git与Markdown
categories: [coding, life]
modify_date: 2016-09-07 23:00:00 +0800
---

从一开始在git上搭建博客，就一直使用Markdown编写博客，写作过程中有时需要一些格式排版，所以就逐步学习Markdown语法。  
实际Markdown语法相对简单，但自己也遇到一些问题，不易察觉，还会花费些时间，记录下。  

## 1. git的使用

### 1.1 git常用配置
修改git全局配置文件`~/.gitconfig`：

```
[alias]
	st = status
	ci = commit
	co = checkout
	br = branch

	clog = log --graph --format=format:'%C(bold blue)%h%C(reset) - %C(bold green)(%ar)%C(reset) %C(white)%s%C(reset) %C(bold white)— %an%C(reset)%C(bold yellow)%d%C(reset)' --abbrev-commit --date=relative --show-signature
[core]
	autocrlf = true
```

### 1.2 git的ssh-key自动添加
在Windows上使用git，最开始不需要自己手动添加ssh-key的，但后来更新不知咋的就每次使用`Git Bash`必须手动添加才能有权上传代码到服器。
每次需要在git中执行：  

```
$ eval "(ssh-agent -s)"
$ ssh-add ~/.ssh/id_rsa
```

实际写博客次数也不多T_T，所以当偶尔心血来潮准备写博客时，又会忘记添加ssh-key，又跑去找下命令，终于忍不了繁琐，寻找自动添加的办法：  
在用户目录下`C:\Users\xx\`创建`.bashrc`文件，内容如下：

```bash
#! /bin/bash
eval `ssh-agent -s`
ssh-add ~/.ssh/id_rsa_qq
```

当运行`Git Bash`时，首先会运行该脚本，解决问题。

### 1.3 git的一些命令

* 修改最近一次的commit信息

```bash
git commit --amend

```

* 版本回退
注意`--hard`和`--soft`，使用`--hard`确认丢弃的修改不要，最好备份后操作。  

```bash
git reset --hard #回退到HEAD，丢弃本地unstaged的修改
git reset --soft/--hard HEAD^  #HEAD回退到上一次commit
git reset --soft/--hard HEAD~1 #HEAD回退到上一次commit
git reset --soft/--hard HEAD~2
git reset --soft/--hard <commit>
```

* 丢弃本地unstaged的修改

```bash
git clean -df # 删除本地所有untracked的文件
git reset --hard # 回退本地tracked文件的修改
```

这地方踩过坑，不要随便删除本地修改，**最好先备份再删除**，可能一下操作把好几个小时的工作量给浪费了。。。  
慎用`git checkout -f`！！！  

* 选择另外一个分支的commit合并到当前分支

```bash
git cherry-pick <commit>
```

## 2. Markdown语法的隐藏细节

### 2.1 换行
原来每次换行，我都是中间空一行，但很难看，都后来才知道正确的写法，**行末两个空格**。  

* 中间空一行是段落间隔：

```
a

b
```

a

b

* 行末两个空格是行间距

```
a  
b
```

a  
b

### 2.2 表格创建
表格依葫芦画瓢，照着语法写，但还是在博客上却未成功生成，先以为是Markdown的解释器原因，还跑去查配置中`Kramdown`的问题。。。  
最后发现是表格前必须有空行，行末两个空格都不行。

| head1 | head2 | head3 |
| :---- | :---: | ----: |
| 1 | 2 | 3 |

### 2.3 代码区块高亮
最开始是使用的如下语法来实现高亮，如下：  

```
{ % highlight c++ % }
#include <iostream>
using namespace std;
{ % endhighlight % }

```
但感觉比较麻烦，看到可以用三个backtick`` ` ``的Fenced code blocks语法来实现高亮，简洁高效，但是最开始依然画瓢失败。。。自己本地在atom里写好的博客预览可以代码高亮，上传到Github却乱成一团。  
最开始都以为Github博客是不是不支持这种语法啊，但官网都给出了文档不应该啊，又开始怀疑`_config.yml`配置问题，里面设置的`highlighter: rouge`是不是有问题呢，折腾了一会儿，又发现是空行啊！！！与表格语法一样，需要在代码块前留空行！！！

参考文献：  
* [Writing on GitHub](https://help.github.com/categories/writing-on-github/)
* [Organizing information with tables](https://help.github.com/articles/organizing-information-with-tables/)  
* [Creating and highlighting code blocks](https://help.github.com/articles/creating-and-highlighting-code-blocks/)  
