#include <linux/init.h>
#include <linux/module.h>


MODULE_VERSION("1.0.0");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("DavidingPlus");
MODULE_DESCRIPTION("A Simple ChrDev Module");


static int __init chrdev_init(void)
{
    printk(KERN_INFO "ChrDev Init!\n");


    return 0;
}

static void __exit chrdev_exit(void)
{
    printk(KERN_INFO "ChrDev Exit!\n");
}


module_init(chrdev_init);
module_exit(chrdev_exit);
