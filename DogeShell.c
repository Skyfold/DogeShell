#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


void fork_and_run(char *program[], char *p_args[]) 
{ 
    // Find out your parent and fork
    pid_t parent = getpid();
    pid_t pid = fork();


    if (pid == -1){
        printf("you failed to fork, find out why");

    // Find out who you are
    } else if(pid >0){
        // you are the parent
        int status;
        waitpid(pid, &status, 0);

    // Do things as child
    } else {
        //append ./ before this.
        execvp(program, p_args);
        printf("Command not found");

    }
}

char* getInput()
{
    char *str = NULL;
    size_t size = 0;
    getline(&str, &size, stdin);
    str[(strlen(str) - 1)] = 0;
    return str;
}

int main(void)
{
    printf("Welcome to Doge Shell\n");
    for (;;) {
    char *program = getInput();

    char *p_args[] =  {program, NULL};
    fork_and_run(program, p_args);
    }
    return 0;
}