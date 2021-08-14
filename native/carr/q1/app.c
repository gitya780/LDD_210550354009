#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
int main()
{
	int FileDesc;

	char Ubuff="This is the user buffer ....sending Data to the Kernel.. ";
	char Kbuff[100];
	FileDesc=open("/dev/main",O_RDWR,0777);
	if(FileDesc<0)
	{
		printf("\nError opening Device\n");
		exit(1);
	}	
	//write(FileDesc,Ubuff,sizeof(ubuff));
	//read(FileDesc,Kbuff,50);
	//printf("\n The Data read from the Kernel is\n>>>> %s <<<<\n",Kbuff);
	close(FileDesc);
}	
