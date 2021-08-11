#include<linux/init.h>
#include<linux/module.h>

static int hello_init(void)
{
	printk("Hello_world\n");
	return 0;
}
static void hello_cleanup(void)
{
	printk("Good bye\n");
}
module_init(hello_init);
module_exit(hello_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("GITESH");
MODULE_DESCRIPTION("A simple hello world LKM!");

