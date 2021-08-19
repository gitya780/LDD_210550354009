#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include<linux/semaphore.h>
#include<linux/delay.h>

char k_buff[50]="this is kernel";
struct semaphore sem_dev;

int open_add(struct inode *inode, struct file *file_op_add);
int release_add(struct inode *inode, struct file *file_op_add);
ssize_t write_add(struct file *file_op_add,const char __user *u_buff,size_t count,loff_t *offp );
ssize_t read_add(struct file *file_op_add,char __user *u_buff, size_t count, loff_t *offp);

static int add_result; 
struct file_operations fop_add=
{
	.owner = THIS_MODULE,
	.open = open_add,
	.read = read_add,
	.write = write_add,
	.release = release_add,
};


int open_add(struct inode *inode, struct file *file_op_add)
{
	printk("AddDev is using MyCalDriver\n");
	return 0;
}


ssize_t read_add(struct file *file_op_add,char __user *u_buff,size_t count,loff_t *offp)
{
	    int result;
        ssize_t retval;
	
	if(down_interruptible(&sem_dev))
        {       
              return -ERESTARTSYS;
        }
        result = copy_to_user((char*)u_buff,(char *)k_buff,sizeof(k_buff));

        up(&sem_dev);
        
        if(result == 0)
        {

                printk(KERN_ALERT"copy to user successfull % d data written \n",sizeof(k_buff));
                retval = sizeof(k_buff);
                return count;
        }
        else
        {
                printk(KERN_ALERT"ERROR writting data to user\n");
                retval = -EFAULT;
                return retval;
        }
        
}


ssize_t write_add(struct file *file_op_add, const char __user *u_buff, size_t count, loff_t *offp)
{
	 int result;
        ssize_t retval;
  
  	if(down_interruptible(&sem_dev))
        {
             return -ERESTARTSYS;
        }

        result = copy_from_user((char*)k_buff,(char*)u_buff,count);
        
        up(&sem_dev);
        if(result==0)
        {
                printk(KERN_ALERT"Message from user : %s\n",k_buff);
                printk(KERN_ALERT"%d bytes of data written succesfully \n",count);
                retval = count;
                return count;
        }
        else
        {
                printk(KERN_ALERT"ERROR writing data\n");
                retval = -EFAULT;
                return retval;
        }

	
	
}


int release_add(struct inode *inode, struct file *file_op_add)
{
	printk("AddDev is logging off from MyCalDriver\n");
	return 0;
}


int open_sub(struct inode *inode, struct file *file_op_sub);
int release_sub(struct inode *inode, struct file *file_op_sub);
ssize_t write_sub(struct file *file_op_sub,const char __user *u_buff,size_t count, loff_t *offp);
ssize_t read_sub(struct file *file_op_sub, char __user *u_buff, size_t count, loff_t *offp);

static int sub_result;

struct file_operations fop_sub=
{
	.owner = THIS_MODULE,
	.open = open_sub,
	.read = read_sub,
	.write = write_sub,
	.release = release_sub,
};


int open_sub(struct inode *inode, struct file *file_op_sub)
{
	printk("SubDev is using MyCalDriver\n");
	return 0;
}


ssize_t write_sub(struct file *file_op_sub, const char __user *u_buff, size_t count,loff_t *offp)
{
		 int result;
        ssize_t retval;
  
  	if(down_interruptible(&sem_dev))
        {
            return -ERESTARTSYS;
        }
        result = copy_from_user((char*)k_buff,(char*)u_buff,count);
        up(&sem_dev);
        
        if(result==0)
        {
                printk(KERN_ALERT"Message from user : %s\n",k_buff);
                printk(KERN_ALERT"%d bytes of data written succesfully \n",count);
                retval = count;
                return count;
        }
        else
        {
                printk(KERN_ALERT"ERROR writing data\n");
                retval = -EFAULT;
                return retval;
        }

	
	
}


ssize_t read_sub(struct file *file_op_sub, char __user *u_buff, size_t count, loff_t *offp)
{
	if(down_interruptible(&sem_dev))
        {
                 return -ERESTARTSYS;
        }
         int result;
        ssize_t retval;

        result = copy_to_user((char*)u_buff,(char *)k_buff,sizeof(k_buff));

         up(&sem_dev);
        if(result == 0)
        {

                printk(KERN_ALERT"copy to user successfull % d data written \n",sizeof(k_buff));
                retval = sizeof(k_buff);
                return count;
        }
        else
        {
                printk(KERN_ALERT"ERROR writting data to user\n");
                retval = -EFAULT;
                return retval;
        }
       
}


*/
int release_sub(struct inode *inode, struct file *file_op_sub)
{
	printk("SubDev is logging of from MyCalDriver\n");
	return 0;
}


struct cdev *AddDev;
struct cdev *SubDev;


dev_t my_device_number;
dev_t mdn_add;
dev_t mdn_sub;


static int calcu_mod_on(void) 
{
	int on_success;
	int major;

	on_success = alloc_chrdev_region(&my_device_number, 0,4,"MyCalDriver"); 
	if (on_success < 0) 
	{
		printk(KERN_ALERT "not successfully allocated region\n");
		return 0;
	}

	major = MAJOR(my_device_number); 
	printk(KERN_ALERT "the allocated driver having the major number: %d\n\nminor no 0: for AddDev device\nminor no 1: for SubDev device\nn",major);
	
	printk("\nFor calculation purpose deiver expected the following device with its major and minor number:\naddition: AddDev\nsubtraction: SubDev\n");
	
	mdn_add = MKDEV(major,0);
	mdn_sub = MKDEV(major,1);

	AddDev = cdev_alloc(); 
	AddDev->ops = &fop_add;
	
	SubDev = cdev_alloc();
	SubDev->ops = &fop_sub;

	int result_add = cdev_add(AddDev,mdn_add,1);  to the kernel section
	if(result_add <0 ) 
	{
		printk(KERN_ALERT "driver not allocated by kernel\n");
		return -1;
	}

	int result_sub = cdev_add(SubDev,mdn_sub,1);
	if(result_sub <0)
	{
		printk(KERN_ALERT "driver not allocated by kernel\n");
		return -1;

	}
	sema_init(&sem_dev,1);
	return 0;
}
//module exit
static void calcu_mod_off(void)
{
	printk("your driver going to logging off\n");
	
	cdev_del(AddDev);
	cdev_del(SubDev);
	printk("all devices are logging off\n");
	
	unregister_chrdev_region(my_device_number, 4);
	printk("your driver log off\n");
}

module_init(calcu_mod_on);
module_exit(calcu_mod_off);



