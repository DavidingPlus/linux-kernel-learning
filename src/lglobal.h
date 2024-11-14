#ifndef _LGLOBAL_H_
#define _LGLOBAL_H_

#include <linux/types.h>
#include <linux/ioctl.h>
#include <linux/mutex.h>


#define GLOBALFIFO_SIZE 0x1000
#define MEM_CLEAR _IO('c', 0)


struct LGlobalFifoDataT
{
    struct cdev *m_cdev;

    dev_t m_devNumber;

    int m_devCount;

    const char *m_devName;

    unsigned char m_mem[GLOBALFIFO_SIZE];

    struct mutex m_mtx;
};


#endif
