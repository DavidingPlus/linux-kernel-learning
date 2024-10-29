#include <linux/init.h>
#include <linux/module.h>

#include "calc.h"


MODULE_VERSION("1.0.0");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("DavidingPlus");
MODULE_DESCRIPTION("A Simple Hello World Module");


static int helloInitData __initdata = -114514;

static const char *helloExitData __exitdata = "abandon";


static int __init hello_init(void)
{
    printk(KERN_INFO "hello: Hello World %d %d\n", add(1, 2), helloInitData);


    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_INFO "hello: Goodbye World %d %s\n", sub(2, 3), helloExitData);
}


module_init(hello_init);
module_exit(hello_exit);
