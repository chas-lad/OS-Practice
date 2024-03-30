// Creates two children from the one parent, and conects the standard output of one to the standard input of the other using pipe().
// The output of child1 becomes the input of child2
// The first child echos some words as standard output and the second child recieves it as input

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pipefd[2];
    pid_t child1, child2;

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    child1 = fork();

    if (child1 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } 
    else if (child1 == 0) { // child1
        close(pipefd[0]); // Close the read end of the pipe
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to the write end of the pipe. It duplicates the file descriptor pipefd[1] (write end of the pipe) to the file descriptor number STDOUT_FILENO (standard output). After this call, any write operation to STDOUT_FILENO (e.g., using printf(), write(), etc.) will effectively write data to the write end of the pipe (pipefd[1]).
        close(pipefd[1]); // Close the original write end of the pipe
        execlp("echo", "echo", "Hello from Child1", NULL); // Execute echo command
        perror("exec");
        exit(EXIT_FAILURE);
    } 
    else { // parent
        child2 = fork();

        if (child2 < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } 
        else if (child2 == 0) { // child2
            close(pipefd[1]); // Close the write end of the pipe
            dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to the read end of the pipe
            close(pipefd[0]); // Close the original read end of the pipe
            execlp("wc", "wc", "-w", NULL); // Execute wc command to count words
            perror("exec");
            exit(EXIT_FAILURE);
        } 
        else {
            // Close both ends of the pipe in the parent
            close(pipefd[0]);
            close(pipefd[1]);
            printf("Parent.\n");
            wait(NULL); // Wait for child2 to complete
        }
    }

    return 0;
}
