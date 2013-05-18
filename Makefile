KDIR ?= /lib/modules/`uname -r`/build

obj-m  := rtl8150.o

default:
	$(MAKE) -C $(KDIR) M=$$PWD

clean:
	rm -fr *.o *.ko .tmp* .rtl8150.* *.order *.symvers *.mod.c .built-in.*
