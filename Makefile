KERN_DIR = /home/xingxingzhihuo/src/myir/kernel

all:
	make -C $(KERN_DIR) M=`pwd` modules
	sz virt_net.ko

clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf modules.order

obj-m	+= virt_net.o
