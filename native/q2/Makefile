
obj-m:= init_param.o
KDIR=/lib/module/$(shell uname -r)/build/
all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
