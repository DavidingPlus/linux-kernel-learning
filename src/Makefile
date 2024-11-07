ifneq ($(KERNELRELEASE),)

globalmem-objs := main.o file.o variable.o
obj-m := globalmem.o


else

KERNRLDIR ?= /lib/modules/${shell uname -r}/build/
PWD := ${shell pwd}

all:
	${MAKE} -C ${KERNRLDIR} M=${PWD} modules

# rm -rf *.o *.o.d core .depend .*.cmd *.ko *.mod.c *.tmp_version *.mod *.order *.symvers
.PHONY: clean
clean:
	${MAKE} -C ${KERNRLDIR} M=${PWD} clean


endif
