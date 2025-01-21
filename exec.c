#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // Full path to the ls command and its arguments
    char *path = "/bin/ls";
    
    // Replaces the current process with the "ls -l" command
    printf("Before execl() call\n");
    
    // Execute the `ls -l` command using execl
    execl(path, "ls", "-l", (char *)NULL); // This replaces the current process with `ls -l`

    // If execl() fails, this line will be executed
    perror("execl() failed");
    return 1;
}

