#include "main.h"

#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#include "fops.h"


MODULE_VERSION("1.0.0");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("DavidingPlus");
MODULE_DESCRIPTION("A Simple GlobalMem Module");


struct file_operations globalmem_fops = {
    .owner = THIS_MODULE,
    .open = globalmem_open,
    .release = globalmem_release,
    .write = globalmem_write,
    .read = globalmem_read,
};

struct globalmem_dev_t globalmem_dev = {
    .cdev = NULL,
    .devNumber = 0,
    .devCount = 1,
    .devName = "globalmem",
};


static int __init globalmem_init(void)
{
    int res = alloc_chrdev_region(&globalmem_dev.devNumber, 0, globalmem_dev.devCount, globalmem_dev.devName);

    if (res < 0)
    {
        printk(KERN_ALERT "globalmem: register_globalmem_region() failed.\n");


        return res;
    }

    globalmem_dev.cdev = cdev_alloc();
    if (!globalmem_dev.cdev)
    {
        printk(KERN_ALERT "globalmem: cdev_alloc() failed.\n");


        return -EFAULT;
    }

    cdev_init(globalmem_dev.cdev, &globalmem_fops);

    res = cdev_add(globalmem_dev.cdev, globalmem_dev.devNumber, globalmem_dev.devCount);
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
    cdev_del(globalmem_dev.cdev);

    unregister_chrdev_region(globalmem_dev.devNumber, globalmem_dev.devCount);


    printk(KERN_INFO "globalmem: globalmem exit!\n");
}


module_init(globalmem_init);
module_exit(globalmem_exit);
