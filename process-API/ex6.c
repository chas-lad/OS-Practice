// wait() is used to wait for any child process to terminate
// waitpid() provides more control over which child process to wait for and how to handle specific child processes.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

    int childID = fork();

    if (childID < 0){
        printf("fork failed");
        exit(1);
    }
    else if (childID == 0){ // child
        printf("child with child process: %d\n", getpid());
    }
    else { // parent
        int status;
        int x = waitpid(childID, &status, 0);
        printf("parent. value returned from wait = %d. Child exited with status: %d", x, status);
    }

    return 0;
}