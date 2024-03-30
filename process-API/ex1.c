// Purpose of this task is to show that the child process has a (near) identical copy of the parents
// address space values. However this is not shared memory! The values of x are still local to the parent and child.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

    int x = 100;

    int rc = fork();

    if (rc < 0){
        printf("fork failed");
        exit(1);
    }
    else if (rc == 0){ // child
        x = 10;
        printf("Value of x in child process (pid: %d ) is: %d\n", (int)getpid(), x);
    }
    else { // parent
        x = 5;
        printf("Value of x in parent process (pid: %d ) is: %d\n", (int)getpid(), x);
    }

    return 0;
}