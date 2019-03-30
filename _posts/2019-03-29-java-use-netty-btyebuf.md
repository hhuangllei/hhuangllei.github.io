---
layout: post
title: Netty ByteBuf下藏的坑
categories: [coding, java]
modify_date: 2019-03-30 15:30:00 +0800
---

最近一直在使用Netty开发服务，但在敏捷开发的快节奏下快速上手就没细看文档，在前人基础上照着样子写着代码，完成了功能开发，通过了验证测试，上线也稳定运行。  
一切看似美好，直到最近发现服务内存缓慢上涨，最终导致OutOfDirectMemoryError的悲剧。  
还好有老司机协助排查，但也折腾费了一番功夫，实际也是一些Netty使用基础没打牢，其中就有ByteBuf的使用与释放问题。  
只追求开发速度留下的祸患，“上手就干”的利弊值得思考。

## 1. ByteBuf介绍  
`ByteBuf`是Netty对于字节数组和NIO缓存的封装，是Netty进行高效率的内存操作的基础。

`ByteBuf`包含`readerIndex`和`writerIndex`两个指针来进行读写操作，和Java的`ByteBuffer`类似。

```
      +-------------------+------------------+------------------+
      | discardable bytes |  readable bytes  |  writable bytes  |
      |                   |     (CONTENT)    |                  |
      +-------------------+------------------+------------------+
      |                   |                  |                  |
      0      <=      readerIndex   <=   writerIndex    <=    capacity
```

分类：  
- Pooled和Unpooled：pooled类型的bytebuf是在已经申请好的内存块取一块内存，而Unpooled是直接通过JDK底层代码申请。
- Unsafe和非Unsafe：这里的Unsafe是JDK底层的对象，通过它能够直接操作到内存。
- Heap和Direct：一个是在堆上分配，一个是直接内存。Direct不受GC的控制。


## 2. ByteBuf使用  
根据官方建议，优先使用`Unpooled`创建使用，避免引入不确定性、依赖系统实现的其他创建方式。

``` java
ByteBuf pooledDirectBuffer = PooledByteBufAllocator.DEFAULT.directBuffer(8192); //direct buffer
ByteBuf unpooledDirectBuffer = UnpooledByteBufAllocator.DEFAULT.directBuffer(8192); //direct buffer

ByteBuf heapBuffer    = Unpooled.buffer(128);
ByteBuf directBuffer  = Unpooled.directBuffer(256);
ByteBuf wrappedBuffer = Unpooled.wrappedBuffer(new byte[128], new byte[256]);
ByteBuf copiedBuffer  = Unpooled.copiedBuffer(ByteBuffer.allocate(128));
```

- [PooledByteBufAllocator](https://netty.io/4.1/api/io/netty/buffer/PooledByteBufAllocator.html)  
- [UnpooledByteBufAllocator](https://netty.io/4.1/api/io/netty/buffer/UnpooledByteBufAllocator.html)  

## 3. ByteBuf引用计数  
ByteBuf生命周期和其他Java对象一致，根据引用计数进行回收使用，而ByteBuf操作使用的直接内存是需要Netty来根据引用计数来释放归还内存。  
当ByteBuf的引用计数未清0而被GC回收掉时，使用的直接内存可能就还未被Netty释放归还就会导致内存泄漏，所以使用ByteBuf需要谨慎何时调用`release()`来管理引用计数。  

关于ByteBuf的释放，原则就是最后一个使用的地方必须承担释放责任，实际一般就是谁创建谁释放，建议阅读三遍官方文档**[Reference counted objects](https://netty.io/wiki/reference-counted-objects.html)**！  

其中涉及`Derived buffers`和`ByteBufHolder`会共享计数，看来确实有些复杂。其实写代码使用ByteBuf时保持一根释放内存的弦就可以，就算泄漏了也还有Netty自带的内存泄漏检测器`-Dio.netty.leakDetectionLevel=advanced`，能够支持比较快捷的排查，但最好提前在单元测试或者预发环境发现泄漏。

如果引用计数为0，继续使用则会报异常： 

```
Exception in thread "main" io.netty.util.IllegalReferenceCountException: refCnt: 0
```

## 4. ByteBuf藏的坑  

### 4.1. 内存释放  
使用`ByteBuf.copy()`和`ByteBuf.readBytes(int length)`等操作会深拷贝新建ByteBuf，留意释放操作，能`wrap`就不`copy`。

否则造成容易造成直接内存泄漏

```
Exception in thread "main" io.netty.util.internal.OutOfDirectMemoryError: failed to allocate 16777216 byte(s) of direct memory (used: 1761607680, max: 1776812032)
```

### 4.2. wrap和slice的引用计数  
这两种操作，看起来都是ByteBuf的浅拷贝，可读区域非空时都是调用返回`buffer.slice()`，但在可读区域为空时引用计数逻辑却不一样  
注意：使用这两种方法时，需要显式使用`ByteBuf.retain()`来增加原始引用计数

- wrap `Unpooled.wrappedBuffer(ByteBuf buffer)`  
包装原始ByteBuf的可读内存区域来新建一个ByteBuf，对原始内存区域的修改会直接对新拷贝的ByteBuf可见。  
Creates a new buffer which wraps the specified buffer's **readable bytes**. A modification on the specified buffer's content will be visible to the returned buffer

  - 浅拷贝ByteBuf，原始ByteBuf引用计数减1，目标ByteBuf单独计数但无实际内存分配  
  - 调用时，可读区域非空，则原始ByteBuf引用计数不变；若可读区域为空，原始ByteBuf引用计数减1，包装出来的ByteBuf为`ByteBufFER`  

  **可读区域为空的处理逻辑不是太理解**，为啥原始ByteBuf引用需要减1？
  ``` java
      public static ByteBuf wrappedBuffer(ByteBuf buffer) {
        if (buffer.isReadable()) {
            return buffer.slice();
        } else {
            buffer.release();
            return EMPTY_BUFFER;
        }
    }
  ```
  
- slice `ByteBuf.slice()`
对原始ByteBuf的可读内存区域进行分片，得到新的浅拷贝的ByteBuf。  
Returns a slice of this buffer's **readable bytes**. 

  - 浅拷贝ByteBuf，和原始ByteBuf共享引用计数，目标ByteBuf单独计数但无实际内存分配  

代码测试基于Netty4.1

``` java
    public static void main(String[] args) {
        ByteBuf data  = Unpooled.directBuffer(8192); // data.refCnt() -> 1
        System.out.println(String.format("data_ref=%d", data.refCnt()));
        data.retain();                                             // data.refCnt() -> 2
        System.out.println(String.format("data_ref=%d", data.refCnt()));

        System.out.print(String.format("data_readableBytes=%d\t", data.readableBytes()));
        data.writeBytes(new byte[100]);
        System.out.println(String.format("data_readableBytes=%d\t", data.readableBytes()));

        // wrap和slice浅拷贝
        ByteBuf wrap = Unpooled.wrappedBuffer(data);               // wrap.refCnt() -> 2, data.refCnt() -> 2
        System.out.println(String.format("data_ref=%d, wrap_ref=%d", data.refCnt(), wrap.refCnt()));
        ByteBuf slice = data.slice();                              // slice.refCnt() -> 2
        System.out.println(String.format("data_ref=%d, wrap_ref=%d, slice_ref=%d",
            data.refCnt(), wrap.refCnt(), slice.refCnt()));

        System.out.println(String.format("data_readableBytes=%d, wrap_readableBytes=%d, slice_readableBytes=%d",
            data.readableBytes(), wrap.readableBytes(), slice.readableBytes()));
        data.writeByte(1);
        System.out.println(String.format("data_readableBytes=%d, wrap_readableBytes=%d, slice_readableBytes=%d",
            data.readableBytes(), wrap.readableBytes(), slice.readableBytes()));

        data.release();                                            // data.refCnt() -> 1
        System.out.println(String.format("data_ref=%d, wrap_ref=%d, slice_ref=%d",
            data.refCnt(), wrap.refCnt(), slice.refCnt()));
    }
```

输出：

```
data_ref=1
data_ref=2
data_readableBytes=0	data_readableBytes=100	
data_ref=2, wrap_ref=2
data_ref=2, wrap_ref=2, slice_ref=2
data_readableBytes=100, wrap_readableBytes=100, slice_readableBytes=100
data_readableBytes=101, wrap_readableBytes=100, slice_readableBytes=100
data_ref=1, wrap_ref=1, slice_ref=1
```

参考文献：  
* [Netty ByteBuf](https://netty.io/4.1/api/io/netty/buffer/ByteBuf.html)  
* [Netty Unpooled](https://netty.io/4.1/api/io/netty/buffer/Unpooled.html)  
* [Reference counted objects](https://netty.io/wiki/reference-counted-objects.html)  
* [Netty Unpooled 内存分配](https://blog.csdn.net/everyok/article/details/84948822)  