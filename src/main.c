#include <linux/init.h>
#include <linux/module.h>

#include "calc.h"


MODULE_VERSION("1.0.0");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("DavidingPlus");
MODULE_DESCRIPTION("A Simple Hello World Module");


// extern 关键字用在变量上，表示仅作声明，变量的定义来自其他源文件。
extern int helloInitData __initdata;
extern const char *helloExitData __exitdata;
extern char *helloInitParam;
extern int helloExitParam[2];
extern int helloExitParamSize;


static int __init hello_init(void)
{
    printk(KERN_INFO "hello: Hello World %d %d %s\n", add(1, 2), helloInitData, helloInitParam);


    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_INFO "hello: Goodbye World %d %s %d %d\n", sub(2, 3), helloExitData, helloExitParam[0], helloExitParam[1]);
}


module_init(hello_init);
module_exit(hello_exit);
