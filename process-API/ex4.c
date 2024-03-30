// Trying out different variants of exec() command,
// exec(), execle(), execlp(), execv(), execvp(), and execvpe()

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
        char* args[3];
        args[0] = "/bin/ls";
        args[1] = NULL; // list of arguments must always be terminated by a NULL pointer when using exec.

        execv(args[0], args);
    }
    else { // parent
        x = 5;
        printf("Value of x in parent process (pid: %d ) is: %d\n", (int)getpid(), x);
    }

    return 0;
}