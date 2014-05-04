#include "linked_list.h"
#include "history.h"
#include <termios.h>
#include <string.h>
#include "dynamic_char_array.h"
#include "input.h"


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


char** inputFromTerminal(struct DCharArray* PosList){
    init_Linked_List();
    setTermios();

    bool HistMode = false;

    bool parenthesesBool = true;
    int c = '\0';
    read(STDIN_FILENO, &c, 1);
    for(;;){
        switch(c){

            // c-d key;
            case '\004':
                exit(0);

            //this is the delete key
            case '\177':
                removeCharFromTerminal();
                HistMode = false;
                break;

            case '\033':
                read(STDIN_FILENO, &c, 1);
                read(STDIN_FILENO, &c, 1);
                switch (c){
                    case 'D': 
                        //left
                        HistMode = false;
                        moveBack();
                        break;

                    case 'C':
                        //right
                        HistMode = false;
                        moveForword();
                        break;

                    case 'A':
                        //up
                        if(LineIsEmpty()){
                            PosList = DCharArray_upHist(PosList);
                            //printf("%s\n", &(PosList->DList[PosList->hist_pos].CharArray[4]));
                            HistMode = true;
                        }else if(HistMode){
                            RemoveAllText();
                            PosList = DCharArray_upHist(PosList);
                            //printf("%s\n", PosList->DList[PosList->hist_pos].CharArray);
                        }
                        break;

                    case 'B':
                        if(HistMode){
                            RemoveAllText();
                            PosList = DCharArray_downHist(PosList);
                        }
                        //down
                        break;

                    case 56:
                    case 70:
                        moveToEnd();
                        //end
                        break;

                    case 55:
                    case 72:
                        moveToStart();
                        //home
                        break;

                    default:
                        fprintf(stderr, "Your escape sequence has %c find out why", c);
                        exit(EXIT_FAILURE);
                    }
                    break;

            case '\"':
                if(parenthesesBool){
                    parenthesesBool = false;
                }else{
                    parenthesesBool = true;
                }
                HistMode = false;
                printCharToTerminal(c);
                break;

            case '\n':
                if(parenthesesBool){
                        char* temp = flattenList();
                        SaveHist(temp);
                        PosList = DCharArray_add_from_file(PosList);
                        return TokenArray(temp);
                }else{
                    printCharToTerminal(c);
                    printf("> ");
                    fflush(stdout);
                }
                break;

            case 9:
                break;

            default:
                printCharToTerminal(c);
                HistMode = false;
        }
        read(STDIN_FILENO, &c, 1);
    }
}

// int main(int argc, char const *argv[])
// {
//     char **temp = input();
//     printf("\n%s\n", temp[0]);
//     return 0;
// }
