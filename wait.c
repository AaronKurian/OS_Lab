#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	pid_t pid = fork();
	
	if (pid == 0)
	{
		printf("Child process (PID: %d) is exiting...\n", getpid());
        	exit(0);
	}
	else if (pid > 0)
	{
		int status;
		pid_t child_pid = wait(&status);
		if (child_pid > 0) 
		{
		    printf("Parent process (PID: %d) waited for child PID: %d to terminate.\n", getpid(), child_pid);
		} else 
		{
		    perror("wait failed");
		}
	}
	else
	{
		printf("Fork failed..");
	}
	return 0;
}
