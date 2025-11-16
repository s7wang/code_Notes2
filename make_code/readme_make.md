# readme_make

A description of make_code directory.

## makefile.example1

The basic writing rules for a makefile are to use `make example1` to generate an. o file in the src directory.

~~~makefile
targets : prerequisites
command
...
# 或是这样：
targets : prerequisites ; command
command
...
~~~

## makefile.example2

Example of wildcard usage in makefile.

| 通配符  | 含义                     |
| ------- | ------------------------ |
| `*`     | 匹配任意长度字符（含空） |
| `?`     | 匹配任意单个字符         |
| `[...]` | 匹配字符集内的任意字符   |

## makefile.example3

Search for files in Makefile.

~~~makefile
# 1、为符合模式<pattern>的文件指定搜索目录<directories>。
vpath <pattern> <directories>

# 2、清除符合模式<pattern>的文件的搜索目录。
vpath <pattern>

# 3、清除所有已被设置好了的文件搜索目录。
vpath
~~~

## makefile.example4

Multi objective examples in Makefile rules.

~~~makefile
bigoutput littleoutput : text.g
	generate text.g -$(subst output,,$@) > $@
# 上述规则等价于：
bigoutput : text.g
	generate text.g -big > bigoutput
littleoutput : text.g
	generate text.g -little > littleoutput
~~~

## makefile.example5

Automatic generation of dependencies for Makefile.

~~~(空)
shell$ gcc -Iinclude -MM src/main.c
main.o: src/main.c src/defs.h include/common.h
~~~

## makefile.example6

Compile the project using the generated dependency files in Makefile.

## makefile.example7

Nested use of makefiles.

~~~(空)
.
├── Makefile
├── makefile.example7
└── example7
    ├── Makefile
    ├── example7.c
    ├── example7.h
    └── main.c
~~~

## makefile.example8

Definition of makefile command package use case. （define）

~~~makefile
# example8_dir/Makefile
TARGET = example8_y.c

define run-yacc
	yacc $(firstword $^)
	mv y.tab.c $@
endef

# 目标规则：处理 .y 文件
$(TARGET): %.c: %.y
	$(run-yacc)

clean: 
	rm -rf $(TARGET)

# .y 文件是 Yacc（Yet Another Compiler Compiler）语法文件。
# 它是一种专门用于描述 语法规则（Parser） 的文件格式，用来生成 语法分析器（parser）。
~~~

## makefile.example9

Examples of variables in makefile.

The usage of "=" ":=" "?=".

| 操作需求             | 推荐用法 |
| ---------------- | ---- |
| 内容依赖其他变量，且需动态更新  | `=`  |
| 内容需要立即展开，不希望后面变化 | `:=` |
| 提供默认值，可被命令行覆盖    | `?=` |
| 给变量追加内容          | `+=` |

## makefile.example10

4.2.1 Variable suffix replacement, such as replacing .o with .c

AND

4.2.2 Example of treating variable values as variables again in a makefile.

## makefile.example11

Usage of "override" target variables and multiline variables.

## makefile.example12

Usage of Pattern variable in a makefile.

~~~makefile
%.o : CFLAGS = -O
# 同样，模式变量的语法和“目标变量”一样：
<pattern ...> : <variable-assignment>
<pattern ...> : override <variable-assignment>
~~~

## makefile.example13

The syntax of conditional judgment in Makefile.(ifeq, ifneq, ifdef, ifndef).

## makefile.example14

1. Use case of subst function

~~~makefile
$(subst <from>,<to>,<text>)
~~~

* 名称：字符串替换函数——`subst`。
* 功能：把字串`<text>`中的`<from>`字符串替换成`<to>`。
* 返回：函数返回被替换过后的字符串。
-----------------

2. Use case of patsubst function

~~~makefile
$(patsubst <pattern>,<replacement>,<text>)
~~~

* 名称：模式字符串替换函数——patsubst。
* 功能：查找`<text>`中的单词（单词以“`空格`”、“`Tab`”或“`回车`”、“`换行`”分隔）是否符合模式`<pattern>`，如果匹配的话，则以`<replacement>`替换。这里，`<pattern>`可以包括通配符“`%`”，表示任意长度的字串。如果`<replacement>`中也包含“`%`”，那么，`<replacement>`中的这个“`%`”将是`<pattern>`中的那个“`%`”所代表的字串。（可以用“`\`”来转义，以“`\%`”来表示真实含义的“`%`”字符）。
* 返回：函数返回被替换过后的字符串。
-----------

3. Use case of strip function

~~~makefile
$(strip <string>)
~~~

* 名称：去空格函数——strip。
* 功能：去掉`<string>`字串中开头和结尾的空字符。
* 返回：返回被去掉空格的字符串值。
----------

4. Use case of findstring function

~~~makefile
$(findstring <find>,<in>)
~~~

* 名称：查找字符串函数——findstring。
* 功能：在字串`<in>`中查找`<find>`字串。
* 返回：如果找到，那么返回`<find>`，否则返回空字符串。
----------

5. Use case of filter and filter-out function

~~~makefile
$(filter <pattern...>,<text>)
~~~

* 名称：过滤函数——filter。
* 功能：以`<pattern>`模式过滤`<text>`字符串中的单词，保留符合模式`<pattern>`的单词。可以有多个模式。
* 返回：返回符合模式`<pattern>`的字串。


~~~makefile
$(filter-out <pattern...>,<text>)
~~~

* 名称：反过滤函数——filter-out。
* 功能：以`<pattern>`模式过滤`<text>`字符串中的单词，去除符合模式`<pattern>`的单词。可以有多个模式。
* 返回：返回不符合模式`<pattern>`的字串。
----------

6. Use case of sort function

~~~makefile
$(sort <list>)
~~~

* 名称：排序函数——sort。
* 功能：给字符串`<list>`中的单词排序（升序）。
* 返回：返回排序后的字符串。
----------------

7. Use case of word and wordlist function

~~~makefile
$(word <n>,<text>)
~~~

* 名称：取单词函数——word。
* 功能：取字符串`<text>`中第`<n>`个单词。（从一开始）
* 返回：返回字符串`<text>`中第`<n>`个单词。如果`<n>`比`<text>`中的单词数要大，那么返回空字符串。

~~~makefile
$(wordlist <s>,<e>,<text>)
~~~

* 名称：取单词串函数——wordlist。
* 功能：从字符串`<text>`中取从`<s>`开始到`<e>`的单词串。`<s>`和`<e>`是一个数字。
* 返回：返回字符串`<text>`中从`<s>`到`<e>`的单词字串。如果`<s>`比`<text>`中的单词数要大，那么返回空字符串。如果`<e>`大于`<text>`的单词数，那么返回从`<s>`开始，到`<text>`结束的单词串。
---------------

8. Use case of words and firstword  function

~~~makefile
$(words <text>)
~~~

* 名称：单词个数统计函数——words。
* 功能：统计`<text>`中字符串中的单词个数。
* 返回：返回`<text>`中的单词数。

~~~makefile
$(firstword <text>)
~~~

* 名称：首单词函数——firstword。
* 功能：取字符串`<text>`中的第一个单词。
* 返回：返回字符串`<text>`的第一个单词。
---------

## makefile.example15

Use case for file name operation function in Makefile.

**dir 取目录函数**

~~~makefile
$(dir <names...>)
#示例： 
$(dir src/foo.c hacks) # 返回值是“src/ ./”。
~~~

* 名称：取目录函数——dir。
* 功能：从文件名序列`<names>`中取出目录部分。目录部分是指最后一个反斜杠（“`/`”）之前的部分。如果没有反斜杠，那么返回“`./`”。
* 返回：返回文件名序列`<names>`的目录部分。

-------------------

**notdir 取文件函数**

~~~makefile
$(notdir <names...>)
# 示例： 
$(notdir src/foo.c hacks) # 返回值是“foo.c hacks”。
~~~

* 名称：取文件函数——notdir。
* 功能：从文件名序列`<names>`中取出非目录部分。非目录部分是指最后一个反斜杠（“`/`”）之后的部分。
* 返回：返回文件名序列`<names>`的非目录部分。

-----------------------

**suffix 取后缀函数**

~~~makefile
$(suffix <names...>)
# 示例：
$(suffix src/foo.c src-1.0/bar.c hacks) # 返回值是“.c .c”。
~~~

* 名称：取后缀函数——suffix。
* 功能：从文件名序列`<names>`中取出各个文件名的后缀。
* 返回：返回文件名序列`<names>`的后缀序列，如果文件没有后缀，则返回空字串。

-------------------

**basename 取前缀函数**

~~~makefile
$(basename <names...>)
# 示例：
$(basename src/foo.c src-1.0/bar.c hacks) # 返回值是“src/foo src-1.0/bar hacks”。
~~~

* 名称：取前缀函数——basename。
* 功能：从文件名序列`<names>`中取出各个文件名的前缀部分。
* 返回：返回文件名序列`<names>`的前缀序列，如果文件没有前缀，则返回空字串。

-------------

**addsuffix 加后缀函数**

~~~makefile
$(addsuffix <suffix>,<names...>)
# 示例：
$(addsuffix .c,foo bar) # 返回值是“foo.c bar.c”。
~~~

* 名称：加后缀函数——addsuffix。
* 功能：把后缀`<suffix>`加到`<names>`中的每个单词后面。
* 返回：返回加过后缀的文件名序列。

--------------------

**addprefix 加前缀函数**

~~~makefile
$(addprefix <prefix>,<names...>)
# 示例：
$(addprefix src/,foo bar) # 返回值是“src/foo src/bar”。
~~~

* 名称：加前缀函数——addprefix。
* 功能：把前缀`<prefix>`加到`<names>`中的每个单词前面。
* 返回：返回加过前缀的文件名序列。

-------------

**join 连接函数**

~~~makefile
$(join <list1>,<list2>)
# 示例：
$(join aaa bbb , 111 222 333) # 返回值是“aaa111 bbb222 333”。
~~~

* 名称：连接函数——join。
* 功能：把`<list2>`中的单词对应地加到`<list1>`的单词后面。如果`<list1>`的单词个数要比`<list2>`的多，那么，`<list1>`中的多出来的单词将保持原样。如果`<list2>`的单词个数要比`<list1>`多，那么，`<list2>`多出来的单词将被复制到`<list2>`中。
* 返回：返回连接过后的字符串。

--------------

## makefile.example16

