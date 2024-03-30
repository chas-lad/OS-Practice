// The purpose of this exercise is to get Hello to print before Goodbye is printed all the time without using the wait() command.

// A pipe is a connection between two processes, such that the standard output from one process becomes the standard input of the other process.
// See https://www.geeksforgeeks.org/pipe-system-call/ for more info.

// When we use fork in any process, file descriptors remain open across child process and also parent process. If we call fork after
// creating a pipe, then the parent and child can communicate via the pipe.


// If you connect two processes - parent and child - using a pipe, you create the pipe before the fork.
// The fork makes the both processes have access to both ends of the pipe. This is not desirable.

// The reading side is supposed to learn that the writer has finished if it notices an EOF condition. This can only happen if all writing sides are closed. So it is best if it closes its writing FD ASAP.
// The writer should close its reading FD just in order not to have too many FDs open and thus reaching a maybe existing limit of open FDs. Besides, if the then only reader dies, the writer gets notified about this by getting a SIGPIPE or at least an EPIPE error (depending on how signals are defined). If there are several readers, the writer cannot detect that "the real one" went away, goes on writing and gets stuck as the writing FD blocks in the hope, the "unused" reader will read something.

// So here in detail what happens:
// parent process calls pipe() and gets 2 file descriptors: let's call it rd and wr.
// parent process calls fork(). Now both processes have a rd and a wr.

// Suppose the child process is supposed to be the reader.
// Then
// the parent should close its reading end (for not wasting FDs and for proper detection of dying reader) and
// the child must close its writing end (in order to be possible to detect the EOF condition).

// Bascially, the read end of the pipe will only see an "end of file" condition (i.e. have read return 0) if the write end of the pipe is closed (meaning that all open file descriptors which refer to it are closed).
// Closing an end of a pipe in a child does not close it for the parent, this is because each process has its own file descriptor table.

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
