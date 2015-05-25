---
layout: page
title: 我的Blog
---

<div id="category_list">
	<h1>Categories</h1>
	<ul class="posts">
		{% assign categories_list = site.categories %}
		{% for category in categories_list %}
			<li><a href="#{{ category[0] }}-ref">
    		{{ category[0] | join: "/" }} <span>{{ category[1].size }}</span></a>
			</li>
		{% endfor %}
	</ul>
</div>

<div id="home">
	{% for category in categories_list %}	
		<h1 id="{{ category[0] }}-ref">{{ category[0] }}</h1>
		<ul class="posts">
			{% assign pages_list = category[1] %}
			{% for post in pages_list %}
				<li><span>{{ post.date | date_to_string }}</span>&raquo; <a href="{{ site.baseurl }}{{ post.url }}">{{ post.title }}</a></li>
			{% endfor %}			
		</ul>
	{% endfor %}
</div>