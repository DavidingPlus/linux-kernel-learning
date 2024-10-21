#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>


MODULE_VERSION("1.0.0");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("DavidingPlus");
MODULE_DESCRIPTION("A Simple ChrDev Module");


static int chrdev_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "driver chrdev open.\n");


    return 0;
}

static int chrdev_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "driver chrdev release.\n");


    return 0;
}


struct file_operations chrdev_ops = {
    .owner = THIS_MODULE,
    .open = chrdev_open,
    .release = chrdev_release,
};


#define DEV_COUNT 1


dev_t devNumber = 0;

struct cdev chrdev;


static int __init chrdev_init(void)
{
    int res = alloc_chrdev_region(&devNumber, 0, DEV_COUNT, "chrdev");

    if (res < 0)
    {
        printk(KERN_ALERT "register_chrdev_region() failed.\n");


        return res;
    }


    cdev_init(&chrdev, &chrdev_ops);

    res = cdev_add(&chrdev, devNumber, DEV_COUNT);
    if (res < 0)
    {
        printk(KERN_ALERT "cdev_add() failed.\n");


        return res;
    }


    printk(KERN_INFO "chrdev init!\n");


    return 0;
}

static void __exit chrdev_exit(void)
{
    cdev_del(&chrdev);

    unregister_chrdev_region(devNumber, DEV_COUNT);


    printk(KERN_INFO "chrdev exit!\n");
}


module_init(chrdev_init);
module_exit(chrdev_exit);
