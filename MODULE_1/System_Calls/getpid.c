#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t pid = getpid();
	printf("The process ID is %d\n", pid);
	return 0;
}
