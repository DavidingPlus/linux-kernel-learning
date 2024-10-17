KERNRLDIR ?= /lib/modules/${shell uname -r}/build/
PWD := ${shell pwd}

obj-m := hello.o
hello-objs := add.o main.o 


all:
	${MAKE} -C ${KERNRLDIR} M=${PWD} modules


.PHONY: clean
clean:
	${MAKE} -C ${KERNRLDIR} M=${PWD} clean
	# rm -rf *.o *.o.d core .depend .*.cmd *.ko *.mod.c *.tmp_version *.mod *.order *.symvers
