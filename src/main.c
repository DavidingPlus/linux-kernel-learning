#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#include "file.h"


MODULE_VERSION("1.0.0");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("DavidingPlus");
MODULE_DESCRIPTION("A Simple ChrDev Module");


extern struct file_operations chrdev_fops;
extern dev_t devNumber;
extern int devCount;
extern struct cdev *cdev;
extern const char *devName;


static int __init chrdev_init(void)
{
    int res = alloc_chrdev_region(&devNumber, 0, devCount, devName);

    if (res < 0)
    {
        printk(KERN_ALERT "chrdev: register_chrdev_region() failed.\n");


        return res;
    }

    cdev = cdev_alloc();
    if (!cdev)
    {
        printk(KERN_ALERT "chrdev: cdev_alloc() failed.\n");


        return -EFAULT;
    }

    cdev_init(cdev, &chrdev_fops);

    res = cdev_add(cdev, devNumber, devCount);
    if (res < 0)
    {
        printk(KERN_ALERT "chrdev: cdev_add() failed.\n");


        return res;
    }


    printk(KERN_INFO "chrdev: chrdev init!\n");


    return 0;
}

static void __exit chrdev_exit(void)
{
    cdev_del(cdev);

    unregister_chrdev_region(devNumber, devCount);


    printk(KERN_INFO "chrdev: chrdev exit!\n");
}


module_init(chrdev_init);
module_exit(chrdev_exit);
