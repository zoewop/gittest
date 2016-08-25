obj-m := basicmem.o
#obj-m := mempool.o

#KDIR	:= /lib/modules/$(shell uname -r)/build
KDIR	:= /work/kernel-mds2450-3.0.22

all:
	make -C $(KDIR) SUBDIRS=$(PWD) modules
	$(CROSS_COMPILE)gcc -o basicmem basicmem.c
clean:
	make -C $(KDIR) SUBDIRS=$(PWD) clean

