#include "lglobal.h"

#include <linux/fs.h>
#include <linux/export.h>

#include "lfops.h"


struct file_operations globalfifoFops = {
    .owner = THIS_MODULE,
    .open = globalfifo_open,
    .release = globalfifo_release,
    .read = globalfifo_read,
    .write = globalfifo_write,
    .llseek = globalemem_llseek,
    .unlocked_ioctl = globalfifo_ioctl,
};

struct LGlobalFifoDataT globalfifoData = {
    .m_cdev = NULL,
    .m_devNumber = 0,
    .m_devCount = 1,
    .m_devName = "globalfifo",
    .m_mem = {0},
};
