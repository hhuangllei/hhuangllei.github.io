---
layout: post
title: Java缓冲字节数组
categories: [coding, java]
modify_date: 2018-03-03 22:00:00 +0800
---

java开发常会遇到缓冲字节数组`byte []`，比如分几次拼凑几个字节数组合成一段音频数据。  
上网搜素看到[ByteBuffer](https://docs.oracle.com/javase/7/docs/api/java/nio/ByteBuffer.html)，初用起来也踩了些坑。

## 1. ByteBuffer  
`ByteBuffer`，使用中需要明确buffer中的几个下标：  
`1 <= mark <= position <= limit <=capacity`  
所有的写入操作`put`让`position`递增，而所有的读取操作`get`都是从`position`开始读取。当未重置`position`直接读取，导致读取到非写入数据。

## 2. ByteArrayOutputStream
实际更简单的是使用继承`OutputStream`的[ByteArrayOutputStream](https://docs.oracle.com/javase/7/docs/api/java/io/ByteArrayOutputStream.html),
向输出流写入字节数组数据，然后调用`toByteArray`得到最后合并的字节数据。

## 3. 测试demo

测试demo代码：

``` java
public class Test {
    public static void main(String[] args) throws IOException {
        // test ByteBuffer
        ByteBuffer bb = ByteBuffer.allocate(512);
        System.out.println("position:" + bb.position() + "\t" + "limit:" + bb.limit() + "\t" +
            "capacity:" + bb.capacity() + "\t" + "remaining:" + bb.remaining());

        bb.mark();
        System.out.println("position:" + bb.position() + "\t" + "limit:" + bb.limit() + "\t" +
            "capacity:" + bb.capacity() + "\t" + "remaining:" + bb.remaining());

        bb.put("abc".getBytes());
        System.out.println("position:" + bb.position() + "\t" + "limit:" + bb.limit() + "\t" +
            "capacity:" + bb.capacity() + "\t" + "remaining:" + bb.remaining());
        bb.put("def".getBytes());
        System.out.println("position:" + bb.position() + "\t" + "limit:" + bb.limit() + "\t" +
            "capacity:" + bb.capacity() + "\t" + "remaining:" + bb.remaining());


        bb.reset();
        System.out.println("position:" + bb.position() + "\t" + "limit:" + bb.limit() + "\t" +
            "capacity:" + bb.capacity() + "\t" + "remaining:" + bb.remaining());

        byte [] buffer = new byte[4];
        bb.get(buffer);
        System.out.println(new String(buffer));
        System.out.println("position:" + bb.position() + "\t" + "limit:" + bb.limit() + "\t" +
            "capacity:" + bb.capacity() + "\t" + "remaining:" + bb.remaining());

        // test ByteArrayOutputStream
        ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
        System.out.println("size: " + outputStream.size());

        outputStream.write("abc".getBytes());
        System.out.println("size: " + outputStream.size());
        outputStream.write("def".getBytes());
        System.out.println("size: " + outputStream.size());

        System.out.println(new String(outputStream.toByteArray()));
        System.out.println("size: " + outputStream.size());
        outputStream.close();

    }
}
```

结果输出：  

``` bash
position:0	limit:512	capacity:512	remaining:512
position:0	limit:512	capacity:512	remaining:512
position:3	limit:512	capacity:512	remaining:509
position:6	limit:512	capacity:512	remaining:506
position:0	limit:512	capacity:512	remaining:512
abcd
position:4	limit:512	capacity:512	remaining:508
size: 0
size: 3
size: 6
abcdef
size: 6
size: 6
```

参考文献：  
* [Java NIO ByteBuffer详解](http://donald-draper.iteye.com/blog/2357084)  
* [Gets byte array from a ByteBuffer in java](https://stackoverflow.com/questions/679298/gets-byte-array-from-a-bytebuffer-in-java)  