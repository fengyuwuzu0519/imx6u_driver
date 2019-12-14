#include <linux/module.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/netdevice.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/netpoll.h>

static struct nf_hook_ops nfho;
static char *drop_if = "eth0";

#define NIPQUAD(addr) \
	    ((unsigned char *)&addr)[0], \
    ((unsigned char *)&addr)[1], \
    ((unsigned char *)&addr)[2], \
    ((unsigned char *)&addr)[3]

unsigned int hook_func (const struct nf_hook_ops *ops,
		struct sk_buff *skb,
		const struct nf_hook_state *state)
{
	struct iphdr *ip = ip_hdr(skb);
	printk("source ip :%d.%d.%d.%d\n",NIPQUAD(ip->saddr));
	printk("dev_name = %s\n",skb->dev->name);

	if (0 == strcmp(skb->dev->name, drop_if)) {
		printk("Dropped packet on %s ...\n", drop_if);
		return NF_DROP;//丢弃数据包
	} else {
		printk("Allow packet pass...\n");
		return NF_ACCEPT;//允许数据包通过
	}
}

static int virt_net_init(void)
{
	nfho.hook = hook_func;
	nfho.hooknum = NF_INET_PRE_ROUTING;
//	nfho.hooknum = NF_INET_POST_ROUTING;
	nfho.pf = PF_INET;
	nfho.priority = NF_IP_PRI_FIRST;//优先级，第一顺位
	nf_register_hook(&nfho);

	return 0;
}

static void virt_net_exit(void)
{
	nf_unregister_hook(&nfho);
}

module_init(virt_net_init);
module_exit(virt_net_exit);

MODULE_AUTHOR("yangf0519@163.com");
MODULE_LICENSE("GPL");
