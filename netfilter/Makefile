KERN_DIR = /home/xingxingzhihuo/src/myir/kernel

all:
	make -C $(KERN_DIR) M=`pwd` modules
	sz netfilter_hook.ko

clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf modules.order

obj-m	+= netfilter_hook.o
