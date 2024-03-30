// Using wait command. The value returned from the wait command is 
// the process ID of the dead child.

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
        printf("child with child process: %d\n", getpid());
    }
    else { // parent
        int status;
        int x = wait(&status);
        printf("parent. value returned from wait = %d. Child exited with status: %d", x, status);
    }

    return 0;
}