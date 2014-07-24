---
layout: default
title: learn to write blog
---

##{{page.title}}##
1. learn to cite a image
	<p>markdown code: ![image]({{site.url}}/assets/img/demo.jpg)</p>
	![image]({{site.url}}/assets/img/demo.jpg)

2. learn to highlight code
	* how to config
		- install Python
		- install [easy_install](https://pypi.python.org/pypi/setuptools#windows-7-or-graphical-install)
			+ download ez_setup.py
			+ python ez_setup.py
			+ cd \"D:\Program Files (X86)\Python27\Scripts\"
			+ easy_install pygments
		- generate pygments.css
			+ cd \"D:\Program Files (X86)\Python27\Scripts\"
			+ pygmentize -S default fruity -f html > pygments.css
		- add pygments.css to html
	* demo
{% highlight ruby linenos%}
def show
	@widget = Widget(params[:id])
	respond_to do |format|
		format.html # show.html.erb
		format.json { render json: @widget }
	end
end
{% endhighlight %}

{% highlight C %}
int s = 0;
for (int i=1; i<10; ++i)
	s += 1;
printf("s = %d\n", s);
{% endhighlight %}
