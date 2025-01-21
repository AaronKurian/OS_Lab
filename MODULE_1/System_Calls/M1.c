/*
Program to Implement 
-fork
-exec
-getpid
-exit
-wait
-close
-stat
-opendir
-readir
System Commands
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

int main() 
{
    // Part 1: Demonstrating fork()
    pid_t pid = fork();
    
    if (pid == 0) 
    {
        // Child process: demonstrates exec()
        printf("Child process (PID: %d) - Before exec()\n", getpid());

        // Replaces the current process with the "ls -l" command
        execl("/bin/ls", "ls", "-l", (char *)NULL);
        
        // If execl fails, print the error message
        perror("execl() failed");
        exit(1);
    } 
    else if (pid > 0) 
    {
        // Parent process: demonstrates wait()
        int status;
        pid_t child_pid = wait(&status);
        if (child_pid > 0) 
        {
            printf("Parent process (PID: %d) waited for child (PID: %d) to terminate\n", getpid(), child_pid);
        } else 
        {
            perror("wait() failed");
        }

        // Part 2: Demonstrating getpid() (in parent)
        printf("Parent process (PID: %d)\n", getpid());

        // Part 3: Demonstrating file operations (close and stat)
        int fd = open("example.txt", O_RDONLY);
        if (fd == -1) 
        {
            perror("File open failed");
        } else 
        {
            printf("File 'example.txt' opened successfully. Closing file...\n");
            close(fd);  // Closing the file
        }

        struct stat fileStat;
        if (stat("example.txt", &fileStat) == 0) 
        {
            printf("File size: %ld bytes\n", fileStat.st_size);
            printf("Last modified time: %ld\n", fileStat.st_mtime);
        } else 
        {
            perror("stat() failed");
        }

        // Part 4: Demonstrating opendir() and readdir()
        DIR *dir = opendir(".");
        if (dir == NULL) 
        {
            perror("opendir() failed");
            exit(1);
        }

        struct dirent *entry;
        printf("Directory contents:\n");
        while ((entry = readdir(dir)) != NULL) 
        {
            printf("Found file: %s\n", entry->d_name);
        }

        closedir(dir);  // Close the directory stream
    } 
    else 
    {
        // Error occurred during fork()
        perror("fork() failed");
        exit(1);
    }

    // Part 5: Demonstrating exit()
    printf("Parent process (PID: %d) is exiting\n", getpid());
    exit(0);

    return 0;  // This line will never be reached
}

