#include "input.h"
#include "linked_list.h"
#include "history.h"
#include "dynamic_char_array.h"

void fork_and_run(char* program, char** p_args) 
{ 
    // Find out your parent and fork
    if(!strncmp(program, "cd", 2)){
        chdir(p_args[1]);

    }else if(!strncmp(program, "exit", 4)){
        printf("Goodbye\n");
        exit(0);
    }else{

        //pid_t parent = getpid(); Change this one day
        pid_t pid = fork();


        if (pid == -1){
            printf("you failed to fork, find out why\n");

        // Find out who you are
        } else if(pid >0){
            // you are the parent
            int status;
            waitpid(pid, &status, 0);
            if(status){
                //change all the things
            }

        // Do things as child
        } else {
            //append ./ before this.

            char temp[64] = "./";
            char* bla = strcat(temp, program);

            char* swap = p_args[0];
            p_args[0] = bla;
            execvp(bla, p_args);

            p_args[0] = swap;

            execvp(program, p_args);
            printf("DogeShell: command not found: %s\n", program);
        }

    }
}

void printDoge(void){
    FILE* fp = fopen("doge.txt", "r");
    char c [64];
    while(fgets(c, 64, fp) != NULL){
        printf("%s", c);
    }
    fclose(fp);
}

int main(int argc, char const *argv[])
{
    if(argc == 1){
        struct DCharArray* list = Init_DCharArray();
        list = DCharArray_add_from_file(list);
        //struct DCharArray* list = Init_DCharArray();
        char *buf = NULL;
        printDoge();
        printf("Welcome to Doge Shell\n");
        printf("%s$ ", getwd(buf));
        fflush(stdout);

        for (;;) {
            char** input = inputFromTerminal(list);
            printf("\n");
            if (input[0] != NULL){
                char* program = input[0];
                fork_and_run(program, input);
                printf("%s$ ", getwd(buf));
                fflush(stdout);
            } else {
                printf("%s$ ", getwd(buf));
                fflush(stdout);
                free(buf);
            }
        }
        free(buf);
    }else {
        char** temp = (char**)malloc((argc*sizeof(char*)));
        for (int i = 0; i < argc; ++i)
        {
            temp[i] = (char*)malloc(strlen(argv[i])*sizeof(char));
        }
        
        //This copy the argv so that I can run it with a function that takes a non constant char.
        //I don't have to do this, but in order to compile without warnings it needs to be done
        for (int i = 0; i < argc; ++i)
        {
                stpcpy(temp[i], argv[i]);
        }

        //argc[0] is itself in other words DogeShell, I don't want it to just run itself everytime...
        char** temp2 = &temp[1];
        fork_and_run(temp[1], temp2);

        //free the arrays within the array
        for (int i = 0; i < argc; ++i)
        {
            free(temp[i]);
        }
        free(temp);
    }
    return 0;
}