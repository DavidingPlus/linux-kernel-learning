#include <linux/init.h>
#include <linux/module.h>


MODULE_VERSION("1.0.0");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("DavidingPlus");
MODULE_DESCRIPTION("A Simple Hello World Module");


char *helloInitParam = "gee";
module_param(helloInitParam, charp, S_IRUGO);


static int __init hello_init(void)
{
    printk(KERN_INFO "hello: Hello World %s\n", helloInitParam);


    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_INFO "hello: Goodbye World\n");
}


module_init(hello_init);
module_exit(hello_exit);
