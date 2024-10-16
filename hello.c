#include <linux/init.h>
#include <linux/module.h>


int hello_init(void)
{
    printk(KERN_INFO "Hello Linux Kernel!\n");


    return 0;
}

void hello_exit(void)
{
    printk(KERN_INFO "Goodbye Linux Kernel!\n");
}


module_init(hello_init);
module_exit(hello_exit);


MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("DavidingPlus");
MODULE_DESCRIPTION("A Simple Hello Linux Kernel Module");
