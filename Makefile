# Makefile
obj-m := basicmem.o

KDIR	:= /work/kernel-mds2450-3.0.22

all:
	make -C $(KDIR) SUBDIRS=$(PWD) modules
	$(CROSS_COMPILE)gcc -o basicmem basicmem.c
clean:
	make -C $(KDIR) SUBDIRS=$(PWD) clean

