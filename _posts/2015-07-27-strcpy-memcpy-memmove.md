---
layout: post
title: strcpy、memcpy、memmove关于内容重叠的一些事
categories: [job]
modify_date: 2015-07-27 22:00:00 +0800
---

C/C++笔试面试中，内存重叠的问题经常被问及，实际主要就是关于三个函数的故事：

* strcpy 字符串拷贝函数，不考虑内存重合
* memcpy 传说是不考虑内存重合问题
* memmove 传说是会考虑内容重合问题

但是当写代码验证时，跟想象的不太一样：**说好了只做字符串拷贝的却进行了一些古怪的操作，说好的memcpy不考虑内存重合问题的却处理内存重合。**

测试代码如下：
{% highlight C++ %}
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int main()
{
	char buf[128];	
	
	strcpy(buf, "abcdef");
	cout << buf << endl;
	//strcpy(&buf[3], buf); // 并没有出现abcabc...的重复
	
	// memcpy和memmove在内存重叠情况下，返回结果居然相同、
	// 一般的说法是memcpy不处理重叠，memmove处理重叠
	// 估计现在的实现，两者相同
	//memcpy(&buf[3], buf, 7);
	memmove(&buf[3], buf, 7);
	
	cout << buf << endl;

	int i=0;
	int a[10];
	for(i=0;i<10;i++)
	{
		a[i]=i;
	}
	memcpy(&a[4],a,6*sizeof(int));
	//memmove(&a[4],a,6*sizeof(int));
	for(i=0;i<10;i++)
	{
		printf("%d ",a[i]);
	}
	printf("\n");
	
	return 0;
}
{% endhighlight %}

最后，贴上网上流传的各种源码，各种传说的出处

* strcpy
{% highlight C++ %}
char *strcpy(char *dest,char *src)
{
        if(dest==NULL||src==NULL)
                return NULL;
        char *ret=dest;
        while((*src)!='\0')
        {
             *dest=*src;
              dest++;
              src++;
        }
        return dest;
}
{% endhighlight %}

* memcpy
{% highlight C++ %}
void *memcpy(void *dest,void *src,unsigned int n)
{
      if(dest==NULL||src==NULL)
            return NULL;
      void *ret=dest;
      while(n>0)
      {
              *(char*)dest=*(char*)src;
              dest=(char*)dest+1;
              src=(char*)src+1;
              n--;
      }
}
{% endhighlight %}

* memmove
{% highlight C++ %}
void *memmove(void *dest,const void *src,unsigned int n)
{
    if(dest==NULL||src==NULL)
         return NULL;
    char *pdest=(char*)dest;
    char *psrc=(char*)src;
    if(pdest<psrc||pdest>psrc+n)
    {
            while(n--)
            {
                  *pdest=*psrc;
                  pdest=pdest+1;
                  psrc=psrc+1;
            }
    }
    else
    {
            pdest=pdest+n-1;
            psrc=psrc+n-1;
            while(n--)
            {
                  *pdest=*psrc;
                  pdest=pdest-1;
                  psrc=psrc-1;
            }
    }
    return dest;
}
{% endhighlight %}