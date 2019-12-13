#ifndef __SHARE_H__
#define __SHARE_H__

#define dump_mem(mem, len)				\
{							\
	int i;					\
	printk("%s: mem = %p len = 0x%x\n", __func__, (mem), (len)); \
		for (i = 0; i < (len); i++) {		\
			if (i !=0 && i%16 == 0)		\
			printk("\n");			\
			printk("0x%02x ", (mem)[i]);	\
	}					\
	printk("\n");				\
}

#endif
