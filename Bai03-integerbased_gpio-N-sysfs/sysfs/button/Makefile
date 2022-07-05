TOOLCHAIN := /home/wibu/working_space/Linux-Porting/BBB/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf/bin
PREFIX := arm-linux-gnueabihf-

ifeq ($(ARCH), arm)
	CC := $(TOOLCHAIN)/$(PREFIX)gcc
endif

all:
	$(CC) -o button app.c gpio.c -I.
	$(CC) -o main main.c 

clean:
	rm -rf button
	rm -rf main
