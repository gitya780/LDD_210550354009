// initialization Functions......
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>

// Function Prototype
int NAME_open(struct inode *inode, struct file *flip);
int NAME_release(struct inode *inode, struct file *flip);
ssize_t NAME_write(struct file *flip, const char __user *Ubuff,size_t count, loff_t *offp);
ssize_t NAME_read(struct file *flip, char __user *Ubuff,size_t count,loff_t *offp);
//struct that defines the operation that the driver provides

struct file_operations fops =
{
	.owner = THIS_MODULE,
	.open  = NAME_open,
	.read = NAME_read,
	.write = NAME_write,
	.release = NAME_release,
};

// stucture for a character driver

struct cdev *my_cdev;

//init module

static int __init CharDevice_init(void)
{
	int result;
	int MAJOR,MINOR;
	dev_t Mydev;
	Mydev = MKDEV(255,0);// create a device driver
	MAJOR=MAJOR(Mydev);
	MINOR=MINOR(Mydev);
printk("\n the Major number is %dy...The Minor Number is %d\n",MAJOR,MINOR);
	result=register_chrdev_region(Mydev,1,"MyCharDevice");// register device region

if(result<0)
{
	printk(KERN_ALERT"\n The Region requested for is not obtainable");
	return(-1);
}	

my_cdev = cdev_alloc();// allocate memory to char Device structure
my_cdev->ops=&fops;// link our file operation to the char device

result=cdev_add(my_cdev,Mydev,1);// notify the kernel abt new device
if(result<0)
{
	printk(KERN_ALERT"\n The Char Device  has not been created...\n");
	unregister_chrdev_region(Mydev,1);
	return (-1);
}
return 0; 
}

// cleanup Module

void __exit CharDevice_exit(void)
{

	dev_t Mydev;
	int MAJOR,MINOR;
	Mydev = MKDEV(255,0);// create a device driver
	MAJOR=MAJOR(Mydev);
	MINOR=MINOR(Mydev);
	
printk("\n the Major number is %d...The Minor Number is %d\n",MAJOR,MINOR);
unregister_chrdev_region(Mydev,1);// unregister device number and Device created

cdev_del(my_cdev);
printk(KERN_ALERT"\n I have unregister the stuff thgat was  allocated ");
return;
}

// open System Call
int NAME_open(struct inode *inode,struct file *flip)
{
	printk(KERN_ALERT "\n This is the Kernel....Open Call..I Have nothing to do\n");
return 0;	
}	

// close System Call
int NAME_release(struct inode *inode,struct file *flip)
{
	printk(KERN_ALERT"\n This is the release method of my character driver\n");
	return 0;
}	
ssize_t NAME_write(struct file *flip, const char __user *Ubuff,size_t count,loff_t *offp)
{
	char kbuff[80];
	int result;
	ssize_t ret;
	result = copy_from_user((char*)kbuff,(char*)Ubuff,count);
	if(result==0)
	{
		printk(KERN_ALERT"Msg from user=%s\n",kbuff);
		printk(KERN_ALERT"%d data written successfully\n",count);
		ret=count;
		return count;
		}
		else
	{
		printk(KERN_ALERT"ERROR Writing data\n");
		ret = -EFAULT;
		return ret;
	}
}

ssize_t NAME_read(struct file *flip, char __user *Ubuff,size_t count,loff_t *offp)
{
	char kbuff[10] = "data";
	int result;
	ssize_t a;
	result = copy_to_user((char*)Ubuff,(const char*)kbuff,sizeof(kbuff));
	if(result==0)
	{
		printk("successfully\n");
	a= sizeof(kbuff);
	return count;
	}
	else
	{
		printk("error\n");
		return -1;
		
	}
}	


module_init(CharDevice_init);
module_exit(CharDevice_exit);

