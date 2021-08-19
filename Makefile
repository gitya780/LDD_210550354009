obj-m:= main.o
KDIR=/lib/modules/$(shell uname  -r)/build/
PWD:=$(shell pwd)

all:
	make -C $(KDIR) M=$(PWD) modules
	gcc app1.c -o apps
	gcc app2.c -o apps
clean:
	make -C $(KDIR) M=$(PWD) clean
	rm app1 app2
