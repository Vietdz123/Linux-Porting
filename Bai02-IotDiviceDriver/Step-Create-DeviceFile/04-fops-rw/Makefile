EXTRA_CFLAGS = -Wall
obj-m = main.o 

KDIR := /lib/modules/`uname -r`/build
CC := gcc

all:
	make -C $(KDIR) M=`pwd` modules
	$(CC) -o app app.c

clean:
	make -C $(KDIR) M=`pwd` clean
	rm -rf app
