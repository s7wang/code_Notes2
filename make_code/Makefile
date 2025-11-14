#==========================
# 可扩展 Example Makefile
#==========================

# 定义所有 example 数字
EXAMPLES := 1 2 3 4 5 6 7 8 9 10 11 12

# 声明所有 exampleX 和 exampleX-clean 为伪目标
.PHONY: $(foreach n,$(EXAMPLES),example$(n) example$(n)-clean)

#==========================
# 使用 eval 生成独立规则
#==========================

# 生成 exampleX 规则
$(foreach n,$(EXAMPLES),$(eval example$(n): ; $(MAKE) -f makefile.example$(n)))

# 生成 exampleX-clean 规则
$(foreach n,$(EXAMPLES),$(eval example$(n)-clean: ; $(MAKE) -f makefile.example$(n) clean))

#==========================
# 可选：all 规则，默认执行所有 example
#==========================
.PHONY: all
all: $(foreach n,$(EXAMPLES),example$(n))
