---
layout: post
title: 在win64 matlab下使用gcc和gfortran来编译mex文件
categories: [coding]
modify_date: 2015-09-18 9:00:00 +0800
---

纠结了好几天，最后总算是解决了，这篇文章分两部分，先上干货教程，再记录辛酸调试历程。

## 一、教程步骤

### 1. 环境配置

搭建环境 win8 64bit + Matlab2012b + mingw-w64 + gnumex2.06

* 安装[mingw-64](http://sourceforge.net/projects/mingw-w64/)

	windows 64位的需要安装mingw-64，不要安装32位的[mingw](http://sourceforge.net/projects/mingw/)，再修改对应环境变量。

* 安装[gnumex](http://sourceforge.net/projects/gnumex)
* 运行gnumex
	
	Matlab下运行gnumex2.06\trunk\gnumex.m
	
	直接运行会出错，需要修改gnumex.m的一些代码：
	
	* gnumex.m没有处理"D:\Program Files\"中间的空格，运行exe时报错，需要修改相应代码，添加双引号
	
		"D:\Program Files\MinGW\mingw32\bin\nm.exe"
	
	* 修改dllcmd，把gfortran的dllcmd设置成与C的一样
		
		1035行改为 `1if pps.lang == C || pps.lang == GFORTRAN`

	* gnumex.m运行后会在gnumex的目录1生成def文件和matlab文件，以及在matlab的目录2生成mexopts.bat mex的配置文件

		目录1 C:\Users\huanglei\AppData\Roaming\MathWorks\MATLAB\R2012b\gnumex		

		目录2 C:\Users\huanglei\AppData\Roaming\MathWorks\MATLAB\R2012b\

		C/C++和gfortran生成的mexopts.bat都需要修改，都没有处理"D:\Program Files\"中间的空格，另外gfortran的还需要添加fintrf.h的头文件目录
		-I "D:\Program Files\MATLAB\MATLAB Production Server\R2012b\extern\include"
		
目前完成环境配置，在matlab里输出mex -setup，已经可以看到gcc的编译器。

### 2. mex文件的编写

C/C++ mex文件编写就不赘述了，这里主要讲一讲fortran mex文件的编写。
这部分需要懂一些fortran编程皮毛以及matlab mex文件编程，

* fortran编程

	缩进坑人，新手常犯错误，记住是6个空格，因为fortran的设计与机器硬件密切相关。
	
	matlab下fortran mex教程 http://wenku.baidu.com/view/ad9a7c60caaedd3383c4d31a.html

* matlab fortran mex编程

	需要添加头文件"fintrf.h"
	
	文件后缀坑人，后缀需要大写**.F**，mex的时候在根据该头文件宏定义进行预处理，.F file needs to be preprocessed to generate .for equivalent

	因为gfrotran都是-fcase-lower，需要从**mexinterface_c.f90**来处理，路径为gnumex2.06\trunk\examples\gfortran\mexinterface_c.f90

给出print.F90的测试代码（主要要从mexinterface_c.f90生成mexinterface模块）：

{% highlight fortran %}
#include "fintrf.h"
      subroutine mexfunction(nlhs,plhs,nrhs,prhs)
      use mexinterface
	  implicit none
      mwPointer plhs(*), prhs(*)
      integer nlhs, nrhs
	  
      call mexPrintf('Hello, world!')
      return
      end
{% endhighlight%}

mex成功后生成print.mexw64，matlab调用print输出`Hello world!`。

## 二、调试记录
	

### 1. gnumex.m的运行

gnumex.m 代码没有处理"D:\Program Files\"中间的空格，运行exe时报错，需要修改相应代码，添加双引号

"D:\Program Files\MinGW\mingw32\bin\nm.exe"

### 2. fortran mex文件的编写

matlab下fortran mex教程 http://wenku.baidu.com/view/ad9a7c60caaedd3383c4d31a.html

fortran教程 缩进坑人

`Error: Non-numeric character in statement label at (1)`

http://wenku.baidu.com/link?url=LDC4abrxr12C7DwDnoMg9wH-2-82TKHZRMngXISddgKAq3rNv-YD01r_oJK211NtZ_UfYB5MlRpxevkl4elowG2UfVovbWOfnMdQEUk-NSO

头文件"fintrf.h" 后缀坑人

在linux下必须把fortran文件后缀改为.F，mex的时候在根据该头文件宏定义进行预处理，.F file needs to be preprocessed to generate .for equivalent

### 3. mingw—w64版本问题

"D:\Program Files\MinGW\bin\nm.exe" 从matlab库文件转换，需要mingw_w64的nm.exe，我的是老版本的mingw_w32!!!

gnumex.m 815行 `[err,list] = dos([ nmcmd    ' -g --defined-only "' libdir lib '.lib"']);`
运行不报错，但是list中有提示信息：

`D:\Program Files\MinGW\bin\nm.exe: libeng.dll: File format not recognized`

导致C:\Users\huanglei\AppData\Roaming\MathWorks\MATLAB\R2012b\gnumex路径下没有生成有效文件，小文件，没有有效内容

http://sourceforge.net/p/gnumex/mailman/message/31464454/

> My first guess is that the linking issue will be due to the fortran 
libraries lflibmx, lflibmex and lflibmat not being created correctly 
(gnumex must convert these from the libraries supplied by Matlab). This 
is done using the program nm.exe which is supplied as part of the 
MinGW-w64 toolchain. The process is to use nm.exe to first create .def 
files which are text files containing symbols from the library files, 
these are then used to convert the libraries. If you are interested 
these libraries are created around lines

http://sourceforge.net/p/gnumex/mailman/message/28916349/

> I seem to remember creating these with the
nm.exe tool from Mingw_w64 and had to make sure that it was the 64-bit
version and not the 32-bit version of that command which was being called.

重装好mingw_w64，**修改环境变量**，期待着美好的事情发生。

### 4. 链接错误

写个简单的测试代码输出Hello world!，在Linux下mex成功，换windows输入
`mex -v print.F90`

提示链接错误

{% highlight bat %}
C:\Users\huanglei\AppData\Local\Temp\mex_S3JZZj\print.obj:print.F90:(.text+0x20): undefined reference to `mexprintf' 
collect2.exe: error: ld returned 1 exit status 
D:\PROGRAM FILES\MATLAB\MATLAB PRODUCTION SERVER\R2012B\BIN\MEX.PL: Error: Link of 'print.F90.mexw64' failed.
{% endhighlight %}

换matlab自带的测试fortran的mex代码, `mexlockf.F`，Linux上mex运行正常，但换windows依然一堆`undefined reference to` T_T

各种Google，标签页不知道打开了多少，但依然没有找到问题，最后突然想到应该去看看gnumex的官方文档啊！！！耐着性子读下去，发现：

http://gnumex.sourceforge.net/documentation.html#L208

> Case Options and Trailing Underscores
> In contrast gfortran does not offer the -fcase switches, and in fact defaults to the behaviour of -fcase-lower. To circumvent the problem that this causes one can use BIND(C,NAME...) clauses in interface blocks for the mx and mex functions, e.g. BIND(C,NAME='MXGETPR') (the mx and mex functions are probably written in C anyway). The demonstration programs give more details.

gfortran默认的都是小写，并且改不了，猛然醒悟，看看之前的提示信息，`mexprintf`小写，对比libmex.def文件只有`MEXPRINTF`和`mexPrintf`所以找不到而导致链接错误，终于要拨云见雾了。

继续看官方文档，给出了解决方案，**use BIND(C,NAME...) clauses in interface blocks for the mx and mex functions, e.g. BIND(C,NAME='MXGETPR') **，并且提供了**mexinterface_c.f90**来处理，并在gnumex2.06\trunk\examples\gfortran目录下提供了示例。

>  mexinterface_c.f90 binds them to the corresponding C-functions (with mixed case names)

修改print.F90，重新mex -v print.F90，看到了希望，结果再次提示

{% highlight bat %}
C:\Users\huanglei\AppData\Local\Temp\mex_GceEL0\print.obj:print.F90:(.text+0x8): undefined reference to `mexPrintf'
collect2.exe: error: ld returned 1 exit status 
link command: gfortran -shared C:\Users\huanglei\AppData\Roaming\MathWorks\MATLAB\R2012b\gnumex\gfortmex.def -o print.mexw64 -LC:\Users\huanglei\AppData\Roaming\MathWorks\MATLAB\R2012b\gnumex -s C:\Users\huanglei\AppData\Local\Temp\mex_GceEL0\print.obj -lflibmx -lflibmex -lflibmat 
D:\PROGRAM FILES\MATLAB\MATLAB PRODUCTION SERVER\R2012B\BIN\MEX.PL: Error: Link of 'print.mexw64' failed.
{% endhighlight %}
  
现在好了，提示的是**mexPrintf**，有大小写了。。。看看链接命令和参数也没问题啊，但为啥还是链接失败？？？

### 5. dlltool生成lib文件

现在确定是gnumex路径下生成的def文件和lib文件的出问题，跑去调试跟踪生成gnumex路径下的def文件和lib也没发现问题。

但注意到了链接时使用的是**-lflibmx -lflibmex -lflibmat**，而先前mex gcc C/C++时成功时是**-llibmx -llibmex -llibmat**，生成.lib文件名就相差了一个字母f，但是mex gcc时就成功了。此时就病急乱投医了，先用gnumex生成lib文件，再重新生成gfortran的mexopts.bat，再修改`D:\program files`的路径问题和头文件包含问题，再把**-lflibmx -lflibmex -lflibmat**修改成**-llibmx -llibmex -llibmat**使用gnumex C/C++生成的lib文件。

重新mex -v print.F90，结果就稀里糊涂的成功了。

初看了下gnumex生成lib文件的代码，C/C++和gfortran就文件名不同，怎么会差别这么大呢。

{% highlight matlab %}
if checkMatlabMinVersion('7')
	[pa,fn,ext]=fileparts(defs2convert{i});
	if pps.lang ~= C, fn = ['f' fn];
end
{% endhighlight %}

继续研究gnumex代码，发现在生成gnumex目录下的lib文件（libeng.lib，libmat.lib，libmex.lib，libmx.lib）时，使用了不同的工具，针对C/C++使用的是**minw64的dlltool**，针对fortran使用的是**gnumex的mexdlltool**，这应该才是症结所在。

{% highlight matlab %}
if pps.lang == C
	dllcmd = ['"' tools_path '\dlltool"'];
else
	dllcmd = ['"' pps.gnumexpath '\mexdlltool" -E --as ' '"' tools_path '\as.exe"'];
end
{% endhighlight %}

gnumex选择C/C++时生成lib文件的bat文件内容如下：

{% highlight bat %}
@echo off
set PATH=D:\Program Files\mingw-w64\x86_64-5.2.0-posix-seh-rt_v4-rev0\mingw64\bin
"D:\Program Files\mingw-w64\x86_64-5.2.0-posix-seh-rt_v4-rev0\mingw64\bin\dlltool" --def "C:\Users\huanglei\AppData\Roaming\MATHWO~1\MATLAB\R2012b\gnumex\libeng.def" --output-lib "C:\Users\huanglei\AppData\Roaming\MATHWO~1\MATLAB\R2012b\gnumex\libeng.lib"
"D:\Program Files\mingw-w64\x86_64-5.2.0-posix-seh-rt_v4-rev0\mingw64\bin\dlltool" --def "C:\Users\huanglei\AppData\Roaming\MATHWO~1\MATLAB\R2012b\gnumex\libmat.def" --output-lib "C:\Users\huanglei\AppData\Roaming\MATHWO~1\MATLAB\R2012b\gnumex\libmat.lib"
"D:\Program Files\mingw-w64\x86_64-5.2.0-posix-seh-rt_v4-rev0\mingw64\bin\dlltool" --def "C:\Users\huanglei\AppData\Roaming\MATHWO~1\MATLAB\R2012b\gnumex\libmex.def" --output-lib "C:\Users\huanglei\AppData\Roaming\MATHWO~1\MATLAB\R2012b\gnumex\libmex.lib"
"D:\Program Files\mingw-w64\x86_64-5.2.0-posix-seh-rt_v4-rev0\mingw64\bin\dlltool" --def "C:\Users\huanglei\AppData\Roaming\MATHWO~1\MATLAB\R2012b\gnumex\libmx.def" --output-lib "C:\Users\huanglei\AppData\Roaming\MATHWO~1\MATLAB\R2012b\gnumex\libmx.lib"
echo Done.
{% endhighlight %}

gnumex选择gfortran时生成lib文件的bat文件内容如下：

{% highlight bat %}
@echo off
set PATH=D:\Program Files\mingw-w64\x86_64-5.2.0-posix-seh-rt_v4-rev0\mingw64\bin
"D:\program files\mingw-w64\gnumex2.06\trunk\mexdlltool" -E --as "D:\Program Files\mingw-w64\x86_64-5.2.0-posix-seh-rt_v4-rev0\mingw64\bin\as.exe" --def "C:\Users\huanglei\AppData\Roaming\MATHWO~1\MATLAB\R2012b\gnumex\libeng.def" --output-lib "C:\Users\huanglei\AppData\Roaming\MATHWO~1\MATLAB\R2012b\gnumex\flibeng.lib"
"D:\program files\mingw-w64\gnumex2.06\trunk\mexdlltool" -E --as "D:\Program Files\mingw-w64\x86_64-5.2.0-posix-seh-rt_v4-rev0\mingw64\bin\as.exe" --def "C:\Users\huanglei\AppData\Roaming\MATHWO~1\MATLAB\R2012b\gnumex\libmat.def" --output-lib "C:\Users\huanglei\AppData\Roaming\MATHWO~1\MATLAB\R2012b\gnumex\flibmat.lib"
"D:\program files\mingw-w64\gnumex2.06\trunk\mexdlltool" -E --as "D:\Program Files\mingw-w64\x86_64-5.2.0-posix-seh-rt_v4-rev0\mingw64\bin\as.exe" --def "C:\Users\huanglei\AppData\Roaming\MATHWO~1\MATLAB\R2012b\gnumex\libmex.def" --output-lib "C:\Users\huanglei\AppData\Roaming\MATHWO~1\MATLAB\R2012b\gnumex\flibmex.lib"
"D:\program files\mingw-w64\gnumex2.06\trunk\mexdlltool" -E --as "D:\Program Files\mingw-w64\x86_64-5.2.0-posix-seh-rt_v4-rev0\mingw64\bin\as.exe" --def "C:\Users\huanglei\AppData\Roaming\MATHWO~1\MATLAB\R2012b\gnumex\libmx.def" --output-lib "C:\Users\huanglei\AppData\Roaming\MATHWO~1\MATLAB\R2012b\gnumex\flibmx.lib"
echo Done.
{% endhighlight %}

因为**dlltool**和**mexdlltool**内部实现细节的不同，导致了生成的lib文件内容和大小存在差异，而坑爹的**mexdlltool**生成的lib不能用。所以应该修改代码：

{% highlight matlab %}
if pps.lang == C || pps.lang == GFORTRAN
	dllcmd = ['"' tools_path '\dlltool"'];
else
	dllcmd = ['"' pps.gnumexpath '\mexdlltool" -E --as ' '"' tools_path '\as.exe"'];
end
{% endhighlight %}

### 6. gfortmex.def入口点修改

此时已经编译链接通过，但不知道使用**dlltool**而不是**mexdlltool**导出lib文件是否存在隐患。
在matlab下尝试运行print，期待着美好的"Hello world!"，结果再次拍醒

{% highlight bat %}
>> print
Mex file entry point is missing.  Please check the (case-sensitive) 
spelling of mexFunction (for C MEX-files), or the (case-insensitive) 
spelling of MEXFUNCTION (for FORTRAN MEX-files).
Invalid MEX-file 'C:\Users\huanglei\Desktop\composite_quantization\lbfgs_um\print.mexw64': 找不到指定的模块。
{% endhighlight %}

提示找不到入口点，说fortran的是MEXFUNCTION，记得先前疯狂Google时看到过类似情况，直接修改gnumex生成的**gfortmex.def**

{% highlight bat %}
EXPORTS
_MEXFUNCTION@16=mexfunction
{% endhighlight %}

改写为：

{% highlight bat %}
EXPORTS
MEXFUNCTION=mexfunction
{% endhighlight %}

重新mex -v print.F90，再次输入print

`Hello world!`

已过凌晨，泪流满面 T_T

## 三、总结心得

搭建环境估计纠结了2天，各种问题，各种Google，配置调试，要耐着性子，一步一步去挖，却忘了一开始应该去阅读官方文档！！！

路漫漫其修远兮，吾将上下而求索~~
