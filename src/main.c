#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#include "lfops.h"
#include "lglobal.h"


MODULE_VERSION("1.0.0");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("DavidingPlus");
MODULE_DESCRIPTION("A Simple GlobalMem Module");


extern struct file_operations globalmemFops;
extern struct LGlobalMemDataT globalmemData;


static int __init globalmem_init(void)
{
    int res = alloc_chrdev_region(&globalmemData.m_devNumber, 0, globalmemData.m_devCount, globalmemData.m_devName);

    if (res < 0)
    {
        printk(KERN_ALERT "globalmem: register_globalmem_region() failed.\n");


        return res;
    }

    globalmemData.m_cdev = cdev_alloc();
    if (!globalmemData.m_cdev)
    {
        printk(KERN_ALERT "globalmem: cdev_alloc() failed.\n");


        return -EFAULT;
    }

    cdev_init(globalmemData.m_cdev, &globalmemFops);

    res = cdev_add(globalmemData.m_cdev, globalmemData.m_devNumber, globalmemData.m_devCount);
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
    cdev_del(globalmemData.m_cdev);

    unregister_chrdev_region(globalmemData.m_devNumber, globalmemData.m_devCount);


    printk(KERN_INFO "globalmem: globalmem exit!\n");
}


module_init(globalmem_init);
module_exit(globalmem_exit);
