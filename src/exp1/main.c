#include <linux/init.h>
#include <linux/module.h>
#include <linux/list.h>

#include "list.h"


MODULE_VERSION("1.0.0");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("DavidingPlus");
MODULE_DESCRIPTION("A Simple Hello World Module");


char *helloInitParam = "gee";
module_param(helloInitParam, charp, S_IRUGO);

static LIST_HEAD(HelloListNodeHead);


static int __init hello_init(void)
{
    printk(KERN_INFO "hello: Hello World %s\n", helloInitParam);

    addListNode(&HelloListNodeHead, 1);
    addListNode(&HelloListNodeHead, 2);
    addListNode(&HelloListNodeHead, 3);

    printList(&HelloListNodeHead);

    updateListNode(&HelloListNodeHead, 2, 20);

    printList(&HelloListNodeHead);

    deleteListNode(&HelloListNodeHead, 1);

    printList(&HelloListNodeHead);


    return 0;
}

static void __exit hello_exit(void)
{
    freeList(&HelloListNodeHead);

    printk(KERN_INFO "hello: Goodbye World\n");
}


module_init(hello_init);
module_exit(hello_exit);
