obj-m := file_varea.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

TARGET_MODULE := file_varea

all: $(TARGET_MODULE).ko test

$(TARGET_MODULE).ko:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

test: test.c
	$(CC) -o test test.c

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
	rm -f test
