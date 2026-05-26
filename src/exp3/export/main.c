#include <linux/init.h>
#include <linux/module.h>

#include "calc.h"


MODULE_VERSION("1.0.0");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("DavidingPlus");
MODULE_DESCRIPTION("A Simple Kernel Module To Export Arithmetic Operations");


static int __init exp3_export_init(void)
{
    printk(KERN_INFO "exp3_export: module loaded\n");

    return 0;
}

static void __exit exp3_export_exit(void)
{
    printk(KERN_INFO "exp3_export: module unloaded\n");
}


module_init(exp3_export_init);
module_exit(exp3_export_exit);
