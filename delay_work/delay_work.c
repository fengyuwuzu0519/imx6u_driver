#include <linux/module.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/in.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/string.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/io.h>
#include <asm/irq.h>

struct delayed_work printk_work;

static void delay_work_run(struct work_struct *work)
{
	printk("-------run delay_work_run-------\n");
	schedule_delayed_work(&printk_work, 300);
}
static int delay_work_init(void)
{

	INIT_DELAYED_WORK(&printk_work, delay_work_run);
	schedule_delayed_work(&printk_work, 300);
	return 0;
}

static void delay_work_exit(void)
{
	cancel_delayed_work_sync(&printk_work);
}

module_init(delay_work_init);
module_exit(delay_work_exit);

MODULE_AUTHOR("yangf0519@163.com");
MODULE_LICENSE("GPL");
