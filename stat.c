#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
	struct stat fileStat;
	
	if(stat("example.txt", &fileStat) == 0)
	{
		printf("File size: %ld bytes\n", fileStat.st_size);
       		printf("Last modified time: %ld\n", fileStat.st_mtime);
	}
	else
	{
		perror("stat failed");
	}
	return 0;
}
