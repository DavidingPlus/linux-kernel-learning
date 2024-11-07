#include <linux/fs.h>
#include <linux/export.h>

#include "file.h"


struct file_operations chrdev_fops = {
    .owner = THIS_MODULE,
    .open = chrdev_open,
    .release = chrdev_release,
    .write = chrdev_write,
    .read = chrdev_read,
};


dev_t devNumber = 0;

int devCount = 1;

struct cdev *cdev = NULL;

const char *devName = "chrdev";
