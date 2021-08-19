#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
	int fd;
	char Ubuff[]=" i am from user2 and delivered to kernel";
	char kbuff[80];

	fd=open("/dev/sub",O_RDWR,0777);
	if(fd<0)
	{
		printf("\nError opening file\n");
		exit(1);
	}
	
	write(fd,Ubuff,sizeof(Ubuff));
	read(fd,kbuff,80);

	printf("data read from kernel : %s\n",kbuff);	
	close(fd);


	return 0;
}
