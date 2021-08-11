#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/string.h>
static int add(int,int);
static int mul(int,int);

static int sub(int,int);
static int div(int,int);

static char* opt ="add";
static int v1=1;
static int v2=2;

module_param(opt,charp,S_IRUGO);

module_param(v1,int,S_IRUGO);

module_param(v2,int,S_IRUGO);

static int parm_init(void)
{

	if(strcmp(opt,"add")==0)
	{
		printk(KERN_ALERT"add=%d\n",add(v1,v2));
	}	

	else if(strcmp(opt,"mul")==0)
	{
		printk(KERN_ALERT"mul=%d\n",mul(v1,v2));
	}
	
	else if(strcmp(opt,"sub")==0)
	{
		printk(KERN_ALERT"sub=%d\n",sub(v1,v2));
	}

	else if(strcmp(opt,"div")==0)
	{
		printk(KERN_ALERT"add=%d\n",div(v1,v2));
	}
return 0;
}

static void para_exit(void)
{
	printk(KERN_ALERT"exit from module");
}
static int add(int v1,int v2)
{
	return(v1+v2);
}	

static int mul(int v1,int v2)
{
	return(v1*v2);
}

static int sub(int v1,int v2)
{
	return(v1-v2);
}

static int div(int v1,int v2)
{
	return(v1/v2);
}	

module_init(parm_init);
module_exit(para_exit);


