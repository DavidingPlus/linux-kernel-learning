#include <linux/fs.h>
#include <linux/export.h>

#include "file.h"


struct file_operations globalmem_fops = {
    .owner = THIS_MODULE,
    .open = globalmem_open,
    .release = globalmem_release,
    .write = globalmem_write,
    .read = globalmem_read,
};


dev_t devNumber = 0;

int devCount = 1;

struct cdev *cdev = NULL;

const char *devName = "globalmem";
