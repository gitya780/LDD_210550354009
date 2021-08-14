#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("GITESH");

// this is addition fuction that we are going to export as symbol
static int my_add(int a, int b)
{
	printk(KERN_ALERT"\n In Function HelloWorld_add of Module.....add\n");
	return(a+b);
}
// command to export symbol into kernel symbol table
EXPORT_SYMBOL(my_add);

// To initalise this module and load it into kernel symbol table

static int hello_init(void)
{
	
	printk(KERN_ALERT"\n HELLO TO ALL");
	return 0;
}
// this removes module from kernel symbol table

static void hello_exit(void)
{
	printk(KERN_ALERT"\n Bye to all\n");
}
module_init(hello_init);
module_exit(hello_exit);

