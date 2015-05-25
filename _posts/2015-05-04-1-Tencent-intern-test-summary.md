---
layout: post
title: Tencent实习线下笔试经验总结
categories: [job]
modify_date: 2015-05-04 20:00:00 +0800
---

4月18日，参加了Tencent实习招聘线下笔试，由于自己准备不足，同时不给与足够重视重视，直接悲惨被刷（但却写着茫茫人海找不到简历来婉拒）。总体感觉是腾讯的笔试，公司很重视，在清华教室线下笔试，监考老师，答题卡，这些都感觉有些遥远了，但腾讯就使用这种方式来筛人。

**考试面很广，内容多且杂**

C/C++，算法，数据结构，数据库，网络，操作系统，Javascript，Objective C

1. 数据库操作

	查找一张表，重复元素的数目

	select id,count(*) from table1 group by id

	http://blog.chinaunix.net/uid-12707183-id-2919036.html

2. 约瑟夫环问题


3. 检测单向链表是否有环

	快慢指针，快指针+2，慢指针+1，有环必定相遇。时间复杂度为O(2n)

	该问题还可以延伸出检测环入口的位置。

	http://blog.csdn.net/gukesdo/article/details/7516021