// Calling close(STDOUT_FILENO); closes the standard output in the current running process and so any subsequent printf()'s won't work.

// Key Points about File Descriptors:
// Unique Identifiers: Each open file or resource is assigned a unique file descriptor, which is an integer value.
// E.g. If we have a file on our disk called file1.txt our OS will assign a unique file descriptor value to it.

// Standard File Descriptors:
// 0: Standard Input (stdin)
// 1: Standard Output (stdout)
// 2: Standard Error (stderr)

// Range:
// File descriptors range from 0 to INT_MAX (typically 2^31 - 1 on 32-bit systems and 2^63 - 1 on 64-bit systems).
// Inherited on Fork: When a process is forked (using the fork() system call), the child process inherits the file descriptors of the parent process.

// Used with System Calls: File descriptors are used with system calls like open(), read(), write(), close(), socket(), bind(), listen(), accept(), etc.,
// to perform input/output operations and manage resources.

// Difference between open and fopen():
// fopen and fclose etc.. are part of a library and are higher level abstractoions of using lower level open() and read().
// When you use the fopen() function in C to open a file, it returns a pointer to a FILE object rather than a file descriptor.
// The FILE object encapsulates the file descriptor internally, and you can use this FILE object with the standard I/O functions
// like fread(), fwrite(), fgets(), fprintf(), etc., to perform input/output operations on the open file.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

    int rc = fork();

    if (rc < 0){
        printf("fork failed");
        exit(1);
    }
    else if (rc == 0){ // child
        printf("child: hello\n");
        close(STDOUT_FILENO);
        printf("child: world\n");

    }
    else { // parent
        printf("parent: hello\n");
        printf("parent: world\n");

    }

    return 0;
}