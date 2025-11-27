# get_pid_kmod/Makefile
# 目标模块名：get_pid_kmod.ko
obj-m := get_pid_kmod.o

# KDIR 指向当前运行内核的头文件目录
KDIR := $(HOME)/Github/kernel_headers/5.4.0-150/linux-headers-5.4.0-150-generic

# 当前模块所在目录
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	
