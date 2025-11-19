CC = gcc
TARGET = example17
SOURCES = main.c foo.c bar.c
OBJS := $(SOURCES:.c=.o)
DEPS := $(SOURCES:.c=.d)

.PHONY: all clean

# 默认目标
all: $(TARGET)

# 链接生成可执行文件
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

# 所有 .o 文件默认使用 -O
%.o: %.c %.d
	$(CC) $(CFLAGS) -c $< -o $@

# 对 foo.o 强制使用 -g（调试模式）
foo.o: override CFLAGS = -g

# 生成依赖文件
%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
	sed -E "s|^([^:]+):|\1 $@ :|" < $@.$$$$ > $@; \
	rm -f $@.$$$$; cat $@

# 自动包含依赖文件，如果不存在也不会报错
-include $(DEPS)

# 清理
clean:
	rm -f $(TARGET) $(OBJS) $(DEPS)
