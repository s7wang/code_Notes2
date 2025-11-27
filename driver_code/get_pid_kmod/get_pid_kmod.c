#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>  // 包含 task_struct 和 current

MODULE_LICENSE("GPL");
MODULE_AUTHOR("GG GG");
MODULE_DESCRIPTION("Kernel module to print current process information");
MODULE_VERSION("0.1");

static int __init get_pid_kmod_init(void)
{
    printk(KERN_INFO "The process is \"%s\" (pid %i)\n", current->comm, current->pid);
    return 0;
}

static void __exit get_pid_kmod_exit(void)
{
    printk(KERN_INFO "Goodbye from get_pid_kmod\n");
}

module_init(get_pid_kmod_init);
module_exit(get_pid_kmod_exit);
