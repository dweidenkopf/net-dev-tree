#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netdevice.h>


static int notifier(struct notifier_block *nb, unsigned long event, void *ptr)
{
	//struct net_device *dev = (struct net_device *) ptr;
	printk(KERN_INFO "notify event %lu.\n", event);
	return NOTIFY_DONE;
}

static struct notifier_block nb = {
	.notifier_call = notifier,
};

static int mod_init(void)
{
	int ret = 0;
	printk(KERN_INFO "Module loaded.");
	ret = register_netdevice_notifier(&nb);
	if (ret)
	{
		printk(KERN_INFO "register failed %d.", ret);
	}
	return 0;
}


static void mod_exit(void)
{
	unregister_netdevice_notifier(&nb);

	printk(KERN_INFO "Module unloaded.");
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("foo");
MODULE_DESCRIPTION("bar");
