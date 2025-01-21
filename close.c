#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int fd = open("example.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("File Open Failed");
		return 1;
	}
	
	if(close(fd) == -1)
	{
		perror("close failed");
		return 1;	
	}
	
	printf("File successfully closed\n");
        return 0;
}
