#include <linux/init.h>
#include <linux/module.h>


MODULE_VERSION("1.0.0");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("DavidingPlus");
MODULE_DESCRIPTION("A Simple Hello World Module");


int add(int a, int b);


static int __init hello_init(void)
{
    printk(KERN_INFO "Hello World: %d\n", add(1, 2));


    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_INFO "Goodbye World!\n");
}


module_init(hello_init);
module_exit(hello_exit);