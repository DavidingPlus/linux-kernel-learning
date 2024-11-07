#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#include "file.h"


MODULE_VERSION("1.0.0");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("DavidingPlus");
MODULE_DESCRIPTION("A Simple GlobalMem Module");


extern struct file_operations globalmem_fops;
extern dev_t devNumber;
extern int devCount;
extern struct cdev *cdev;
extern const char *devName;


static int __init globalmem_init(void)
{
    int res = alloc_chrdev_region(&devNumber, 0, devCount, devName);

    if (res < 0)
    {
        printk(KERN_ALERT "globalmem: register_globalmem_region() failed.\n");


        return res;
    }

    cdev = cdev_alloc();
    if (!cdev)
    {
        printk(KERN_ALERT "globalmem: cdev_alloc() failed.\n");


        return -EFAULT;
    }

    cdev_init(cdev, &globalmem_fops);

    res = cdev_add(cdev, devNumber, devCount);
    if (res < 0)
    {
        printk(KERN_ALERT "globalmem: cdev_add() failed.\n");


        return res;
    }


    printk(KERN_INFO "globalmem: globalmem init!\n");


    return 0;
}

static void __exit globalmem_exit(void)
{
    cdev_del(cdev);

    unregister_chrdev_region(devNumber, devCount);


    printk(KERN_INFO "globalmem: globalmem exit!\n");
}


module_init(globalmem_init);
module_exit(globalmem_exit);
