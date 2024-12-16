#include <linux/init.h>
#include <linux/module.h>
#include <linux/genhd.h>


MODULE_VERSION("1.0.0");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("DavidingPlus");
MODULE_DESCRIPTION("A Simple Blkdev Module");


static int __init blkdev_init(void)
{
    int major = register_blkdev(0, "blkdev");
    if (major < 0)
    {
        printk(KERN_ALERT "blkdev: register_blkdev() failed.\n");


        return -EFAULT;
    }

    printk(KERN_INFO "blkdev: blkdev init!\n");


    return 0;
}

static void __exit blkdev_exit(void)
{
    unregister_blkdev(0, "blkdev");

    printk(KERN_INFO "blkdev: blkdev exit!\n");
}


module_init(blkdev_init);
module_exit(blkdev_exit);
