#include "list.h"

#include <linux/module.h>
#include <linux/slab.h>
#include <linux/list.h>


void addListNode(struct list_head *listHead, int id)
{
    HelloListNode *node = kmalloc(sizeof(HelloListNode), GFP_KERNEL);
    if (!node)
    {
        printk(KERN_ERR "kmalloc failed\n");


        return;
    }

    node->id = id;

    INIT_LIST_HEAD(&node->list);

    // 尾插。
    list_add_tail(&node->list, listHead);

    printk(KERN_INFO "add node: %d\n", id);
}

HelloListNode *findNode(struct list_head *listHead, int id)
{
    HelloListNode *pos = NULL;

    list_for_each_entry(pos, listHead, list)
    {
        if (pos->id == id) return pos;
    }


    return NULL;
}

void updateListNode(struct list_head *listHead, int oldId, int newId)
{
    HelloListNode *node = findNode(listHead, oldId);
    if (!node)
    {
        printk(KERN_INFO "node not found\n");


        return;
    }

    node->id = newId;

    printk(KERN_INFO "update %d -> %d\n", oldId, newId);
}

void deleteListNode(struct list_head *listHead, int id)
{
    HelloListNode *pos = NULL, *tmp = NULL;

    list_for_each_entry_safe(pos, tmp, listHead, list)
    {
        if (id == pos->id)
        {
            list_del(&pos->list);

            kfree(pos);

            printk(KERN_INFO "delete node: %d\n", id);


            return;
        }
    }

    printk(KERN_INFO "node not found\n");
}

void printList(struct list_head *listHead)
{
    HelloListNode *pos = NULL;

    printk(KERN_INFO "===== list begin =====\n");

    list_for_each_entry(pos, listHead, list)
    {
        printk(KERN_INFO "id = %d\n", pos->id);
    }

    printk(KERN_INFO "===== list end =====\n");
}

void freeList(struct list_head *listHead)
{
    HelloListNode *pos = NULL, *tmp = NULL;

    list_for_each_entry_safe(pos, tmp, listHead, list)
    {
        list_del(&pos->list);

        kfree(pos);
    }
}
