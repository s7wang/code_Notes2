#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("GG GG");
MODULE_DESCRIPTION("A simple Hello World kernel module");
MODULE_VERSION("0.1");

// 模块初始化函数
static int __init hello_init(void) {
    printk(KERN_INFO "Hello, world! Module loaded.\n");
    return 0;
}

// 模块卸载函数
static void __exit hello_exit(void) {
    printk(KERN_INFO "Goodbye, world! Module unloaded.\n");
}

module_init(hello_init);
module_exit(hello_exit);
