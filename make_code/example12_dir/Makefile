# example12_dir/Makefile
CC = gcc
TARGET = example12
OBJS = main.o foo.o bar.o

# 所有 .o 文件默认使用 -O
%.o : CFLAGS = -O

# 对 foo.o 强制使用 -g（即调试模式），覆盖系统/命令行变量
foo.o : override CFLAGS = -g

# 链接生成可执行文件
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# 编译各个 .c 文件生成 .o
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
