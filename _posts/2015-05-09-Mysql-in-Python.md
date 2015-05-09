---
layout: post
title: Mysql在Python中的使用
modify_date: 2015-05-09 21:00:00 +0800
---

最近在学python搭建网站，后端主要是基于[Tornado框架](http://demo.pythoner.com/itt2zh/index.html)，另外肯定要涉及数据库的操作。常用数据库有SQLite，MySQL，MongoDB，相对来说MySQL使用更多一些。

MySQL在Python中主要是通过两种方式来使用：

1. mysql-connector-python。MySQL官方的纯Python驱动。
2. SQLAlchemy。ORM框架SQLAlchemy，Object-Relational Mapping，把关系数据库的表结构映射到对象上。


接下来分别介绍这两种方式：

* mysql-connector-python

  该方式一般是新建数据库链接`mysql.connector.connect(param)`，再创建游标`conn.cursor()`，进而执行sql语句`cursor.execute(sqlcmd)`

  需要注意当执行插入修改等操作，需要提交事务才会生效，`conn.commit()`

  数据库插入示例代码：
{% highlight Python %}
#-*- coding:utf-8 -*-

import mysql.connector

def main():
    conn = mysql.connector.connect(user='root', password='root', database='test', use_unicode=True)
    cursor = conn.cursor()
    cursor.execute('create table user2 (id varchar(20) primary key, name varchar(20))')
    cursor.execute("insert into user (id, name) values (%s, %s)", ["3", "void"])
    print cursor.rowcount

    conn.commit()
    cursor.close()
    conn.close()

if __name__ == "__main__":
    main()
{% endhighlight %}

  数据库查询示例代码：

{% highlight Python %}
#-*- coding:utf-8 -*-

import mysql.connector

def main():
    conn = mysql.connector.connect(user='root', password='root', database='test', use_unicode=True)
    cursor = conn.cursor()
    cursor.execute("select * from user")
    values = cursor.fetchall()

    print values
    cursor.close()
    conn.close()

if __name__ == "__main__":
    main()
{% endhighlight %}


* SQLAlchemy
	
  数据库表格创建示例代码：
{% highlight Python %}
from sqlalchemy import MetaData, Table, Column, String, create_engine, ForeignKey
from sqlalchemy.orm import sessionmaker
from sqlalchemy.ext.declarative import declarative_base

Base = declarative_base()
# 初始化数据库连接:
engine = create_engine('mysql+mysqlconnector://root:root@localhost:3306/test', echo=True)
metadata = MetaData(engine)

user = Table(
    "user", metadata,
    Column("id", String(20), primary_key=True),
    Column("name", String(20))
    )


book = Table(
    "book", metadata,
    Column('id', String(20), primary_key=True),
    Column('name', String(20)),
    Column('user_id', String(20), ForeignKey("user.id"))
    )


book.create()

{% endhighlight %}

  数据库插入示例代码：

{% highlight Python %}
#-*- coding:utf-8 -*-

from sqlalchemy import Column, String, create_engine, ForeignKey
from sqlalchemy.orm import sessionmaker
from sqlalchemy.ext.declarative import declarative_base

Base = declarative_base()

class User(Base):
    __tablename__ = "user"

    id = Column(String(20), primary_key=True)
    name = Column(String(20))
    #books = relationship("Book")

class Book(Base):
    __tablename__ = 'book'

    id = Column(String(20), primary_key=True)
    name = Column(String(20))

    user_id = Column(String(20), ForeignKey("user.id"))

# 初始化数据库连接:
engine = create_engine('mysql+mysqlconnector://root:root@localhost:3306/test')
# 创建DBSession类型:
DBSession = sessionmaker(bind=engine)

# 创建session对象:
session = DBSession()
# 创建新User对象:
#new_user = User(id='3', name='sqlalchemy')
# 添加到session:
#session.add(new_user)

new_book = Book(id="1", name="book1", user_id="1")
session.add(new_book)

# 提交即保存到数据库:
session.commit()
# 关闭session:
session.close()
{% endhighlight %}

  数据库查询示例代码：

{% highlight Python %}
#-*- coding:utf-8 -*-

from sqlalchemy import Column, String, create_engine, ForeignKey
from sqlalchemy.orm import sessionmaker
from sqlalchemy.ext.declarative import declarative_base

Base = declarative_base()

class User(Base):
    __tablename__ = "user"

    id = Column(String(20), primary_key=True)
    name = Column(String(20))
    #books = relationship("Book")
    def __str__(self):
        return "id: %s\tname: %s\n" % (self.id, self.name)

class Book(Base):
    __tablename__ = 'book'

    id = Column(String(20), primary_key=True)
    name = Column(String(20))

    user_id = Column(String(20), ForeignKey("user.id"))

# 初始化数据库连接:
engine = create_engine('mysql+mysqlconnector://root:root@localhost:3306/test')
# 创建DBSession类型:
DBSession = sessionmaker(bind=engine)

# 创建session对象:
session = DBSession()

user = session.query(User).filter(User.id=='1').one()
print user

users = session.query(User).all()
print "count %d\n" % len(users)
for user in users:
    print user    

# 关闭session:
session.close()
{% endhighlight %}


参考文献：

* http://www.liaoxuefeng.com
* http://www.jb51.net/article/49457.htm
* http://blog.csdn.net/dupei/article/details/6014488
* http://blog.csdn.net/tastelife/article/details/25218895
* http://www.dongwm.com/archives/sqlalchemyjiaochengyi/