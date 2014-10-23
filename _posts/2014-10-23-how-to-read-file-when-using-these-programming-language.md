---
layout: post
title: 使用不同编程语言读取文件
---

在编程中，读取文件是很频繁很常规的操作，关于不同的编程语言，文件操作略有不同，有时一种语言较长时间没用，当再捡起使用时就可能忘记如何进行文件操作，所以在此总结记录下不同编程语言读取文件的操作，供以后查阅。

* C

	关于C的文件操作，主要是涉及C的读写函数，如`fopen fgetc  fputc fgets fputs fseek fclose`等。下面给出按行读取文件的代码示例：
{% highlight C++ %}
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main()
{
	char filename[] = "test.txt";
	
	FILE *fin;
	char buf[512];
	if ((fin = fopen(filename, "r")) == NULL)
	{
		printf("Error: open file failed.\n");
		return -1;
	}

	while (!feof(fin))
	{
		fgets(buf, 512, fin);
		printf(buf);
	}
	fclose(fin);

	system("pause");

	return 0;
}
{% endhighlight %}
  
* C++
  
	关于C++的文件操作，主要是涉及到`fstream`中的`ifstream`和`ofstream`。下面给出按行读取文件的代码示例：
{% highlight C++ %}
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	string filename = "test.txt";

	try
	{
		ifstream fin(filename);
		string line = "";
		while (!fin.eof())
		{
			getline(fin, line);
			cout << line << endl;
		}
		fin.close();
	}
	catch (exception &e)
	{
		cerr << e.what() << endl;
	}

	system("pause");
	return 0;
}
{% endhighlight %}

* C#

	关于C#的文件操作，主要是涉及到`System.IO`中的`StreamReader`和`StreamWriter`。下面给出按行读取文件的代码示例：
{% highlight C# %}
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Test
{
    class Program
    {
        static void Main(string[] args)
        {            
            string filename = @"test.txt";            
           
            try
            {
                StreamReader sr = new StreamReader(filename);
                string line = "";

                while (!sr.EndOfStream)
                {
                    line = sr.ReadLine();
                    Console.WriteLine(line);
                }

                sr.Close();
            }
            catch (IOException e)
            {
                Console.WriteLine(e.ToString());
            }                        
        }
    }
}
{% endhighlight %}

* Java

	关于Java的文件操作，主要是涉及到`java.io`中的`FileReader FileWriter BufferedReader BufferedWriter`。下面给出按行读取和写入文件的代码示例：
{% highlight Java %}
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
 
public class JavaFile {
    public static void main(String[] args) {
        try {
            // read file content from file
            StringBuffer sb= new StringBuffer("");
			
            FileReader reader = new FileReader("D://test.txt");
            BufferedReader br = new BufferedReader(reader);
            String str = null;
           
            while((str = br.readLine()) != null) {
                sb.append(str+"/n"); 
                System.out.println(str);
            }
           
            br.close();
            reader.close();
			
            // write string to file
            FileWriter writer = new FileWriter("c://test2.txt");
            BufferedWriter bw = new BufferedWriter(writer);
            bw.write(sb.toString());
			
            bw.close();
            writer.close();
        }
        catch(FileNotFoundException e) {
            e.printStackTrace();
        }
        catch(IOException e) {
            e.printStackTrace();
        }
    }
}
{% endhighlight %}
	
* Python

	关于Python的文件操作，是很便捷的，主要是使用`open`函数打开文件，后续使用`for`循环读取文件内容即可。下面给出按行读取文件的代码示例：
{% highlight Python %}
# -*- coding: utf8 -*-

def main():
    filename = "D:\\test.txt"

    try:
        inFile = open(filename, "r")
    except IOError:
        print "Error: open file failed"        
    else:
        for line in inFile:            
            print line
    finally:
        inFile.close()

if __name__ == "__main__":
    main()
{% endhighlight %}

* Matlab

	关于Matlab的文件操作，和C的读写函数类似，主要是涉及`fopen fgetl fgets fputs fread fwrite fseek fclose`等。下面给出按行读取文件的代码示例：
{% highlight Matlab %}
filename = 'test.txt';

fid = fopen(filename, 'r');
while ~feof(fid)
    line = fgetl(fid);
    fprintf('%s\n', line);
end
fclose(fid);
{% endhighlight %}