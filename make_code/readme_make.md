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
