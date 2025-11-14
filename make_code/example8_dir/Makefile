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