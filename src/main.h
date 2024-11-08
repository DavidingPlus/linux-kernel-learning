#ifndef _MAIN_H_
#define _MAIN_H_

#include <linux/types.h>


#define GLOBALMEM_SIZE 0x1000


struct LGlobalMemDataT
{
    struct cdev *m_cdev;

    dev_t m_devNumber;

    int m_devCount;

    const char *m_devName;

    unsigned char m_mem[GLOBALMEM_SIZE];
};


#endif
