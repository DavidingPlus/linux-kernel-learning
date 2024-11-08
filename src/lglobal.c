#include "lglobal.h"

#include <linux/fs.h>
#include <linux/export.h>

#include "lfops.h"


struct file_operations globalmemFops = {
    .owner = THIS_MODULE,
    .open = globalmem_open,
    .release = globalmem_release,
    .write = globalmem_write,
    .read = globalmem_read,
    .llseek = globalemem_llseek,
    .unlocked_ioctl = globalmem_ioctl,
};

struct LGlobalMemDataT globalmemData = {
    .m_cdev = NULL,
    .m_devNumber = 0,
    .m_devCount = 1,
    .m_devName = "globalmem",
    .m_mem = {0},
};
