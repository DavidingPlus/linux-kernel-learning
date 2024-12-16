#include <linux/init.h>
#include <linux/module.h>


MODULE_VERSION("1.0.0");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("DavidingPlus");
MODULE_DESCRIPTION("A Simple Blkdev Module");


static int __init blkdev_init(void)
{
    printk(KERN_INFO "blkdev: blkdev init!\n");


    return 0;
}

static void __exit blkdev_exit(void)
{
    printk(KERN_INFO "blkdev: blkdev exit!\n");
}


module_init(blkdev_init);
module_exit(blkdev_exit);
