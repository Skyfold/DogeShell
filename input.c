#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Linked_List.h"
#include <unistd.h>
#include <termios.h>

struct termios termios_original;

void reset_input_mode(void){
    tcsetattr(STDIN_FILENO, TCSANOW, &termios_original);
}

void setTermios(void){
    struct termios termio;
    
    //This sees if the input is not from the terminal (may not be necessary, but may need later)
    if(!isatty(STDIN_FILENO)){
        //TODO: make this ignore everything
        fprintf(stderr, "You are trying to input things not from the terminal, why?\n");
        exit(EXIT_FAILURE);
    }

    //This gets the terminal settings and gets terminal settings so you can reset terminal
    if (tcgetattr(STDIN_FILENO, &termio) || tcgetattr(STDIN_FILENO, &termios_original)){
        fprintf(stderr, "You cannot get the settings from terminal, good luck XD\n");
        exit (EXIT_FAILURE);
    }

    
    //This returns the terminal state to normal on exit    
    atexit(reset_input_mode);

    //Change the terminal settings and set them (note this does not check if they were actually applied or if something else went wrong)
    termio.c_lflag &= ~ICANON;
    termio.c_lflag &= ~ECHO;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &termio)){
        fprintf(stderr, "Your terminal settings didn't get set\n");
        exit(EXIT_FAILURE);
    }

}


int main(void){
    init_Linked_List();
    setTermios();

    int c = '\0';
    for (;;){

        read(STDIN_FILENO, &c, 1);
        switch(c){

            // c-d key;
            case '\004':
                exit(0);

            //this is the delete key
            case '\177':
                removeCharFromTerminal();
                break;

            case '\033':
                read(STDIN_FILENO, &c, 1);
                read(STDIN_FILENO, &c, 1);
                switch (c){
                    case 'D': 
                    //left
                    moveBack();
                        break;
                    case 'C':
                    //right
                    moveForword();
                        break;
                    case 'A':
                    //up
                        break;
                    case 'B':
                    //down
                        break;
                    default:
                        fprintf(stderr, "Your escape sequence has %c find out why", c);
                        exit(EXIT_FAILURE);
                }
                break;

            case '\n':
                printf("\n");
                //printFromRoot();
                printf("\n");
                break;
            default:
                printCharToTerminal(c);
        }
    }
}
