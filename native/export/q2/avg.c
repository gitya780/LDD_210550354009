#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>
#include"header.h"


MODULE_LICENSE("GPL");

static int my_add(int a, int b);


int a_test=50, b_test=40;

static int hello_init(void)
{
	int avg;
	printk(KERN_ALERT "Hello world\n");
	avg=my_add(a_test,b_test)/2;
	printk(KERN_ALERT "\n The Average is %d\n",avg);
	return 0;
}


static void hello_exit(void)
{
	printk(KERN_ALERT"Goodbye,World\n");
}

module_init(hello_init);
module_exit(hello_exit);
