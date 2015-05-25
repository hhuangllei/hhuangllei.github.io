---
layout: post
title: windows下使用openmp编译并行matlab版本的libsvm
categories: [coding]
---

最近使用matlab版本的libsvm进行实验，发现当训练样本稍微多一些，svmtrain和svmpredict的时间过长，拖慢了实验进度，因此就去找关于libsvm的并行解决方法。

实际在libsvm官方的[FAQ](http://www.csie.ntu.edu.tw/~cjlin/libsvm/faq.html)中，就有说明，可以使用[openmp](http://zh.wikipedia.org/wiki/OpenMP)来进行并行训练训练预测，只需要参照[官方说明](http://www.csie.ntu.edu.tw/~cjlin/libsvm/faq.html#f432)在svm.cpp文件的相应位置加上openmp的编译指示`#pragma omp parallel for private(j)`等语句，再重新编译即可。

但实际上，我在编译这上面还是折腾了一会儿，主要原因还是使用VS习惯了，对编译参数不熟悉。使用openmp编译是要修改参数，当时我参照[官方说明](http://www.csie.ntu.edu.tw/~cjlin/libsvm/faq.html#f8032)，修改make.m文件，如

`mex CFLAGS="\$CFLAGS -std=c99 -fopenmp" -lgomp  -largeArrayDims libsvmread.c`

此时提示找不到gomp.lib这个库文件。我又跑去网上搜“matlab mex openmp”，网上一般都是使用

`CFLAGS="\$CFLAGS -fopenmp" LDFLAGS="\$LDFLAGS -fopenmp"`

加入这个编译参数后，重新编译得到mexw64文件(在windows服器上使用)，但用来训练预测并没有实现并行。。。

突然发现，`CFLAGS LDFLAGS`好像都是Linux下编译时使用的编译参数啊（使用matlab的大神都是在Linux下使用的啊。。。），原来折腾大半天原来在windows上照着Linux的编译啊。。。

我的运行环境是windows，matlab2012b，mex使用编译器是Microsoft Visual C++ 2010。知道问题所在，解决起来就很快了，就是编译参数的问题，修改make.m文件，在mex编译语句中加入`COMPFLAGS="$COMPFLAGS /openmp"`，重新编译，测试运行，成功并行^_^

在正样本1000，负样本1000，特征维度1000的训练集上，训练速度测试如下所示：

<table width="300" border="1" bordercolor="black" cellspacing="1">
<tr>
<td> </td>
<td>时间(s)</td>
</tr>
<tr>
<td>并行svm</td>
<td>6.65</td>
</tr>
<tr>
<td>非并行svm</td>
<td>35.96</td>
</tr>
</table>

使用上述条件下训练出来的模型来进行预测，测试集3w，预测速度测试如下所示：

<table width="300" border="1" bordercolor="black" cellspacing="1">
<tr>
<td> </td>
<td>时间(s)</td>
</tr>
<tr>
<td>并行svm</td>
<td>9.77</td>
</tr>
<tr>
<td>非并行svm</td>
<td>109.28</td>
</tr>
</table>

进行实验的机器是一台24核的服务器，但发现24核并行的libsvm并没有提速24倍，连12倍都没有，我认为这主要是按照官方文档使用openmp来进行并行的代码部分有限，并没有充分开发出并行的效果，所以提升有效。但是，当看到有几倍速度的提升时，已经感觉够用了，不想再继续折腾下去，毕竟openmp只是看了下入门。
