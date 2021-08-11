#include<linux/nodule.h>
#include<linux/init.h>
#include<linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("GITESH");
MODULE_DISCRIPTION("MODULE PARAMETER");
// VARIABLE ARE DECLEAR AS STATIC
static int intvar 7;
module_param(intvar,int,S_IRUGO);

static int param_init(void)
{
	printk(	KERN_ALERT"\n in init function");
	printk(KERN_ALERT"\n valur of intvar =%d\n",intvar);
return 0;
}

static void param_exit(void)
{
	printk(KERN_ALERT"\n BYE");

}	

module_init(param_init);
module_exit(param_exit);

