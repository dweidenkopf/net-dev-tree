#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netdevice.h>


static int notifier(struct notifier_block *nb, unsigned long event, void *ptr)
{
	struct net_device *dev = (struct net_device *) ptr;
	struct net_device *parent = NULL;

	printk(KERN_INFO "notify event %lu.\n", event);
	if (event == NETDEV_REGISTER) {
		if (dev) {
			printk(KERN_INFO "dev name: %s\n", dev->name);	
			if (dev->iflink && dev->nd_net) {
				parent = dev_get_by_index(dev->nd_net, dev->iflink);
				if (parent) {
					printk(KERN_INFO "parent name: %s\n", parent->name);	
					dev_put(parent);
				}
			}
		}
	}
	return NOTIFY_DONE;
}

static struct notifier_block nb = {
	.notifier_call = notifier,
};

static int mod_init(void)
{
	struct net *net;
	struct net_device *dev;
	struct net_device *parent;
	int ret = 0;
	printk(KERN_INFO "Module loaded.\n");
//	ret = register_netdevice_notifier(&nb);
	//if (ret)
	//{
		//printk(KERN_INFO "register failed %d.\n", ret);
	//}

	for_each_net(net) {
		for_each_netdev(net, dev) {
			printk(KERN_INFO "dev name: %s\n", dev->name);	
			if (dev->iflink && dev->nd_net) {
				parent = dev_get_by_index(dev->nd_net, dev->iflink);
				if (parent) {
					printk(KERN_INFO "\tparent name: %s\n", parent->name);	
					dev_put(parent);
				}
			}
		}
	}
	
	return 0;
}


static void mod_exit(void)
{
	unregister_netdevice_notifier(&nb);

	printk(KERN_INFO "Module unloaded.\n");
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("foo");
MODULE_DESCRIPTION("bar");
