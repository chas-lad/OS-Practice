// Despite the child and parent process both writing to the same file using the same
// file descriptor concurrently, the output is always deterministic with the parent process's
// content being written to the file first. There is no interleaving of text, which means the OS
// is handling the scheduling of the writes to the file for us so that one process does their entire write,
// finishes, then the next process performs it's entire write.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(){

    int fd = open("./testFile.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);

    int rc = fork();

    if (rc < 0){
        printf("fork failed");
        exit(1);
    }
    else if (rc == 0){ // child
        const char *data1 = "Hello, World!\n";
        const char *data2 = "This is a sample text.\n";
        ssize_t bytes_written;
        bytes_written = write(fd, data1, strlen(data1));

        printf("Child process (pid: %d )\n", (int)getpid());
    }
    else { // parent
        const char *data2 = "This is a sample text.\n";
        ssize_t bytes_written;
        bytes_written = write(fd, data2, strlen(data2));

        printf("Parent process (pid: %d )\n", (int)getpid());
    }

    close(fd);

    return 0;
}