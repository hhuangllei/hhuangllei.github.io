---
layout: post
title: 杨氏矩阵的查找
modify_date: 2015-04-06 23:00:00
---

杨氏矩阵（Young tableau），每行元素是递增的，每列元素也是递增的。即`a[i][j]<a[i+1][j] && a[i][j]<a[i][j+1]`。

杨氏矩阵的填写，勾长公式

杨氏矩阵的查找，记该矩阵`m * n`，两种方法：左下角到右上角查找`O(m+n)`，四分矩阵查找`O(n^lg3)`

要在这样的矩阵中查找某个数值元素的位置，复杂度可以达到o(m+n)，其中n为矩阵行长度，m为矩阵列长度。

参考文献：

* http://en.wikipedia.org/wiki/Young_tableau
* http://articles.leetcode.com/2010/10/searching-2d-sorted-matrix-part-ii.html
* http://blog.csdn.net/sgbfblog/article/details/7745450
* http://blog.csdn.net/acdreamers/article/details/14549077

