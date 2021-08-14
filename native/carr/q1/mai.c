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

//struct that defines the operation that the driver provides

struct file_operations fops =
{
	.owner = THIS_MODULE,
	.open  = NAME_open,
	//.read = NAME_read,
	//.write = NAME_write,
	.release = NAME_release,
};

// stucture for a character driver

struct cdev *my_cdev;

//init module

static int _init  CharDevice_init(void)
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

void _init CharDevice_exit(void)
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
module_init(CharDevice_init);
module_exit(CharDevice_exit);

