#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main() 
{
    pid_t pid = fork(); // Create a child process

    if (pid == 0) 
    {
        // Child process: simulates a long-running task
        printf("Child process (PID: %d) is running...\n", getpid());

        // Simulate a long-running task
        while (1) 
        {
            sleep(1);  // Child process keeps running
        }
    } 
    else if (pid > 0) 
    {
        // Parent process: sends a signal to the child to terminate it using kill()
        printf("Parent process (PID: %d) will send SIGTERM to child process (PID: %d)\n", getpid(), pid);

        sleep(2); // Give the child process some time to run

        // Send SIGTERM signal to the child process
        if (kill(pid, SIGTERM) == 0) 
        {
            printf("SIGTERM signal sent to child process (PID: %d)\n", pid);
        } else 
        {
            perror("kill() failed");
        }

        // Wait for the child process to terminate
        wait(NULL);
        printf("Parent process (PID: %d) has finished\n", getpid());
    } 
    else 
    {
        // Error occurred during fork()
        perror("fork() failed");
        exit(1);
    }

    return 0;
}

