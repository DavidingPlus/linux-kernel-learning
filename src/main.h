#ifndef _MAIN_H_
#define _MAIN_H_


struct globalmem_dev_t
{
    struct cdev *cdev;

    dev_t devNumber;

    int devCount;

    const char *devName;
};


#endif
