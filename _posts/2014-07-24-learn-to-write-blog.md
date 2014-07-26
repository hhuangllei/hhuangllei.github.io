---
layout: default
title: learn to write blog
---

##{{page.title}}##
* learn to cite a image
<p>markdown code: ![image]({{site.url}}/assets/img/demo.jpg)</p>
![image]({{site.url}}/assets/img/demo.jpg)

* learn to highlight code
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

* learn to use Post URL
<p>{% post_url 2014-07-23-hello-world %}</p>
