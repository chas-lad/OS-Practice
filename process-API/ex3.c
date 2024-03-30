// The purpose of this exercise is to get Hello to print before Goodbye is printed all the time without using the wait() command.

// A pipe is a connection between two processes, such that the standard output from one process becomes the standard input of the other process.
// See https://www.geeksforgeeks.org/pipe-system-call/ for more info.

// In Unix-like operating systems, when a child process inherits a file descriptor from its parent,
// it gets a copy of that file descriptor. However, this copy still refers to the same underlying file
// or pipe in the operating system's file table. So, when the child writes to its copy of the writing
// end of the pipe (pipefd[1]), the data is written to the same underlying pipe that the parent's copy
// of pipefd[0] is reading from.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Create a child process
    int rc = fork();

    if (rc == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (rc == 0) {  // Child process
        close(pipefd[0]);  // Close the reading end of the pipe
        printf("Hello\n");
        write(pipefd[1], "1", 1);  // Write to the pipe
        close(pipefd[1]);  // Close the writing end of the pipe
        exit(EXIT_SUCCESS);
    } else {  // Parent process
        close(pipefd[1]);  // Close the writing end of the pipe
        char buf;
        read(pipefd[0], &buf, 1);  // Read from the pipe. This read call will block until the child writes to the pipe.
        printf("Goodbye\n");
        close(pipefd[0]);  // Close the reading end of the pipe
    }

    return 0;
}
