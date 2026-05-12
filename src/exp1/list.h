#ifndef _LIST_H_
#define _LIST_H_

#include <linux/list.h>


typedef struct HelloListNode
{
    int id;

    struct list_head list;
} HelloListNode;


void addListNode(struct list_head *listHead, int id);

void updateListNode(struct list_head *listHead, int oldId, int newId);

void deleteListNode(struct list_head *listHead, int id);

void printList(struct list_head *listHead);

void freeList(struct list_head *listHead);


#endif
